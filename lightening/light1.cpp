//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "light1.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLight *Light;
    int cenX;// = Light->Width/2 ;
    int cenY;// = Light->Height/2 ;

//---------------------------------------------------------------------------
__fastcall TLight::TLight(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

int degX(int deg)
{
//    int rad = DegToRad(deg);
    int rad = 0;
    if(deg<180)
        rad = cenX+ deg;
    else
        rad = cenX- deg ;
    return rad ;
}

int degY(int deg)
{
//    int rad = DegToRad(deg);
    int rad = 0;
    if(deg<180)
        rad = cenY- deg;
    else
        rad = cenY+ deg ;
    return rad ;
}

void line(int x, int y)
{
//    Light->Canvas->Brush->Color = clBlue;
    Light->Canvas->MoveTo(cenX, cenY);
    Light->Canvas->LineTo(x,y);
}

void __fastcall TLight::FormShow(TObject *Sender)
{
//    Canvas->Brush->Color = clBlack;
//    Canvas->Ellipse(0,0,Light->Width,Light->Height);
    cenX = Light->Width/2 ;
    cenY = Light->Height/2 ;

//    bool loopEnd = false ;
//    while(loopEnd) {
//        line(degX(2), degY(2));
//    }

    for(int i=0;i<360;i++)
        line(degX(i), degY(i));
}
//---------------------------------------------------------------------------
void __fastcall TLight::FormResize(TObject *Sender)
{
    cenX = Light->Width/2 ;
    cenY = Light->Height/2 ;
//    Canvas->Brush->Color = clBlack;
//    Canvas->Ellipse(0,0,Light->Width,Light->Height);
}
//---------------------------------------------------------------------------
