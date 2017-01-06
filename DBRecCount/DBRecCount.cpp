//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DBRecCount.res");
USEFORM("RecCount.cpp", DBRecCount);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "DB Rec Count";
        Application->CreateForm(__classid(TDBRecCount), &DBRecCount);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
