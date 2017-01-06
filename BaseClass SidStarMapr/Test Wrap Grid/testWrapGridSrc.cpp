//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "testWrapGridSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WrapGrid"
#pragma resource "*.dfm"
TtestWrapGrid *testWrapGrid;
//---------------------------------------------------------------------------
__fastcall TtestWrapGrid::TtestWrapGrid(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
