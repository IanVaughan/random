//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "testerSrc.h"
#include "Sid.h"
#include "Star.h"
#include "Mapr.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Ttest *test;
//---------------------------------------------------------------------------
__fastcall Ttest::Ttest(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Ttest::sidBClick(TObject *Sender)
{
    Sid* sid = new Sid(this);
    if(sid->Execute())
    {
        sidB->Glyph->LoadFromFile("C:\\Program Files\\Common Files\\Borland Shared\\Images\\Buttons\\check.bmp");
    }
    else
    {
        sidB->Glyph->LoadFromFile("C:\\Program Files\\Common Files\\Borland Shared\\Images\\Buttons\\ignore.bmp");
    }
    delete sid ;
}
//---------------------------------------------------------------------------

void __fastcall Ttest::starBClick(TObject *Sender)
{
    Star *star = new Star(this) ;
    if(star->Execute())
    {
        starB->Glyph->LoadFromFile("C:\\Program Files\\Common Files\\Borland Shared\\Images\\Buttons\\check.bmp");
    }
    else
    {
        starB->Glyph->LoadFromFile("C:\\Program Files\\Common Files\\Borland Shared\\Images\\Buttons\\ignore.bmp");
    }
    delete star ;
}
//---------------------------------------------------------------------------

void __fastcall Ttest::mapcBClick(TObject *Sender)
{
    Mapr *mapr = new Mapr(this) ;
    if(mapr->Execute())
    {
        mapcB->Glyph->LoadFromFile("C:\\Program Files\\Common Files\\Borland Shared\\Images\\Buttons\\check.bmp");
    }
    else
    {
        mapcB->Glyph->LoadFromFile("C:\\Program Files\\Common Files\\Borland Shared\\Images\\Buttons\\ignore.bmp");
    }
    delete mapr ;
}
//---------------------------------------------------------------------------

void __fastcall Ttest::closeClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
