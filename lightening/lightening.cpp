//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("lightening.res");
USEFORM("light1.cpp", Light);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TLight), &Light);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
