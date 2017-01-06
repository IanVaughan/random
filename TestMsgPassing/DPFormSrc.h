//---------------------------------------------------------------------------
#ifndef DPFormSrcH
#define DPFormSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TDPForm : public TForm
{
__published:
    TButton *Button1;
    TLabel *Label1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);

private:

public:
    __fastcall TDPForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDPForm *DPForm;
//---------------------------------------------------------------------------
#endif
