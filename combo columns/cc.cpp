//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "cc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
    TStringList *strList1 = new TStringList;
    strList1->Add("HSBC");
    strList1->Add("BBC");
    strList1->Add("1");
    strList1->Add("Long Line");

    TStringList *strList2 = new TStringList;
    strList2->Add("end");
    strList2->Add("of");
    strList2->Add("the");
    strList2->Add("line");

    //loop all of the items in the string list
    for(int i=0; i<strList1->Count; i++)
    {
       	int t = Canvas->TextWidth(strList1->Strings[i]);

        String line = strList1->Strings[i] ;
        //add spaces
        while(Canvas->TextWidth(line) < 80)
            line += " ";

        //build the line
        line += strList2->Strings[i] ;

        //add it to the combo box
        cb->Items->Add(line);
    }
}
//---------------------------------------------------------------------------
