//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "aveCalc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
int numbers[6] ;
int count ;
float ave ;

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    count = 1 ;
    for(int i=0; i<6; i++)
        numbers[i] = 0 ;
    ave = 0.0 ;
}
//---------------------------------------------------------------------------

void TForm1::calcAve()
{

    for(int i=0; i<6; i++)
        ave += numbers[i] ;
    ave = ave / 6 ;
    aveEd->Text = ave ;
}

void __fastcall TForm1::addClick(TObject *Sender)
{
    int num = Edit1->Text.ToIntDef(0);
    if(num>0 && num<49)
    {
        numbers[count] = num ;
        count ++;

        calcAve();
    }

    Edit1->Clear() ;

    if(count == 6)
    {
        count == 1 ;
        aveEd->Clear() ;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::exitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
