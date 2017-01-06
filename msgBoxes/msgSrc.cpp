//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "msgSrc.h"
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
    Application->MessageBox("MB_ABORTRETRYIGNORE\nMB_ICONEXCLAMATION","1/8",MB_ABORTRETRYIGNORE|MB_ICONEXCLAMATION);
    Application->MessageBox("MB_OK\nMB_ICONWARNING","2/8",MB_OK|MB_ICONWARNING);
    Application->MessageBox("MB_OKCANCEL\nMB_ICONINFORMATION","3/8",MB_OKCANCEL|MB_ICONINFORMATION);
    Application->MessageBox("MB_RETRYCANCEL\nMB_ICONASTERISK","4/8",MB_RETRYCANCEL|MB_ICONASTERISK);
    Application->MessageBox("MB_YESNO\nMB_ICONQUESTION","5/8",MB_YESNO|MB_ICONQUESTION);
    Application->MessageBox("MB_YESNOCANCEL\nMB_ICONSTOP","6/8",MB_YESNOCANCEL|MB_ICONSTOP);
    Application->MessageBox("MB_OK\nMB_ICONERROR","7/8",MB_OK|MB_ICONERROR);
    Application->MessageBox("MB_OK\nMB_ICONHAND","8/8",MB_OK|MB_ICONHAND);
    Close();
}
//---------------------------------------------------------------------------
/*
MB_ABORTRETRYIGNORE
MB_OK
MB_OKCANCEL
MB_RETRYCANCEL
MB_YESNO
MB_YESNOCANCEL

MB_ICONEXCLAMATION
MB_ICONWARNING
MB_ICONINFORMATION
MB_ICONASTERISK
MB_ICONQUESTION
MB_ICONSTOP
MB_ICONERROR
MB_ICONHAND
*/
