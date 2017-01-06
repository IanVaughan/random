//---------------------------------------------------------------------------
#ifndef filterH
#define filterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfilterForm : public TForm
{
__published:	// IDE-managed Components
    TDatabase *Database1;
    TQuery *Query1;
    TDBGrid *DBGrid1;
    TDataSource *DataSource1;
    TPanel *Panel1;
    TSpeedButton *go;
    TEdit *Edit1;
    TLabel *Label1;
    TSpeedButton *param;
    TLabel *Label2;
    TEdit *paramEdit;
    void __fastcall goClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Edit1Change(TObject *Sender);
    void __fastcall paramClick(TObject *Sender);
    void __fastcall paramEditChange(TObject *Sender);
    void __fastcall paramEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
    __fastcall TfilterForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfilterForm *filterForm;
//---------------------------------------------------------------------------
#endif
