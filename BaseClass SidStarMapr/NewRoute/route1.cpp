//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "route1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WrapGrid"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------


/*Fix to Fix
Direct to Fix
Course to Fix
Course from Fix
Course to Fly
Course to Intercept Radial
Hold at Fix
Hold at Fix for N Orbits
Fly DME Arc
*/

void __fastcall TForm1::fixtoFixRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Fix to Fix" ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::directToFixRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Direct to Fix" ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::courseToFixRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Course to Fix" ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::courseFromFixRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Course from Fix";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::courseToFlyRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Course to Fly" ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::courseToInterceptRadialRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Course to Intercept Radial" ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::holdAtFixRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Hold at Fix";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::holdAtFixForNOrbitsRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Hold at Fix for N Orbits" ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::flyDMEArcRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Fly DME Arc" ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::courseFromRunwayRBClick(TObject *Sender)
{
    dataNB->ActivePage = "Course from Runway";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::addBTNClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cancelBTNClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
    RichEdit1->Lines->Clear();
    RichEdit1->Lines->Add("Fly radial 010 to ALTO with cleared level of F100. Until at the end of the day to find out if this wraps!");
    int pos = RichEdit1->Lines->Text.Pos("010");
    int space = RichEdit1->Lines->Text.Pos(" ");
    RichEdit1->SelStart = pos-1 ;
    RichEdit1->SelLength = 3 ;
    RichEdit1->SelAttributes->Color = clRed ;
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsBold << fsUnderline ;
    RichEdit1->SelLength = 0;

}
//---------------------------------------------------------------------------



