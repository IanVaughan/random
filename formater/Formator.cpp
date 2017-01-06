//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Formator.res");
USEFORM("formator.cpp", startForm);
USEFORM("..\..\..\MYDOCU~1\PROGRA~2\FORMATER\working.cpp", work);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "Code Formater";
        Application->CreateForm(__classid(TstartForm), &startForm);
        Application->CreateForm(__classid(Twork), &work);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
