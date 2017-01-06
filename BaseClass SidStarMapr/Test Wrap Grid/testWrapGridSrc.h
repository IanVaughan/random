//---------------------------------------------------------------------------
#ifndef testWrapGridSrcH
#define testWrapGridSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WrapGrid.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TtestWrapGrid : public TForm
{
__published:	// IDE-managed Components
    TWrapGrid *WrapGrid1;
    TStatusBar *StatusBar1;
    TToolBar *ToolBar1;
    TMainMenu *MainMenu1;
    TPopupMenu *PopupMenu1;
    TMenuItem *File1;
    TMenuItem *Exit1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TPanel *Panel1;
    TButton *Button1;
    TEdit *Edit1;
    TButton *Button2;
private:	// User declarations
public:		// User declarations
    __fastcall TtestWrapGrid(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TtestWrapGrid *testWrapGrid;
//---------------------------------------------------------------------------
#endif
