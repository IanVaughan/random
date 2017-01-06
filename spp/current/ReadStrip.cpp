//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ReadStrip.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//#include <commdlg.h>
TStringList *strLst_fileData ;       // list to hold data from file

// -----------------------------------------------------------------------------
ReadStrip::ReadStrip()
{
    strLst_fileData = new TStringList ;
}

// -----------------------------------------------------------------------------
void ReadStrip::openFile(AnsiString fromFile, TComboBox *toCombo)
{
    //if executed then load all text from file into strLst_fileData

        strLst_fileData->LoadFromFile(fromFile);

        AnsiString temp ;                               // temp substring
        for (int i=0;i<strLst_fileData->Count ;i++) {   //loop num of items in strLst_fileData
            temp = strLst_fileData->Strings[i] ;        //convert strLst_fileData to AnsiString
            if(temp.SubString(0,2) == "FO") {           //if the DRAW_LINE is a FOrmat DRAW_LINE
                int i = 5;                              //counter, set after 'FO "'
                AnsiString ch;                          // temp char holder
                do{
                   ch = temp.SubString(i,1);            // get 1 char
                   i++;
                }while(ch!="\"");                       //repeat until end of name string (in quotes)
                toCombo->Items->Add(temp.SubString(5,i-6)) ; //add name to string list
            }//if
        }//for
}//openFile

// -----------------------------------------------------------------------------
bool __fastcall ReadStrip::createStrip(AnsiString stripName, TStringList *data, TCanvas *canvas, TPoint scale)
{
    //FO "Ians Strip 1" 7.75 1
    int index = 0;                  // used to hold hte pos of the fps we want out of the StringList
    int i=0;
    // find the name passed form the combox box in the strLst_fileData
    for (i;i<strLst_fileData->Count ;i++) { //loop num of items in strLst_fileData
        // return the pos of the strip name into index
        index = strLst_fileData->Strings[i].Pos(stripName) ;
        if(index!=0) break ; // if found break so we keep where it was found (index)
    }
    if(index==-1) // stripName should be their!!
       Application->MessageBox("Error! Not Found.","Read:showStrip",MB_OK);
    if(index>0) {
        AnsiString t1 = strLst_fileData->Strings[i] ; // temp string DRAW_LINE
        // get the string thats after the name by
        // creating a substring from the index + length of the stripName + 2 (1 for " and 1 for a whitespace)
        // to the end of the whole string
        t1 = t1.SubString(index+stripName.Length()+2, t1.Length());

        //get strip details
        // width
        int n_width = t1.Pos(" "); // find space
        AnsiString s_width = t1.SubString(0,n_width-1); //  get 1st numbers
        float f_width = s_width.ToDouble(); // convert to float
        //height
        AnsiString s_height = t1.SubString(n_width+1,t1.Length()-n_width); // get 2nd numbers
        float f_height = s_height.ToDouble();

        // this bit is only relevent in draw to the screen
        // clear rect & resize image box to fix current fps
//        if(to==TO_SCR) {
//            Form1->Image1->Width = f_width*xInch ;
//            Form1->Image1->Height = f_height*yInch ;
//        }

        //output of rectangle
        canvas->Rectangle(0,0,f_width*scale.x,f_height*scale.y) ;

        //other info (LI and text) eg.
        //  LI 100 0 100 300
        do{ // repeat thougth stringLines reading id until FO found or end of list
            i++ ;
            t1 = strLst_fileData->Strings[i] ; // temp string DRAW_LINE
            if(t1.Pos("LI")>0) // find out if a LI idenifier is there
            {
                AnsiString t2 = t1;   // make a copy so we can muck around with it
                //x1
                t2 = t2.SubString(4,t2.Length()-3); // get the numbers after the LI code
                AnsiString s = t2.SubString(0,t2.Pos(" ")-1); // get first number
                float x1 = s.ToDouble();
                //y1
                t2 = t2.Delete(1,t2.Pos(" ")); // cut out num just used
                s = t2.SubString(0,t2.Pos(" ")-1); // get first number
                float y1 = s.ToDouble();
                //x2
                t2 = t2.Delete(1,t2.Pos(" ")); // cut out num just used
                s = t2.SubString(0,t2.Pos(" ")-1); // get first number
                float x2 = s.ToDouble();
                //y2
                t2 = t2.Delete(1,t2.Pos(" ")); // cut out num just used
                float y2 = t2.ToDouble();

                //draw lines
                 canvas->MoveTo(x1*scale.x,y1*scale.y);
                 canvas->LineTo(x2*scale.x,y2*scale.y);
            }
            else if(t1.Pos("FO")==0) // if not a FO DRAW_FIELD then it must be a name DRAW_FIELD
            {
                //eg FO DRAW_LINE : CS 5 5 10 RED
                AnsiString t2 = t1 ; // copy current DRAW_LINE so we cut muck around with it
                AnsiString text = t2.SubString(0,t2.Pos(" ")-1);  // get 1st 2 letters,the code '??'
                // x
                t2 = t2.Delete(1,t2.Pos(" ")); // cut out just used ??
                AnsiString s = t2.SubString(0,t2.Pos(" ")-1); // get 1st number
                float x = s.ToDouble();
                // y
                t2 = t2.Delete(1,t2.Pos(" ")); // cut out just used ??
                s = t2.SubString(0,t2.Pos(" ")-1); // get first number
                float y = s.ToDouble();
                // point
                t2 = t2.Delete(1,t2.Pos(" ")); // cut out just used ??
                s = t2.SubString(0,t2.Pos(" ")-1); // get first number
                int point = s.ToInt();
                //color
                t2 = t2.Delete(1,t2.Pos(" ")); // cut out num just used
                AnsiString color = t2 ;

                // convert ascii text from file to TColor tc
                TColor tc ;  // temp color var
                if(color=="BLACK") tc = clBlack ;
                if(color=="BLUE") tc = clBlue ;
                if(color=="RED") tc = clRed ;

                for (int i=0;i<data->Count ;i++)   // loop all of string list
                {
                    // if the 'text' from this big if from ubove matches up in the string list passed in
                    if(data->Strings[i].Pos(text)!=0)
                    {
                        AnsiString t9 = data->Strings[i].Delete(1,3); ;
                        canvas->Font->Size = point ;   // set font to size 'point'
                        canvas->Font->Color = tc ;  // set font color to 'tc'
                        canvas->TextOut(x*scale.x,y*scale.y,t9);
                    }
                }
            }
            //used to show the Image, prob with sizeing if the 2nd size is smaller than the 1st

            if(t1.Pos("FO")>0) break ;
        }while(i<strLst_fileData->Count-2); //while less than num of items in list
                                     // or another FO code reached
    }

    // clear up if the output was to the printer
//    if(to==TO_PRN) {
//        prnOut->EndDoc();
//    }

    return true;
}//createStrip

// -----------------------------------------------------------------------------
