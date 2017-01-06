//notes:-
//check files not read-only

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "my1.h"
#include "working.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma link "cspin"
#pragma resource "*.dfm"
Tstart *start;
String filename ;
//---------------------------------------------------------------------------
__fastcall Tstart::Tstart(TComponent* Owner) : TForm(Owner)
{
}
// -----------------------------------------------------------------------------

void __fastcall Tstart::BitBtn2Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall Tstart::goClick(TObject *Sender)
{
    Hide();
    work->Show();
    work->Hide();
    Show();
}
//---------------------------------------------------------------------------

void __fastcall Tstart::FileListBox1DblClick(TObject *Sender)
{
    goClick(NULL);
}
//---------------------------------------------------------------------------





