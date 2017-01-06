//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("dx_copy.res");
USEFORM("dx.cpp", Form1);
USELIB("..\..\..\..\..\mssdk\lib\Borland\dxguid.lib");
USELIB("..\..\..\..\..\mssdk\lib\Borland\ddraw.lib");
USELIB("..\..\..\..\..\mssdk\lib\Borland\d3dim.lib");
USEUNIT("..\..\..\..\..\projects\mapeditor\source\d3dutils.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
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
