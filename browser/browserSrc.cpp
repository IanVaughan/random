//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "browserSrc.h"
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


void __fastcall TForm1::ComboBox1Click(TObject *Sender)
{
    if(ComboBox1->Text != " ") HTML1->RequestDoc(ComboxBox1->Text);    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1KeyPress(TObject *Sender, char &Key)
{
    if(Key == VK_RETURN){
        Key = 0;
        if(ComboxBox1->Text == " ") return;
        Combox
}
//---------------------------------------------------------------------------
 