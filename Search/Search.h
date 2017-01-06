//---------------------------------------------------------------------------
#ifndef SearchH
#define SearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TSearchForm : public TForm
{
__published:
    TStringGrid *StringGrid1;
    TPanel *Panel1;
    TCheckBox *faAnyFileCB;
    TEdit *Edit1;
    TGroupBox *FileAttribsGB;
    TCheckBox *faReadOnlyCB;
    TCheckBox *faHiddenCB;
    TCheckBox *faSysFileCB;
    TCheckBox *faVolumeIDCB;
    TCheckBox *faDirectoryCB;
    TCheckBox *faArchiveCB;
    TBitBtn *SearchBTN;
    TSpeedButton *SpeedButton1;
    TOpenDialog *OpenDialog;
    void __fastcall faAnyFileCBClick(TObject *Sender);
    void __fastcall SearchBTNClick(TObject *Sender);

    void __fastcall SpeedButton1Click(TObject *Sender);
private:

public:
    __fastcall TSearchForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSearchForm *SearchForm;
//---------------------------------------------------------------------------
#endif
