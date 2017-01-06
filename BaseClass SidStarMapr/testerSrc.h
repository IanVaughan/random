//---------------------------------------------------------------------------
#ifndef testerSrcH
#define testerSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Ttest : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TSpeedButton *sidB;
    TSpeedButton *starB;
    TSpeedButton *mapcB;
    TPanel *Panel1;
    TSpeedButton *close;
    void __fastcall sidBClick(TObject *Sender);
    void __fastcall starBClick(TObject *Sender);
    void __fastcall mapcBClick(TObject *Sender);
    void __fastcall closeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall Ttest(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Ttest *test;
//---------------------------------------------------------------------------
#endif
