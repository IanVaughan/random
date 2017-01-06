//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "RecCount.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDBRecCount *DBRecCount;
//---------------------------------------------------------------------------

__fastcall TDBRecCount::TDBRecCount(TComponent* Owner) : TForm(Owner)
{
    DBRecCountSG->Cells[0][0] = "Table Name \\ Record Count";
    DBRecCountSG->Cells[1][0] = "1";

    DBRecCountSG->ColWidths[0] = 150;

    m_kDBName = "BestDatabase";
    DBNameEdit->Text = m_kDBName;

    OptionsPanel->Visible = false;

    Show();
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::FormShow(TObject *Sender)
{
    FillTableNames();

    ProgressBar1->Max = m_pkDBTablesSL->Count;
    ProgressBar1->Hide();

//    GoBTNClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::FormDestroy(TObject *Sender)
{
    delete m_pkDBTablesSL;
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::GoBTNClick(TObject *Sender)
{
    GoBTN->Enabled = false;
    ProgressBar1->Show();

    Count();

    DBRecCountSG->ColCount++;
    DBRecCountSG->Cells[DBRecCountSG->ColCount-1][0] = DBRecCountSG->ColCount-1;
    ProgressBar1->Position = 0;
    ProgressBar1->Hide();

    GoBTN->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::CloseBTNClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void TDBRecCount::FillTableNames()
{
    ProgressBar1->Show();

    m_pkDBTablesSL = new TStringList;
    GetTableNames(m_pkDBTablesSL);

    for(int i = 0; i < m_pkDBTablesSL->Count; i++)
    {
        PopulateFieldNames(m_pkDBTablesSL->Strings[i]);

        /*DBRecCountSG->Cells[0][i+1] = m_pkDBTablesSL->Strings[i];
        DBRecCountSG->RowCount++;

        ProgressBar1->Position = i;
        Application->ProcessMessages();*/
    }

    ProgressBar1->Hide();
}
// -----------------------------------------------------------------------------

void TDBRecCount::GetTableNames(TStringList *&pkSL)
{
    try
    {
        BestDB->Session->GetTableNames(m_kDBName, "*.*", false, false, pkSL);
    }
    catch (...)
    {
        throw;
    }
}
// -----------------------------------------------------------------------------

void TDBRecCount::PopulateFieldNames(String kTableName)
{
    DBRecCountSG->Cells[0][DBRecCountSG->RowCount-1] = kTableName;

    TTable *pkTempT = new TTable(this);
    pkTempT->DatabaseName = "BestDatabase";
    pkTempT->TableName = kTableName;
    pkTempT->Open();

    for(int i=0; i<pkTempT->FieldCount; i++)
    {
        DBRecCountSG->Cells[0][DBRecCountSG->RowCount] = " - " + pkTempT->Fields[i]->FieldName;
        DBRecCountSG->RowCount++;

        ProgressBar1->Position = i;
        Application->ProcessMessages();
    }

    pkTempT->Close();
    delete pkTempT;
}
// -----------------------------------------------------------------------------

void TDBRecCount::Count()
{
    TQuery *pkGetRecCountQ = new TQuery(this);
    pkGetRecCountQ->DatabaseName = m_kDBName;

    DBRecCountSG->Visible = false;

    for(int i = 0; i < m_pkDBTablesSL->Count; i++)
    {
/*        pkGetRecCountQ->SQL->Add("SELECT COUNT (*) FROM " + m_pkDBTablesSL->Strings[i]);
        pkGetRecCountQ->Open();
        DBRecCountSG->Cells[DBRecCountSG->ColCount-1][i+1] = pkGetRecCountQ->Fields[0]->AsInteger;
        pkGetRecCountQ->Close();
        pkGetRecCountQ->SQL->Clear();
*/

        GetFieldData(m_pkDBTablesSL->Strings[i], i);
    }

    DBRecCountSG->Visible = true;

    delete pkGetRecCountQ;
}
// -----------------------------------------------------------------------------

void TDBRecCount::GetFieldData(String kTableName, int nRow)
{
//    DBRecCountSG->Cells[0][DBRecCountSG->RowCount-1] = kTableName;

/*        pkGetRecCountQ->SQL->Add("SELECT * FROM " + m_pkDBTablesSL->Strings[i]);
        pkGetRecCountQ->Open();
        DBRecCountSG->Cells[DBRecCountSG->ColCount-1][i+1] = pkGetRecCountQ->Fields[0]->AsInteger;
        pkGetRecCountQ->Close();
        pkGetRecCountQ->SQL->Clear();
*/

    TTable *pkTempT = new TTable(this);
    pkTempT->DatabaseName = "BestDatabase";
    pkTempT->TableName = kTableName;
    pkTempT->Open();

    for(int recCount=0; recCount<pkTempT->RecordCount; recCount++)
    {
        for(int fieldCount=0; fieldCount<pkTempT->FieldCount; fieldCount++)
        {
            DBRecCountSG->Cells[recCount+1][nRow] =
                    " - " + pkTempT->Fields[fieldCount]->AsString;
            DBRecCountSG->RowCount++;

            ProgressBar1->Position = fieldCount * recCount;
            Application->ProcessMessages();
        }
    }

    pkTempT->Close();
    delete pkTempT;
}
// -----------------------------------------------------------------------------

void __fastcall TDBRecCount::DBNameEditExit(TObject *Sender)
{
    m_kDBName = DBNameEdit->Text;

    FillTableNames();
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::OptionsBTNClick(TObject *Sender)
{
    if(OptionsBTN->Caption == "Options >>")
    {
        OptionsBTN->Caption = "<< Options";
        OptionsPanel->Show();

    }
    else if(OptionsBTN->Caption == "<< Options")
    {
        OptionsBTN->Caption = "Options >>";
        OptionsPanel->Hide();
    }
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::SpeedButton1Click(TObject *Sender)
{
    if(SaveDialog->Execute())
    {
        SaveToFileEdit->Text = SaveDialog->FileName;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::SaveToFileEditExit(TObject *Sender)
{
    ProgressBar1->Position = 0;
    int max = ProgressBar1->Max;
    ProgressBar1->Max = (DBRecCountSG->RowCount-2) * (DBRecCountSG->ColCount-2);
    ProgressBar1->Show();

    TStringList *pkDataSL = new TStringList;
    String kBuildStr = "";

    for(int row = 1; row < DBRecCountSG->RowCount-1; row++)
    {
        kBuildStr = m_pkDBTablesSL->Strings[row-1];

        for(int col = 1; col < DBRecCountSG->ColCount-1; col++)
        {
            kBuildStr += "," + DBRecCountSG->Cells[col][row];

            ProgressBar1->Position++;
            Application->ProcessMessages();
        }
        pkDataSL->Add(kBuildStr);
    }

    pkDataSL->SaveToFile(SaveToFileEdit->Text);
    delete pkDataSL;
    ProgressBar1->Hide();
    ProgressBar1->Max = max;
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::ClearBTNClick(TObject *Sender)
{
    DBRecCountSG->Visible = false;
    ProgressBar1->Show();
    int max = ProgressBar1->Max;
    ProgressBar1->Max = DBRecCountSG->RowCount * DBRecCountSG->ColCount;

    for(int row = 1; row < DBRecCountSG->RowCount-1; row++)
    {
        for(int col = 1; col < DBRecCountSG->ColCount-1; col++)
        {
            DBRecCountSG->Cells[col][row] = "";

            ProgressBar1->Position++;
            Application->ProcessMessages();
        }
    }

    DBRecCountSG->ColCount = 2;
    ProgressBar1->Hide();
    ProgressBar1->Max = max;
    DBRecCountSG->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TDBRecCount::LoadBTNClick(TObject *Sender)
{
    ClearBTNClick(this);

    if(OpenDialog->Execute())
    {
        LoadData(OpenDialog->FileName);
        SaveToFileEdit->Text = OpenDialog->FileName;
    }
}
//---------------------------------------------------------------------------

void TDBRecCount::LoadData(String filename)
{
    if(!FileExists(filename)) return;

    DBRecCountSG->Visible = false;

    ProgressBar1->Position = 0;
    int max = ProgressBar1->Max;
    ProgressBar1->Show();

    TStringList *pkDataSL = new TStringList;
    pkDataSL->LoadFromFile(filename);

    int cols = GetCols(pkDataSL->Strings[0]);
    ProgressBar1->Max = pkDataSL->Count * cols;
    DBRecCountSG->ColCount = cols+2;
    for(int i=0;i<cols+1;i++) DBRecCountSG->Cells[i+1][0] = i+1;

    String kBuildStr = "";

    for(int row=0; row < pkDataSL->Count; row++)
    {
        kBuildStr = pkDataSL->Strings[row];

        for(int col=0; col < cols; col++)
        {
            DBRecCountSG->Cells[col+1][row+1] = GetDataCol(kBuildStr, col+1);

            ProgressBar1->Position++;
            Application->ProcessMessages();
        }
    }

    delete pkDataSL;
    ProgressBar1->Hide();
    ProgressBar1->Max = max;

    DBRecCountSG->Visible = true;
}
// -----------------------------------------------------------------------------

int TDBRecCount::GetCols(String line)
{
    int count = 0;
    int pos = -1;

    while(line.Pos(","))
    {
        line = line.Delete(1, line.Pos(","));
        count++;

        if(count > 500)
        {
            count = -1;
            break;
        }
    }
    return count;
}
// -----------------------------------------------------------------------------

String TDBRecCount::GetDataCol(String line, int col)
{
    //delete upto the column
    for(int i=0; i<col; i++)
    {
        line.Delete(1, line.Pos(","));
    }

    //now delete every thing after it
    line.Delete(line.Pos(","), line.Length());

    return line;
}
// -----------------------------------------------------------------------------

