//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef traymainH
#define traymainH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#define MYWM_NOTIFY         (WM_APP+100)
#define IDC_MYICON                     1006
extern HINSTANCE g_hinst;
LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi);
//---------------------------------------------------------------------------
class TWorkTimer : public TForm
{
__published:
    TImage *Image1;
    TImage *Image2;
    TPopupMenu *PopupMenu1;
    TMenuItem *Properties1;
    TMenuItem *lunch;
    TMenuItem *Shutdown1;
    TMenuItem *N1;
    TMenuItem *N2;
    TTimer *Timer1;
    TLabel *startTimeTextL;
    TMenuItem *working;
    TLabel *todayL;
    TLabel *startTimeL;
    TSpeedButton *hide;
    TSpeedButton *pause;
    TSpeedButton *showWeek;
    TStaticText *todaySTL;
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Properties1Click(TObject *Sender);
    void __fastcall lunchClick(TObject *Sender);
    void __fastcall Shutdown1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall workingClick(TObject *Sender);

    void __fastcall hideClick(TObject *Sender);
    void __fastcall pauseClick(TObject *Sender);
private:
    void __fastcall DrawItem(TMessage& Msg);
    void __fastcall MyNotify(TMessage& Msg);
    bool __fastcall TrayMessage(DWORD dwMessage);
    HANDLE __fastcall IconHandle(void);
    PSTR __fastcall TipText(void);

public:
    virtual __fastcall TWorkTimer(TComponent* Owner);

    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_DRAWITEM,TMessage,DrawItem)
        MESSAGE_HANDLER(MYWM_NOTIFY,TMessage,MyNotify)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern TWorkTimer *WorkTimer;
//---------------------------------------------------------------------------
#endif
