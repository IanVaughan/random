//---------------------------------------------------------------------------
#ifndef workingH
#define workingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cgauges.h"
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Twork : public TForm
{
__published:
    TProgressBar *ProgressBar1;
    TCGauge *gau;
    TBitBtn *stopBTN;
    TBevel *Bevel1;
    TLabel *Label1;
    TLabel *from;
    TLabel *Label3;
    TLabel *to;
    TLabel *Label5;
    TLabel *filenameLabel;
    TAnimate *Animate1;
    TBitBtn *again;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall stopBTNClick(TObject *Sender);
    void __fastcall againClick(TObject *Sender);

private:
    void Do(String filename);
    String CheckLine(String aline, int dent);
    void CheckLength(TStringList*, int);
    bool InString(String testSt, int pos);
    bool SplitableChar(char ch);
    bool InComment(String line, int pos);

public:
    void Run();
    __fastcall Twork(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Twork *work;
//---------------------------------------------------------------------------
#endif
