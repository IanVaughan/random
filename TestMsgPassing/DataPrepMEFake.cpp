//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DataPrepMEFake.res");
USEFORM("DataPrepSrcFake.cpp", MainForm);
USELIB("MapEditorFake.lib");
USEFORM("DPFormSrc.cpp", DPForm);
USELIB("..\..\..\Program Files\Borland\CBuilder3\Lib\memmgr.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TMainForm), &MainForm);
        Application->CreateForm(__classid(TDPForm), &DPForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
