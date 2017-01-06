//---------------------------------------------------------------------------
#ifndef addItemH
#define addItemH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TaddItemForm : public TForm
{
__published:	// IDE-managed Components
    TEdit *itemName;
    TRadioButton *cat;
    TRadioButton *Item;
    TLabel *Label1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TaddItemForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TaddItemForm *addItemForm;
//---------------------------------------------------------------------------
#endif
