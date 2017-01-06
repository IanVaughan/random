//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CodeViewCreatorSrc.h"
#include "CreatorSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCodeViewCreator *CodeViewCreator;
//---------------------------------------------------------------------------

__fastcall TCodeViewCreator::TCodeViewCreator(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TCodeViewCreator::GoBTNClick(TObject *Sender)
{
    Hide();
    Creator->Create(DirectoryListBox->Items->Strings[DirectoryListBox->ItemIndex]);
    Show();
}
//---------------------------------------------------------------------------

void __fastcall TCodeViewCreator::CancelBTNClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

