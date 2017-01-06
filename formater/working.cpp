//notes:
//doesnt allow same line ifs
//doesnt allow non use of { } on simple lines
//doesnt capture { } in strings
//if prev line have no ; then it was a long line, extra dent next line
//same as next one line ifs
//for loops with no {
//not to tab in single comments like these
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "working.h"
#include "formator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma resource "*.dfm"
Twork *work;
int gap ;
bool inComment ;
bool extraGap ;
//---------------------------------------------------------------------------

__fastcall Twork::Twork(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Twork::FormShow(TObject *Sender)
{
    Animate1->Active = true ;
    Run();
}
//---------------------------------------------------------------------------

void Twork::Run()
{
//?
    Show();
    stopBTN->Kind = bkAbort ;
    again->Visible = false ;

    //add all the files from the TFileList to a string list
    TStringList *filenames = new TStringList ;

    if(!startForm->allDir->Checked)
    {
        for (int i = 0; i < startForm->FileListBox1->Items->Count; i++)
            if (startForm->FileListBox1->Selected[i])
               if (FileExists(startForm->FileListBox1->Items->Strings[i]))
                    filenames->Add(startForm->FileListBox1->Items->Strings[i]);
    }
    //else add whole dir to string list : filenames

    gau->MaxValue = filenames->Count;
    gap = startForm->numtabs->Value;

    for(int i=0; i<filenames->Count; i++) {
        filenameLabel->Caption = filenames->Strings[i] ;
        Do(filenames->Strings[i]);
        gau->Progress = i;
    }

    Animate1->Active = false  ;
    stopBTN->Kind = bkClose;
    stopBTN->Caption = "Close" ;
    again->Visible = true ;
}
// -----------------------------------------------------------------------------

void Twork::Do(String filename)
{
    TStringList *file = new TStringList ;
    file->LoadFromFile(filename);

    ProgressBar1->Max = file->Count;
    to->Caption = file->Count;
    from->Caption = "0" ;

//    int extra_gap=0 ;
    String aline;
    int inc = 0 ;
    for(int i=0; i<file->Count; i++)
    {
        from->Caption = i ;
        aline = file->Strings[i] ;

//        if(aline.Pos("/*") && !InString(aline, aline.Pos("/*"))) inComment = true ;
//        if(aline.Pos("*/") && !InString(aline, aline.Pos("*/"))) inComment = false ;
        inComment = false ;

        if(aline.Pos("}")
        && !InString(aline, aline.Pos("}"))
        && !InComment(aline, aline.Pos("}"))) {
            inc -- ;
        }
        //method for making sure an if without an { is only inc once, ie just the next line
/*        if(extra_gap >0)
        {
            inc--;
            extra_gap-- ;
        }
 */
        //the hard bits
        file->Strings[i] = CheckLine(aline, inc*gap);
//        CheckLength(file, i);

        if(aline.Pos("{")
        && !InString(aline, aline.Pos("{"))
        && !InComment(aline, aline.Pos("{")))
            inc++;

        //or if code hasnt got an '{'
//        if( (aline.Pos("if") || aline.Pos("for") || aline.Pos("do") ) &&
//             aline.Pos("{")==0 && file->Strings[i+1].Pos("{")==0) {
//            inc ++ ;
//            extra_gap ++ ;
//        }

        ProgressBar1->StepIt();
        Application->ProcessMessages();
    }

    //if the database file is read only, change it
    String dbase = filename;
    DWORD attrib = GetFileAttributes(dbase.c_str());
    if((attrib&FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY)
    //set it to read write
    SetFileAttributes(dbase.c_str(), attrib-FILE_ATTRIBUTE_READONLY);

    file->SaveToFile(filename);
    delete file;
}
// -----------------------------------------------------------------------------

bool Twork::SplitableChar(char ch)
{
    if(ch == '.' || ch == '>' || ch == '=' || ch == ')' || ch == ',' || ch == '-')
    return true;
    else
    return false ;
}
// -----------------------------------------------------------------------------

bool Twork::InString(String testSt, int pos)
{
    //get string on left side of cursor
    String onLeft = testSt.SubString(0, pos-1);
    //get string on right side of cursor
    String onRight = testSt.SubString(pos, testSt.Length());

    //if no " on the right side of cursor, then all clear, not in a string
    if(onRight.Pos("\"") == 0) return false ;
    else
    if(onLeft.Pos("\"")==0) return false;
    else
    //ok, simple test failed, so now, if on rhs a ", then see if others on rhs
    if(onRight.Pos("\"")) {
        //get a line from " to eol
        String temp = onRight.SubString(onRight.Pos("\"")+1, onRight.Length());
        // if line has another " in then see how many
        if(temp.Pos("\"")){
            int count = 0;
            do{
                temp = temp.SubString(temp.Pos("\"")+1, temp.Length());
                count++;
            }while(temp.Length() > 0 && temp.Pos("\""));
            float fcount = count/2 ;
        }
        // if not, then we were in a string
        else return true ;
    }
    else return true;
}
// -----------------------------------------------------------------------------

String Twork::CheckLine(String aline, int dent)
{
    //if the string is empty, forget, lets go home!
    if(aline.IsEmpty()) return "";
    //get rid of the spaces already there
    aline = aline.TrimLeft();
    String space ;
    //make a string holding the number of spaces needed
    for(int a=0; a<dent; a++) space.Insert(" ",0);
    //if the line was just inserted because it was too long, then give it an extra gap
    if(extraGap) {
        for(int a=0; a<gap; a++)
        space.Insert(" ", 0);
        extraGap = false ;
    }
    //insert the spaces
    aline.Insert(space,0);
    return aline;
}
//------------------------------------------------------------------------------

void Twork::CheckLength(TStringList *list, int index)
{
    int maxlen = startForm->lineLen->Value ;
    String aline = list->Strings[index] ;

    //now check line length
    if(aline.Length() > maxlen)
    {
        //ok, so its longer, where can we cut it off!
        //Twork backwards from the maxlen point to see it we reach a cut point
        int loop = maxlen ;
        String newLine;
        do{
            //check if the current char is a valid one to split a line on
            if(SplitableChar(aline[loop]))
                // if it is, check that were not in a text string "hello world"
                if(!InString(aline,loop))  {
                    //if not, then split it up and get out, else keep going for next one
                    newLine = aline.SubString(loop+1, aline.Length());
                    aline = aline.SubString(0, loop);
                    extraGap = true ;
                    break;
               }
               loop--;
            }while(loop>0);
            //if loop counter not zero, then we did it! else, try again
            if(loop==0) {
            //if its got a remark, we can basicly do what we want with it
            if(aline.Pos("//")) {
                int compos = aline.Pos("//");
                //if from the comment to the eol is less than the maxlinelen
                // then do this
                if((aline.Length() - compos) < maxlen){
                    newLine = aline.SubString(compos+1, aline.Length());
                    aline = aline.SubString(0,compos);
                    extraGap = true ;
                }
                //else no valid split before comment, have to split the comment up
                else {
                    //so find a space in the comment
                    loop=maxlen ;
                    do{loop--;}while(aline[loop]!=' ');
                    newLine = "//" + aline.SubString(loop, aline.Length());
                    aline = aline.SubString(0, loop-1);
                    extraGap = true ;
                }
            }
        }
        list->Insert(index, newLine);
    }
}
//---------------------------------------------------------------------------

bool Twork::InComment(String line, int pos)
{
    if(inComment)return true;
    int com = line.Pos("//");
    if(com==0) return false ;
    if(pos<com) return false ;
    return true ;
}
// -----------------------------------------------------------------------------

void __fastcall Twork::stopBTNClick(TObject *Sender)
{
    startForm->Close();
    Close();
}

void __fastcall Twork::againClick(TObject *Sender)
{
    startForm->Show();
    Hide();
}
//---------------------------------------------------------------------------

