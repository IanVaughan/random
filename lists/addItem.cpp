//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "addItem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TaddItemForm *addItemForm;
//---------------------------------------------------------------------------
__fastcall TaddItemForm::TaddItemForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TaddItemForm::BitBtn1Click(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TaddItemForm::BitBtn2Click(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TaddItemForm::FormShow(TObject *Sender)
{
    itemName->Clear();
//    cat->Checked = true;
}
//---------------------------------------------------------------------------

