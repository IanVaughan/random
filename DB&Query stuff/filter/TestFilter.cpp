//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("TestFilter.res");
USEFORM("filter.cpp", filterForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TfilterForm), &filterForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
