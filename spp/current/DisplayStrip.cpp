//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DisplayStrip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDisplayStripForm *DisplayStripForm ;

// -----------------------------------------------------------------------------
#include <printers.hpp>
#include <stdlib.h>
TStringList *strLst_fileData ;       // list to hold data from file

//---------------------------------------------------------------------------
__fastcall TDisplayStripForm::TDisplayStripForm(TComponent* Owner)
    : TForm(Owner)
{
     strLst_fileData = new TStringList ;     // init the list to hold file data
     strLst_fileData = NULL ;
}

//---------------------------------------------------------------------------
//initial : 163/62-7/9/99
// method : getFormats()
// in : null
// returns : AnsiString - a comma seperated string containing all the strip formats in the given file
AnsiString __fastcall TDisplayStripForm::getFormats(AnsiString fileName)
{
    strLst_fileData->LoadFromFile(fileName);    //load all text from file into strLst_fileData

    TStringList *formatNames = new TStringList ; //list to hold names of formats to return

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
            formatNames->Add(temp.SubString(5,i-6)) ; //add name to string list
        }//if
    }//for

    temp = formatNames->CommaText;
    delete formatNames;

    return temp ;
}//openFile

// -----------------------------------------------------------------------------
// initial : createStrip
// in : AnsiString stripName - the strip format to use
//   : TStringList *data - a list of items to be displayed (eg "CS,BAW321" will put BAW321 where CS is defined)
//   : whereOut to - a typeDef of TO_PRN or TO_SCR, used to define where to ouput
// returns : true if found format & displayed it, false otherwize.
bool __fastcall TDisplayStripForm::createStrip(AnsiString stripName, TStringList *data, whereOut to)
{
    int xInch, yInch;
    TCanvas *canvas ;
    TPrinter *prnOut = Printer() ;

    switch (to) {
        case TO_SCR : {
                            Caption = "DisplayStrip - " + stripName ;
                            canvas = DisplayStripForm->Canvas ;
                            xInch = DisplayStripForm->PixelsPerInch ;
                            yInch = DisplayStripForm->PixelsPerInch ;
                            break;
                      }
        case TO_PRN : {
                          prnOut->BeginDoc();
                          canvas = prnOut->Canvas;

                          // next 4 blocks all to get the DPI on the printer
                          // block calls GetPrinter to get the current printer settings
                          char ch_device[80] = "";        // create temp char arrays to hold GetPrinter call
                          char ch_driver[80] = "";
                          char ch_port[80] = "";
                          int prnDeviceMode = 0;
                          prnOut->GetPrinter(ch_device, ch_driver, ch_port, prnDeviceMode);

                          HANDLE prnHandle ; // the HANDLE to the printer
                          OpenPrinter(ch_device, &prnHandle, NULL); // get a HANDLE to the printer

                          LONG docPropRet = DocumentProperties(DisplayStripForm->Handle, prnHandle,"", NULL, NULL, 0);               // step 1 - get size for DEVMODE struct
                          DEVMODE *dev_mode = (DEVMODE*)malloc(docPropRet) ;                                              // step 2 - create full DEVMODE stuct for size returned
                          docPropRet = DocumentProperties(DisplayStripForm->Handle, prnHandle, "", dev_mode, 0, DM_OUT_BUFFER);      // step 3 - get the printer settings into a DEVMODE struct

                          xInch = dev_mode->dmPrintQuality ;
                          yInch = dev_mode->dmYResolution ;

                          free (dev_mode);
                          break;
                      }
    }//end switch

    //FO "Ians Strip 1" 7.75 1
    int index = 0;                  // used to hold hte pos of the fps we want out of the StringList
    int i=0;
    // find the name passed form the combox box in the strLst_fileData
    for (i;i<strLst_fileData->Count ;i++) { //loop num of items in strLst_fileData
        index = strLst_fileData->Strings[i].Pos(stripName) ; // return the pos of the strip name into index
        if(index!=0) break ; // if found break so we keep where it was found (index)
    }
    if(index<=0){ // stripName should be their!!
       return false ;
    }else
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
        if(to==TO_SCR) {
            DisplayStripForm->Width = f_width*xInch ;
            DisplayStripForm->Height = f_height*yInch ;
        }

        if(to==TO_SCR) {
            DisplayStripForm->Show();             //show the form
            //output of rectangle
            canvas->Rectangle(0,0,f_width*xInch,f_height*yInch) ;
        }
        else {
            DisplayStripForm->Hide();             //hide
        }

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
                 canvas->MoveTo(x1*xInch,y1*yInch);
                 canvas->LineTo(x2*xInch,y2*yInch);
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
                        canvas->TextOut(x*xInch,y*yInch,t9);
                    }
                }
            }
            //used to show the Image, prob with sizeing if the 2nd size is smaller than the 1st

            if(t1.Pos("FO")>0) break ;
        }while(i<strLst_fileData->Count-2); //while less than num of items in list
                                     // or another FO code reached

        // clear up if the output was to the printer
        if(to==TO_PRN) {
            prnOut->EndDoc();
        }
        return true;
    }
    else return true ;
}//createStrip

//---------------------------------------------------------------------------
// initial : showStrip
// in : AnsiString stripName - the strip format to use
//   : TStringList *data - a list of items to be displayed (eg "CS,BAW321" will put BAW321 where CS is defined)
// returns : true if found format & displayed it, false otherwize.
bool __fastcall TDisplayStripForm::showStrip(AnsiString name, TStringList* list)
{
    return createStrip(name, list, TO_SCR);
}

// -----------------------------------------------------------------------------
// initial : printStrip
// in : AnsiString stripName - the strip format to use
//   : TStringList *data - a list of items to be displayed (eg "CS,BAW321" will put BAW321 where CS is defined)
// returns : true if found format & displayed it, false otherwize.
bool __fastcall TDisplayStripForm::printStrip(AnsiString name, TStringList* list)
{
     return createStrip(name, list, TO_PRN);
}

// -----------------------------------------------------------------------------
void __fastcall TDisplayStripForm::FormDestroy(TObject *Sender)
{
    delete strLst_fileData ;
}
//---------------------------------------------------------------------------

