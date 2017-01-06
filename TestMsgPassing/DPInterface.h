//---------------------------------------------------------------------------
#ifndef DPInterfaceH
#define DPInterfaceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TDPInterface : public TForm
{
__published:
    TButton *Button1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    void __fastcall Button1Click(TObject *Sender);

private:

public:
    __fastcall TDPInterface(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TDPInterface *DPInterface;
//---------------------------------------------------------------------------
#endif
