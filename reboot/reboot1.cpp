//---------------------------------------------------------------------------
#include <vcl.h>
#include <shellapi.h>
#pragma hdrstop

#include "reboot1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Logoff1Click(TObject *Sender)
{
//    UINT flags = EWX_LOGOFF;
    ExitWindowsEx(EWX_LOGOFF ,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Reboot1Click(TObject *Sender)
{
    ExitWindowsEx(EWX_REBOOT ,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Shutdown1Click(TObject *Sender)
{
    ExitWindowsEx(EWX_SHUTDOWN,0);
}
//---------------------------------------------------------------------------

void TForm1::AddTrayIcon()
{
    NOTIFYICONDATA icondata;
    memset (&icondata, 0, sizeof(icondata));
    icondata.cbSize = sizeof (icondata);

    icondata.hWnd = Handle ;
    strncpy (icondata.szTip, "Reboot", sizeof(icondata.szTip));
    icondata.hIcon = Application->Icon->Handle ;
    icondata.uCallbackMessage = iconmessage;
    icondata.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP ;
    Shell_NotifyIcon(NIM_ADD, &icondata);
}

void TForm1::RemoveTrayIcon()
{
    NOTIFYICONDATA icondata;
    memset(&icondata, 0, sizeof(icondata));
    icondata.cbSize = sizeof(icondata);

    icondata.hWnd = Handle ;
    Shell_NotifyIcon(NIM_DELETE, &icondata);
}

void __fastcall TForm1::WndProc(Messages::TMessage &Message)
{
    if(Message.Msg == iconmessage)
    {
      if(Message.LParam == WM_LBUTTONDBLCLK)
      {
            Show();
      }
      if(Message.LParam == WM_RBUTTONDOWN)
      {
          PopupMenu1->Popup(1,1);
      }
      return;
    }
    TForm::WndProc(Message);
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    iconmessage = RegisterWindowMessage("IconNotify");
    AddTrayIcon();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    RemoveTrayIcon();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Hide();
}
//---------------------------------------------------------------------------
