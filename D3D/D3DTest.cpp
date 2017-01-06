//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("D3DTest.res");
USEFORM("D3DTestSrc.cpp", D3DTestForm);
USELIB("..\..\..\mssdk\lib\Borland\dxguid.lib");
USELIB("..\..\..\mssdk\lib\Borland\ddraw.lib");
USELIB("..\..\..\mssdk\lib\Borland\d3dim.lib");
USEUNIT("..\..\..\My Documents\Programing\D3D\D3DError.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TD3DTestForm), &D3DTestForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
