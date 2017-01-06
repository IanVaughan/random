//---------------------------------------------------------------------------
#ifndef testRunnerH
#define testRunnerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TtestRun : public TForm
{
__published:	// IDE-managed Components
    TButton *gvpeBTN;
    TButton *gveBTN;
    TButton *CloseBTN;
    void __fastcall CloseBTNClick(TObject *Sender);
    void __fastcall gvpeBTNClick(TObject *Sender);
    void __fastcall gveBTNClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TtestRun(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TtestRun *testRun;
//---------------------------------------------------------------------------
#endif
