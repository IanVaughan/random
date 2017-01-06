//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DPFormSrc.h"
#include "DataPrepSrcFake.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDPForm *DPForm;
//---------------------------------------------------------------------------

__fastcall TDPForm::TDPForm(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TDPForm::FormShow(TObject *Sender)
{
    Label1->Caption = ((DPBasicData*)MainForm->MapData->test->Items[0])->Name;
}
//---------------------------------------------------------------------------

void __fastcall TDPForm::Button1Click(TObject *Sender)
{
    //delete the DPBasicData item
    delete MainForm->MapData->test->Items[0];

    //delete the TList
    delete MainForm->MapData->test;
    MainForm->MapData->test = NULL;

    DPBasicData *add = new DPBasicData;
    strcpy(add->Name, "TestSrc");
    memset(add->LatLong, 0, 30);

    MainForm->MapData->test = new TList;
    MainForm->MapData->test->Add(add);

    Close();
}
//---------------------------------------------------------------------------

