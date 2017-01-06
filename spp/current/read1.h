//---------------------------------------------------------------------------
#ifndef read1H
#define read1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "cspin.h"
#include <Menus.hpp>
#include <OleCtrls.hpp>
#include <vcf1.hpp>
//---------------------------------------------------------------------------
class TreadForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TComboBox *ComboBox1;
    TSpeedButton *print;
    TPrintDialog *PrintDialog1;
     TSpeedButton *screen;
    void __fastcall printClick(TObject *Sender);
    void __fastcall screenClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TreadForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TreadForm *readForm;
//---------------------------------------------------------------------------
#endif
   