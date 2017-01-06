//---------------------------------------------------------------------------
#ifndef ClipPadSrcH
#define ClipPadSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TClipPad : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
private:	// User declarations
public:		// User declarations
    __fastcall TClipPad(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClipPad *ClipPad;
//---------------------------------------------------------------------------
#endif
