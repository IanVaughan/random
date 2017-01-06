//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MapEditorFake.h"
#include "MapEditorSrcFake.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMapEditorFormFake *MapEditorFormFake;
// -----------------------------------------------------------------------------
DPFormShowData *dpData;
//---------------------------------------------------------------------------
__fastcall TMapEditorFormFake::TMapEditorFormFake(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMapEditorFormFake::Button1Click(TObject *Sender)
{
    dpData = new DPFormShowData;
    dpData->test = new TList;

    DPBasicData *add = new DPBasicData;
    strcpy(add->Name, "TDLL");
    memset(add->LatLong, 0, 30);

    dpData->test->Add(add);

    SendMsg(&dpData);

    delete dpData->test->Items[0];
    delete dpData->test;
    delete dpData;
}
//---------------------------------------------------------------------------
