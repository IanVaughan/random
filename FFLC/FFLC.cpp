//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("FFLC.res");
USEFORM("FFLCSrc.cpp", FFLC);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TFFLC), &FFLC);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------


