//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "testRunner.h"
#include "GroundVehiclePerformanceEditorSrc.h"
#include "GroundVehicleEditorSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TtestRun *testRun;
//---------------------------------------------------------------------------

__fastcall TtestRun::TtestRun(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TtestRun::gvpeBTNClick(TObject *Sender)
{
    GroundVehiclePerformanceEditor->Show();
}
//---------------------------------------------------------------------------

void __fastcall TtestRun::gveBTNClick(TObject *Sender)
{
    GroundVehicleEditorForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TtestRun::CloseBTNClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

