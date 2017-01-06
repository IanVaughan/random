//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Search.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSearchForm *SearchForm;
//---------------------------------------------------------------------------

__fastcall TSearchForm::TSearchForm(TComponent* Owner) : TForm(Owner)
{
    Edit1->Text = "File path";
    Edit1->SelStart = 0;
    Edit1->SelLength = 9;


    StringGrid1->Cells[0][0] = "Filename";
    StringGrid1->Cells[1][0] = "Size";

    faAnyFileCBClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TSearchForm::faAnyFileCBClick(TObject *Sender)
{
    if(faAnyFileCB->Checked == true)
    {
        faReadOnlyCB->Enabled = false;
        faHiddenCB->Enabled = false;
        faSysFileCB->Enabled = false;
        faVolumeIDCB->Enabled = false;
        faDirectoryCB->Enabled = false;
        faArchiveCB->Enabled = false;

        faReadOnlyCB->Checked = false;
        faHiddenCB->Checked = false;
        faSysFileCB->Checked = false;
        faVolumeIDCB->Checked = false;
        faDirectoryCB->Checked = false;
        faArchiveCB->Checked = false;
    }
    else
    {
      faReadOnlyCB->Enabled = true;
        faHiddenCB->Enabled = true;
        faSysFileCB->Enabled = true;
        faVolumeIDCB->Enabled = true;
        faDirectoryCB->Enabled = true;
        faArchiveCB->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSearchForm::SearchBTNClick(TObject *Sender)
{
    TSearchRec sr;
    int iAttributes = 0;
    StringGrid1->RowCount = 2;

    iAttributes |= faReadOnly * faReadOnlyCB->Checked
                | faHidden * faHiddenCB->Checked
                | faSysFile * faSysFileCB->Checked
                | faVolumeID * faVolumeIDCB->Checked
                | faDirectory * faDirectoryCB->Checked
                | faArchive * faArchiveCB->Checked
                | faAnyFile * faAnyFileCB->Checked;

    if (FindFirst(Edit1->Text, iAttributes, sr) == 0)
    {
        if (sr.Attr == iAttributes)
        {
            StringGrid1->Cells[0][StringGrid1->RowCount] = sr.Name;
            StringGrid1->Cells[1][StringGrid1->RowCount] = IntToStr(sr.Size);
        }

        while (FindNext(sr) == 0)
        {
            if (sr.Attr == iAttributes)
            {
                StringGrid1->Cells[0][StringGrid1->RowCount-1] = sr.Name;
                StringGrid1->Cells[1][StringGrid1->RowCount-1] = IntToStr(sr.Size);
                StringGrid1->RowCount++;
            }
        }
    }
    FindClose(sr);
}
//---------------------------------------------------------------------------

void __fastcall TSearchForm::SpeedButton1Click(TObject *Sender)
{
    if(OpenDialog->Execute())
    {
        Edit1->Text = OpenDialog->FileName;
    }
}
//---------------------------------------------------------------------------

