//---------------------------------------------------------------------------
#include "stdio.h"
#include <vcl.h>
#pragma hdrstop

#include "extactMsgBoxTextSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma link "WrapGrid"
#pragma resource "*.dfm"
TextractMsgTextForm *extractMsgTextForm;
//---------------------------------------------------------------------------
__fastcall TextractMsgTextForm::TextractMsgTextForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TextractMsgTextForm::ExtractSingleFile1Click(TObject *Sender)
{
    if (OpenDialog1->Execute())
    {
        fileNameP->Caption = OpenDialog1->FileName;
//        ConvertFiles(OpenDialog1->Files);
    }
}
//---------------------------------------------------------------------------

void __fastcall TextractMsgTextForm::ExtractMultiableFiles1Click(TObject *Sender)
{
    FILE *stream;
    char FirstLine[512];

    TStringList *file = new TStringList ;

    OpenDialog1->Options.Clear();
    OpenDialog1->Options << ofAllowMultiSelect << ofFileMustExist;
    OpenDialog1->Filter = "Cpp Files (*.cpp)|*.cpp|Text files (*.txt)|*.txt|All files (*.*)|*.*";
    OpenDialog1->FilterIndex = 0; // start the dialog showing all files

    int lineCount = 0;

    if (OpenDialog1->Execute())
    {
//        fileNameP->Caption = OpenDialog1->DirName;
        StatusBar1->SimpleText = "Working..." ;
        ProgressBar1->Max = OpenDialog1->Files->Count ;
        for (int I = 0; I < OpenDialog1->Files->Count; I ++)
        {
            StringGrid1->RowCount = I+1 ;
            StringGrid1->Cells[0][I+1] = OpenDialog1->Files->Strings[I] ;

/*            stream = fopen(OpenDialog1->Files->Strings[I].c_str(), "r");
            if (stream)
            {
                // read the first line from the file
                fgets(FirstLine, sizeof(FirstLine), stream);
                StringGrid1->Cells[1][I+1] = FirstLine;
                fclose(stream);
            }
*/


            String fileLine = "" ;
            file->LoadFromFile(OpenDialog1->Files->Strings[I]);
            for(int i=0; i<file->Count; i++)
            {
                fileLine = file->Strings[i] ;
                StringGrid1->Cells[1][I+1] =  i ;
                float perc_a = i.IntToFloat / file->Count ;
                float perc = perc_a * 100 ;
                StringGrid1->Cells[2][I+1] =  perc;
                Application->ProcessMessages();
            }
            lineCount += file->Count ;

            StringGrid1->Cells[2][I+1] = "Done";
            StringGrid1->Row = I ;





            ProgressBar1->Position = I ;

            Application->ProcessMessages();
        }
        StatusBar1->SimpleText = "Done. Line count is "+lineCount ;
    }
}
//---------------------------------------------------------------------------

void __fastcall TextractMsgTextForm::Exit1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void TextractMsgTextForm::ConvertFiles(TStrings *fl)
{
//
}
void __fastcall TextractMsgTextForm::FormShow(TObject *Sender)
{
    StringGrid1->Cells[0][0] = "File Name";
    StringGrid1->Cells[1][0] = "A line";
    StringGrid1->Cells[2][0] = "Percent done";
}
//---------------------------------------------------------------------------

