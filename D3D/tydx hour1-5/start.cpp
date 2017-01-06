//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("start.res");
USEFORM("D3DSrc.cpp", D3D);
USELIB("..\..\..\..\mssdk\lib\Borland\dxguid.lib");
USELIB("..\..\..\..\mssdk\lib\Borland\ddraw.lib");
USELIB("..\..\..\..\mssdk\lib\Borland\d3dim.lib");
USEUNIT("..\..\..\..\My Documents\Programing\D3D\tydx hour1-5\d3dutil.cpp");
USEUNIT("..\..\..\..\My Documents\Programing\D3D\tydx hour1-5\Cube.cpp");
USEUNIT("..\..\..\..\My Documents\Programing\D3D\tydx hour1-5\D3DError.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TD3D), &D3D);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
