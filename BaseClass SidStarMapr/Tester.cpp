//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Tester.res");
USEFORM("testerSrc.cpp", test);
USEFORM("BaseSidStarMapr.cpp", BaseSidStarMapr);
USEUNIT("Sid.cpp");
USEUNIT("Star.cpp");
USEUNIT("Mapr.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(Ttest), &test);
        Application->CreateForm(__classid(TBaseSidStarMapr), &BaseSidStarMapr);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
