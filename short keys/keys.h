//---------------------------------------------------------------------------
#ifndef keysH
#define keysH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tshortcut : public TForm
{
__published:
    TGroupBox *GroupBox1;
    TSpeedButton *a;
    TSpeedButton *b;
    TSpeedButton *c;
    TSpeedButton *d;
    TSpeedButton *e;
    TSpeedButton *f;
    TSpeedButton *g;
    TSpeedButton *h;
    TSpeedButton *i;
    TSpeedButton *j;
    TSpeedButton *k;
    TSpeedButton *l;
    TSpeedButton *m;
    TSpeedButton *n;
    TSpeedButton *o;
    TSpeedButton *p;
    TSpeedButton *q;
    TSpeedButton *r;
    TSpeedButton *s;
    TSpeedButton *t;
    TSpeedButton *u;
    TSpeedButton *v;
    TSpeedButton *w;
    TSpeedButton *x;
    TSpeedButton *y;
    TSpeedButton *z;

    TSpeedButton *resetAllButton;
    TSpeedButton *closeButton;
    TSpeedButton *resetRedButton;
    TSpeedButton *onTopButton;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall closeButtonClick(TObject *Sender);
    void __fastcall resetAllButtonClick(TObject *Sender);

    void __fastcall resetRedButtonClick(TObject *Sender);
    void __fastcall onTopButtonClick(TObject *Sender);
private:
    bool __fastcall Up(TSpeedButton* btn);
    bool __fastcall Down(TSpeedButton* btn);

public:
    __fastcall Tshortcut(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tshortcut *shortcut;
//---------------------------------------------------------------------------
#endif
