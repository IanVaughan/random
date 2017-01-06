//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MapEditorFake.h"
#include "DPInterface.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDPInterface *DPInterface;
// -----------------------------------------------------------------------------

DPFormShowData *dpData;
// -----------------------------------------------------------------------------

__fastcall TDPInterface::TDPInterface(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TDPInterface::Button1Click(TObject *Sender)
{
    dpData = new DPFormShowData;

    DPBasicData *add = new DPBasicData;
    strcpy(add->Name, "TDLL");
    memset(add->LatLong, 0, 30);

    dpData->test = new TList;
    dpData->test->Add(add);

    Label1->Caption = ((DPBasicData*)dpData->test->Items[0])->Name;

    SendMsg(dpData);

    Label2->Caption = ((DPBasicData*)dpData->test->Items[0])->Name ;

    delete dpData->test->Items[0];
    delete dpData->test;
    delete dpData;
}
//---------------------------------------------------------------------------

