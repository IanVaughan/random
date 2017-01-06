//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DataPrepSrcFake.h"
#include "MapEditorFake.h"
#include "DPFormSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner)
{
    RegCallback(ToBeCalled);
}
//---------------------------------------------------------------------------

bool TMainForm::ToBeCalled(DPFormShowData *dataIn)
{
    MapData = dataIn;

    DPForm->ShowModal();

//dont need to
//    (*dataIn) = MapData;

//    MapData = NULL;

    return false;
}
// -----------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

