//---------------------------------------------------------------------------
#ifndef extactMsgBoxTextSrcH
#define extactMsgBoxTextSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include "cgauges.h"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <Tabs.hpp>
#include "WrapGrid.h"
//---------------------------------------------------------------------------
class TextractMsgTextForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Exit1;
    TStatusBar *StatusBar1;
    TToolBar *ToolBar1;
    TMenuItem *ExtractSingleFile1;
    TMenuItem *ExtractMultiableFiles1;
    TMenuItem *N1;
    TPanel *Panel1;
    TOpenDialog *OpenDialog1;
    TPanel *fileNameP;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TTabSet *TabSet1;
    TProgressBar *ProgressBar1;
    TWrapGrid *WrapGrid1;
    void __fastcall ExtractSingleFile1Click(TObject *Sender);
    void __fastcall ExtractMultiableFiles1Click(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    
private:	// User declarations
    void ConvertFiles(TStrings *);
public:		// User declarations
    __fastcall TextractMsgTextForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TextractMsgTextForm *extractMsgTextForm;
//---------------------------------------------------------------------------
#endif
