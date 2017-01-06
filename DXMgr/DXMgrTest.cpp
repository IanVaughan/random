//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DXMgrTest.res");
USEFORM("dxTest.cpp", dxTestForm);
USELIB("Dxmgr.lib");
USEFILE("Dxmgr.h");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TdxTestForm), &dxTestForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
