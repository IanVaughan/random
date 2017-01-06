//---------------------------------------------------------------------------
#ifndef DisplayStripH
#define DisplayStripH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TDisplayStripForm : public TForm
{
__published:	// IDE-managed Components
    void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations
    enum whereOut {TO_SCR, TO_PRN} ;
    bool __fastcall createStrip(AnsiString, TStringList*, whereOut);

public:		// User declarations
    __fastcall TDisplayStripForm(TComponent* Owner);

     //call getFormats to return all avabile formats in the gived file
     //in : the fileName
     AnsiString __fastcall getFormats(AnsiString);
     // call these methods to either display on screen or print to printer
     //createStrip & printStrip
     // in : AnsiString stripName - the strip format to use
     //    : TStringList *data - a list of items to be displayed (eg "CS,BAW321" will put BAW321 where CS is defined)
     bool __fastcall showStrip(AnsiString, TStringList*);
     bool __fastcall printStrip(AnsiString, TStringList*);
};
//---------------------------------------------------------------------------
extern PACKAGE TDisplayStripForm *DisplayStripForm;
//---------------------------------------------------------------------------
#endif
 