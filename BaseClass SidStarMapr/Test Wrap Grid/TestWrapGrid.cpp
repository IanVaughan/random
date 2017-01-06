//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("TestWrapGrid.res");
USEFORM("testWrapGridSrc.cpp", testWrapGrid);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TtestWrapGrid), &testWrapGrid);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
