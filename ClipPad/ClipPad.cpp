//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ClipPad.res");
USEFORM("ClipPadSrc.cpp", ClipPad);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TClipPad), &ClipPad);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
