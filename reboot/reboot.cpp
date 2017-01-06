//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("reboot.res");
USEFORM("reboot1.cpp", Form1);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        ShowWindow(Application->Handle, SW_HIDE);
        Application->ShowMainForm = false ;
        Application->CreateForm(__classid(TForm1), &Form1);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
