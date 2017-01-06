//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "read1.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
#include "DisplayStrip.h"
TreadForm *readForm;
TDisplayStripForm *OutStrip;
AnsiString fromFile = "demo1.spp" ;
//---------------------------------------------------------------------------
__fastcall TreadForm::TreadForm(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//user clicks this to print strip
void __fastcall TreadForm::printClick(TObject *Sender)
{
 // if the user has selected an item in the combox box
    if(ComboBox1->ItemIndex != -1)
    {
        TStringList *strLst_displayData = new TStringList ;          // holds data to be displayed
        strLst_displayData->Add("CS,BAW231");
        strLst_displayData->Add("NF,THING");

        if(PrintDialog1->Execute())
        {
            //output strip
            OutStrip->printStrip(ComboBox1->Text, strLst_displayData);
        } // if print

        delete strLst_displayData ;
    }// if combox
}// end printClick

// -----------------------------------------------------------------------------
// user clicks this to show strip to screen
void __fastcall TreadForm::screenClick(TObject *Sender)
{
    // if the user has selected an item in the combox box
    if(ComboBox1->ItemIndex != -1)
    {
        //create temp strLst_fileData to send to showStrip
        TStringList *strLst_displayData = new TStringList ;          // holds data to be displayed
        strLst_displayData->Add("CS,BAW231");
        strLst_displayData->Add("NF,THING");

        OutStrip->showStrip(ComboBox1->Text, strLst_displayData);

        delete strLst_displayData ;
    }
    else
    {
        TStringList *strLst_displayData = new TStringList ;          // holds data to be displayed
        strLst_displayData->Add("CS,BAW231");
        strLst_displayData->Add("NF,THING");

        if(!OutStrip->showStrip(ComboBox1->Text, strLst_displayData))
        {
            Application->MessageBox("Strip format not found.","Reader",MB_OK+MB_ICONEXCLAMATION);
        }

        delete strLst_displayData ;
    }
}//end speedButton show to screen

//---------------------------------------------------------------------------


void __fastcall TreadForm::FormShow(TObject *Sender)
{
    TStringList *sl = new TStringList ;         // temp string list
    AnsiString as ;                             // temp ansiString
    as = OutStrip->getFormats(fromFile); //
    sl->CommaText = as;                         // convert ansistring to stringlist
    for(int i=0; i<sl->Count; i++) {            // add string list to combox
        ComboBox1->Items->Add(sl->Strings[i]);
    }
    delete sl ;
}
//---------------------------------------------------------------------------

