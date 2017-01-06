//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("read.res");
USEFORM("read1.cpp", readForm);
USEFORM("DisplayStrip.cpp", DisplayStripForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "Reader";
        Application->CreateForm(__classid(TreadForm), &readForm);
        Application->CreateForm(__classid(TDisplayStripForm), &DisplayStripForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
