//---------------------------------------------------------------------------
#ifndef RecCountH
#define RecCountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <DBTables.hpp>
#include <Db.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TDBRecCount : public TForm
{
__published:
    TStringGrid *DBRecCountSG;
    TPanel *Panel1;
    TBitBtn *GoBTN;
    TBitBtn *CloseBTN;
    TDatabase *BestDB;
    TProgressBar *ProgressBar1;
    TPanel *OptionsPanel;
    TButton *OptionsBTN;
    TSaveDialog *SaveDialog;
    TGroupBox *GroupBox1;
    TButton *ClearBTN;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *DBNameEdit;
    TEdit *SaveToFileEdit;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton1;
    TButton *LoadBTN;
    TOpenDialog *OpenDialog;
    TLabel *Label3;
    void __fastcall CloseBTNClick(TObject *Sender);
    void __fastcall GoBTNClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall DBNameEditExit(TObject *Sender);
    void __fastcall OptionsBTNClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SaveToFileEditExit(TObject *Sender);
    void __fastcall ClearBTNClick(TObject *Sender);
    void __fastcall LoadBTNClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

private:
    TStringList *m_pkDBTablesSL;
    String m_kDBName;

    void FillTableNames();
    void GetTableNames(TStringList *&);
    void PopulateFieldNames(String kTableName);

    void Count();
    void GetFieldData(String kTableName, int nRow);

    void LoadData(String);
    int GetCols(String line);
    String GetDataCol(String line, int col);

public:
    __fastcall TDBRecCount(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDBRecCount *DBRecCount;
//---------------------------------------------------------------------------
#endif
