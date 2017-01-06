#include <vcl.h>
#pragma hdrstop
HINSTANCE g_hinst;
//---------------------------------------------------------------------------
USEFORM("traymain.cpp", WorkTimer);
USERES("trayicon.res");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE hInstance, LPSTR, int)
{
    Application->Initialize();
    g_hinst = hInstance;
    Application->Title = "Work Timer";
        Application->CreateForm(__classid(TWorkTimer), &WorkTimer);
        Application->Run();

    return 0;
}
//---------------------------------------------------------------------------

