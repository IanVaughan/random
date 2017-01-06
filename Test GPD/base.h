//---------------------------------------------------------------------------
#ifndef baseH
#define baseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	

    TListBox *airPerfLB;
    TListBox *vehLB;
    TButton *Button1;
    TListBox *gndPerfLB;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall vehLBClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    
private:

public:		
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
