//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "filter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfilterForm *filterForm;
//---------------------------------------------------------------------------
__fastcall TfilterForm::TfilterForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfilterForm::FormShow(TObject *Sender)
{
//    Query1->ParamByName("sidid")->AsString = "_";
    Query1->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfilterForm::goClick(TObject *Sender)
{
    if(go->Down)
        Query1->Filtered = true;
    else
        Query1->Filtered = false;
}
//---------------------------------------------------------------------------

void __fastcall TfilterForm::Edit1Change(TObject *Sender)
{
    int id = Edit1->Text.ToIntDef(-999);
    if(id == -999)
        go->Enabled = false;
    else
    {
        Query1->Filter = "Route_Segment_Type='" + (String)id + "'";
        go->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfilterForm::paramClick(TObject *Sender)
{
    Query1->Close();
    Query1->ParamByName("fixid")->AsString = paramEdit->Text;
    Query1->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfilterForm::paramEditChange(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TfilterForm::paramEditKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == VK_RETURN)
        paramClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TfilterForm::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == VK_RETURN)
        go->Down = true;
//        goClick(this);
}
//---------------------------------------------------------------------------
