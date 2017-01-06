//---------------------------------------------------------------------------
#ifndef SIDsrcH
#define SIDsrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TSIDform : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *Panel;
    TLabel *NameLabel;
    TLabel *MinimumAltLabel;
    TLabel *MaximumAltLabel;
    TDBEdit *NameDBEdit;
    TDBEdit *MinAltDBEdit;
    TDBEdit *MaxAltDBEdit;
    TPopupMenu *StartPopupMenu;
    TMenuItem *Add;
    TMenuItem *Edit;
    TMenuItem *Delete;
    TButton *cancelBTN;
    TButton *saveBTN;
    TGroupBox *GroupBox1;
    TLabel *StartRouteLabel;
    TLabel *Label1;
    TLabel *Label3;
    TListBox *ListBox1;
    TListBox *ListBox2;
    TListBox *ListBox3;
    TLabel *RunwayTransitionLabel;
    TComboBox *StartComboBox;
    TButton *Button1;
    TButton *Button2;
    TComboBox *EndComboBox;
    TLabel *StartTransLabel;
    TButton *NewEndBtn;
    TButton *DeleteEndBtn;
    TButton *EditEndBtn;
    TButton *EndDownBtn;
    TButton *EndUpBtn;
    TButton *CommonDownBtn;
    TButton *CommonUpBtn;
    TButton *StartDownBtn;
    TButton *StartUpBtn;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall cancelBTNClick(TObject *Sender);
    void __fastcall saveBTNClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TSIDform(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSIDform *SIDform;
//---------------------------------------------------------------------------
#endif
