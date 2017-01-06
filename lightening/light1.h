//---------------------------------------------------------------------------
#ifndef light1H
#define light1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TLight : public TForm
{
__published:	// IDE-managed Components
    void __fastcall FormShow(TObject *Sender);
    
    void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TLight(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLight *Light;
//---------------------------------------------------------------------------
#endif
