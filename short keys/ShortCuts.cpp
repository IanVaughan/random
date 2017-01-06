//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ShortCuts.res");
USEFORM("keys.cpp", shortcut);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(Tshortcut), &shortcut);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
