//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("PSorta.res");
USEFORM("PSortaSrc.cpp", ProjectSorta);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TProjectSorta), &ProjectSorta);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
