//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DeleteFormSrc.h"
#include "FileCtrl.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDeleteForm *DeleteForm;
//---------------------------------------------------------------------------

__fastcall TDeleteForm::TDeleteForm(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TDeleteForm::DeleteFiles(String kPathDir)
{
    TSearchRec sr;

    String kPathDirExt = kPathDir + "*.*";

    // search for files, starting with the first of the type
    FindFirst(kPathDirExt, faAnyFile, sr);

    while(FindNext(sr) == 0)
    {
        DeleteFile(/*kPathDir + */sr.Name);
    }

    FindClose(sr);
}
// -----------------------------------------------------------------------------

void __fastcall TDeleteForm::DirBTNClick(TObject *Sender)
{
    if(OpenDialog1->Execute())
    {
        Edit1->Text = OpenDialog1->FileName;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDeleteForm::DeleteBTNClick(TObject *Sender)
{
    String kAirspacePathDir = Edit1->Text;//"\\";

    //delete all existing best files.
    if (DirectoryExists(kAirspacePathDir))
    {
        Label1->Caption = "Dir found OK";

        //clear the directory
        DeleteFiles(kAirspacePathDir);

        CloseHandle(kAirspacePathDir.c_str());

        //remove the directory
        bool bDone = RemoveDir(kAirspacePathDir);
        if(!bDone)
        {
            Label2->Caption = "Dir not deleted";
        }
        else
        {
            Label2->Caption = "Dir deleted OK";
        }
    }
    else
    {
        Label1->Caption = "Dir not found";
    }
}
//---------------------------------------------------------------------------

void __fastcall TDeleteForm::CloseBTNClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

