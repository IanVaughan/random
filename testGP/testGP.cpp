//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//USERES("testGP.res");
USEFORM("GroundVehiclePerformanceEditorSrc.cpp", GroundVehiclePerformanceEditor);
USEFORM("GroundVehicleEditorSrc.cpp", GroundVehicleEditorForm);
USEFORM("testRunner.cpp", testRun);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TtestRun), &testRun);
        Application->CreateForm(__classid(TGroundVehicleEditorForm), &GroundVehicleEditorForm);
        Application->CreateForm(__classid(TGroundVehiclePerformanceEditor), &GroundVehiclePerformanceEditor);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------

