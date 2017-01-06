//---------------------------------------------------------------------------
#ifndef CreateListH
#define CreateListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TListProg : public TForm
{
__published:	// IDE-managed Components
    TTreeView *Tree;
    TMainMenu *MainMenu1;
    TPopupMenu *PopupMenu1;
    TMenuItem *File3;
    TMenuItem *Exit2;
    TMenuItem *N9;
    TMenuItem *PrintSetup3;
    TMenuItem *Print3;
    TMenuItem *N10;
    TMenuItem *SaveAs3;
    TMenuItem *Save3;
    TMenuItem *Open2;
    TMenuItem *New2;
    TMenuItem *Edit2;
    TMenuItem *Replace2;
    TMenuItem *Find2;
    TMenuItem *N12;
    TMenuItem *Paste2;
    TMenuItem *Copy2;
    TMenuItem *Cut2;
    TMenuItem *N13;
    TMenuItem *Undo2;
    TMenuItem *Help1;
    TMenuItem *About1;
    TMenuItem *Paste1;
    TMenuItem *Copy1;
    TMenuItem *Cut1;
    TMenuItem *N3;
    TMenuItem *Undo1;
    TStatusBar *StatusBar1;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TPrintDialog *PrintDialog1;
    TPrinterSetupDialog *PrinterSetupDialog1;
    TFindDialog *FindDialog1;
    TReplaceDialog *ReplaceDialog1;
    TImageList *TreeImages;
    TToolBar *ToolBar1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    TSpeedButton *SpeedButton8;
    TSpeedButton *SpeedButton9;
    TSpeedButton *SpeedButton10;
    TMenuItem *N1;
    TMenuItem *Insertfile1;
    void __fastcall TreeKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    
    void __fastcall SaveAs3Click(TObject *Sender);
    void __fastcall Save3Click(TObject *Sender);
    void __fastcall PrintSetup3Click(TObject *Sender);
    void __fastcall Print3Click(TObject *Sender);
    void __fastcall Exit2Click(TObject *Sender);
    void __fastcall Open2Click(TObject *Sender);
    void __fastcall New2Click(TObject *Sender);
    
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall TreeGetImageIndex(TObject *Sender, TTreeNode *Node);
    void __fastcall TreeDragDrop(TObject *Sender, TObject *Source, int X,
          int Y);
    void __fastcall TreeDragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Cut2Click(TObject *Sender);
    void __fastcall Cut1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall SpeedButton9Click(TObject *Sender);
    void __fastcall SpeedButton10Click(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
private:	// User declarations
    typedef struct {
        String comment;
        int type;
    }NodeData;
public:		// User declarations
    __fastcall TListProg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TListProg *ListProg;
//---------------------------------------------------------------------------
#endif
