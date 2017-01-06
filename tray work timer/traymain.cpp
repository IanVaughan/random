#include <vcl.h>
#include <shellapi.h>
#pragma hdrstop

#include "traymain.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TWorkTimer *WorkTimer;

//---------------------------------------------------------------------------
__fastcall TWorkTimer::TWorkTimer(TComponent* Owner)
  : TForm(Owner)
{
    Height = 147;
}
//---------------------------------------------------------------------------

int s,m,h;
void __fastcall TWorkTimer::FormCreate(TObject *Sender)
{
    s=0;
    m=0;
    h=0;

	TrayMessage(NIM_ADD);
    TrayMessage(NIM_MODIFY);
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::FormDestroy(TObject *Sender)
{
	TrayMessage(NIM_DELETE);
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::DrawItem(TMessage& Msg)
{
     IconDrawItem((LPDRAWITEMSTRUCT)Msg.LParam);
     TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::MyNotify(TMessage& Msg)
{
    POINT MousePos;

    switch(Msg.LParam)
    {
        case WM_RBUTTONUP:
            if (GetCursorPos(&MousePos))
            {
                PopupMenu1->PopupComponent = WorkTimer;
                SetForegroundWindow(Handle);
                PopupMenu1->Popup(MousePos.x, MousePos.y);
            }
            else
                Show();
            break;
        case WM_LBUTTONUP:
            break;
        default:
            break;
    }
    TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::hideClick(TObject *Sender)
{
    Hide();
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::pauseClick(TObject *Sender)
{
    if(pause->Caption == "Pause")
    {
        lunchClick(this);
        pause->Caption = "Continue";
    }
    else
    {
        workingClick(this);
        pause->Caption = "Pause";
    }
}
//---------------------------------------------------------------------------


//******************************************************************************
//* SysTray stuff

bool __fastcall TWorkTimer::TrayMessage(DWORD dwMessage)
{
    NOTIFYICONDATA tnd;
    PSTR pszTip;

    pszTip = TipText();

    tnd.cbSize          = sizeof(NOTIFYICONDATA);
    tnd.hWnd            = Handle;
    tnd.uID             = IDC_MYICON;
    tnd.uFlags          = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    tnd.uCallbackMessage	= MYWM_NOTIFY;

    if (dwMessage == NIM_MODIFY)
    {
        tnd.hIcon		= IconHandle();
        if (pszTip)
           lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
	    else
        tnd.szTip[0] = '\0';
    }
    else
    {
        tnd.hIcon = NULL;
        tnd.szTip[0] = '\0';
    }

    return (Shell_NotifyIcon(dwMessage, &tnd));
}
//---------------------------------------------------------------------------

HANDLE __fastcall TWorkTimer::IconHandle(void)
{
    return (Image1->Picture->Icon->Handle);
}
//---------------------------------------------------------------------------

PSTR __fastcall TWorkTimer::TipText(void)
{
    return ("Work Timer");
}
//---------------------------------------------------------------------------

LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi)
{
	HICON hIcon;

	hIcon = (HICON)LoadImage(g_hinst, MAKEINTRESOURCE(lpdi->CtlID), IMAGE_ICON,
		16, 16, 0);
	if (!hIcon)
		return(FALSE);

	DrawIconEx(lpdi->hDC, lpdi->rcItem.left, lpdi->rcItem.top, hIcon,
		16, 16, 0, NULL, DI_NORMAL);

	return(TRUE);
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::workingClick(TObject *Sender)
{
    Timer1->Enabled = true;
    working->Checked = true ;
    lunch->Checked = false ;
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::lunchClick(TObject *Sender)
{
    Timer1->Enabled = false;

    working->Checked = false ;
    lunch->Checked = true ;
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::Properties1Click(TObject *Sender)
{
    Show();
}
//---------------------------------------------------------------------------

void __fastcall TWorkTimer::Shutdown1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

//******************************************************************************
//* Timer events

void __fastcall TWorkTimer::Timer1Timer(TObject *Sender)
{
    //clock
    s++;
    if(s>59)
    {
        s=0;
        m++;
    }
    if(m>59)
    {
        m=0;
        h++;
    }

    //convert
    String hStr = (String)h;
    String mStr = (String)m;
    String sStr = (String)s;

    //test for preciding zero
    if(h<9) hStr = "0"+hStr;
    if(m<9) mStr = "0"+mStr;
    if(s<9) sStr = "0"+sStr;

    //display
    todayL->Caption = hStr + ":" + mStr + ":" + sStr;
}
//---------------------------------------------------------------------------




