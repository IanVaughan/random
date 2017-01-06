//---------------------------------------------------------------------------
#ifndef myH
#define myH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TCSpinEdit *CSpinEdit1;
    TLabel *Label1;
    TLabel *Label2;
    TCSpinEdit *CSpinEdit2;
private:	// User declarations
public:		// User declarations
    __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
