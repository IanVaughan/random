//---------------------------------------------------------------------------
#ifndef DeleteFormSrcH
#define DeleteFormSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TDeleteForm : public TForm
{
__published:
    TEdit *Edit1;
    TSpeedButton *DirBTN;
    TOpenDialog *OpenDialog1;
    TBitBtn *CloseBTN;
    TBitBtn *DeleteBTN;
    TLabel *Label1;
    TLabel *Label2;
    void __fastcall DirBTNClick(TObject *Sender);
    void __fastcall CloseBTNClick(TObject *Sender);

    void __fastcall DeleteBTNClick(TObject *Sender);
private:
    void DeleteFiles(String kPathDir);
    
public:	
    __fastcall TDeleteForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDeleteForm *DeleteForm;
//---------------------------------------------------------------------------
#endif
