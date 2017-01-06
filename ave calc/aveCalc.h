//---------------------------------------------------------------------------
#ifndef aveCalcH
#define aveCalcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TEdit *Edit1;
    TButton *add;
    TEdit *aveEd;
    TButton *exit;
    TBitBtn *BitBtn1;
    TSpeedButton *SpeedButton1;
    void __fastcall addClick(TObject *Sender);
    void __fastcall exitClick(TObject *Sender);
private:	// User declarations
    void calcAve();
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
