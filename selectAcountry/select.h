//---------------------------------------------------------------------------
#ifndef selectH
#define selectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <checklst.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TTreeView *TreeView1;
    TCheckListBox *CheckListBox1;
    TListBox *ListBox1;
    TImageList *ImageList1;
    TComboBox *ComboBox1;
    TListView *ListView1;
    TBitBtn *BitBtn1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ComboBox1Click(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall ListBox1DrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
    void __fastcall ComboBox1DrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
