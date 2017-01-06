//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "keys.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tshortcut *shortcut;
//---------------------------------------------------------------------------
__fastcall Tshortcut::Tshortcut(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Tshortcut::closeButtonClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall Tshortcut::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    switch(UpCase((Char)Key))
    {
        case 'A' : Down(a) ; break;
        case 'B' : Down(b) ; break;
        case 'C' : Down(c) ; break;
        case 'D' : Down(d) ; break;
        case 'E' : Down(e) ; break;
        case 'F' : Down(f) ; break;
        case 'G' : Down(g) ; break;
        case 'H' : Down(h) ; break;
        case 'I' : Down(i) ; break;
        case 'J' : Down(j) ; break;
        case 'K' : Down(k) ; break;
        case 'L' : Down(l) ; break;
        case 'M' : Down(m) ; break;
        case 'N' : Down(n) ; break;
        case 'O' : Down(o) ; break;
        case 'P' : Down(p) ; break;
        case 'Q' : Down(q) ; break;
        case 'R' : Down(r) ; break;
        case 'S' : Down(s) ; break;
        case 'T' : Down(t) ; break;
        case 'U' : Down(u) ; break;
        case 'V' : Down(v) ; break;
        case 'W' : Down(w) ; break;
        case 'X' : Down(x) ; break;
        case 'Y' : Down(y) ; break;
        case 'Z' : Down(z) ; break;
    }
}
//---------------------------------------------------------------------------

bool __fastcall Tshortcut::Down(TSpeedButton* btn)
{
    if(btn->Down)
        btn->Font->Color = clRed;
    btn->Down = true;
    return btn->Down;
}
// -----------------------------------------------------------------------------

bool __fastcall Tshortcut::Up(TSpeedButton* btn)
{
    btn->Font->Color = clWindowText;
    btn->Down = false;
    return btn->Down;
}
// -----------------------------------------------------------------------------

void __fastcall Tshortcut::resetAllButtonClick(TObject *Sender)
{
    Up(a);
    Up(b);
    Up(c);
    Up(d);
    Up(e);
    Up(f);
    Up(g);
    Up(h);
    Up(i);
    Up(j);
    Up(k);
    Up(l);
    Up(m);
    Up(n);
    Up(o);
    Up(p);
    Up(q);
    Up(r);
    Up(s);
    Up(t);
    Up(u);
    Up(v);
    Up(w);
    Up(x);
    Up(y);
    Up(z);
}
//---------------------------------------------------------------------------

void __fastcall Tshortcut::resetRedButtonClick(TObject *Sender)
{
    a->Font->Color = clWindowText;
    b->Font->Color = clWindowText;
    c->Font->Color = clWindowText;
    d->Font->Color = clWindowText;
    e->Font->Color = clWindowText;
    f->Font->Color = clWindowText;
    g->Font->Color = clWindowText;
    h->Font->Color = clWindowText;
    i->Font->Color = clWindowText;
    j->Font->Color = clWindowText;
    k->Font->Color = clWindowText;
    l->Font->Color = clWindowText;
    m->Font->Color = clWindowText;
    n->Font->Color = clWindowText;
    o->Font->Color = clWindowText;
    p->Font->Color = clWindowText;
    q->Font->Color = clWindowText;
    r->Font->Color = clWindowText;
    s->Font->Color = clWindowText;
    t->Font->Color = clWindowText;
    u->Font->Color = clWindowText;
    v->Font->Color = clWindowText;
    w->Font->Color = clWindowText;
    x->Font->Color = clWindowText;
    y->Font->Color = clWindowText;
    z->Font->Color = clWindowText;
}
//---------------------------------------------------------------------------

void __fastcall Tshortcut::onTopButtonClick(TObject *Sender)
{
    if(onTopButton->Down)
        FormStyle = fsStayOnTop;
    else
        FormStyle = fsNormal;
}
//---------------------------------------------------------------------------

