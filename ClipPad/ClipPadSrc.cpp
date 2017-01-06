//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ClipPadSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClipPad *ClipPad;
//---------------------------------------------------------------------------

__fastcall TClipPad::TClipPad(TComponent* Owner) : TForm(Owner)
{
    Memo1->Strings->Clear();
}
//---------------------------------------------------------------------------
