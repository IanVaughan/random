//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DeleteDir.res");
USEFORM("DeleteFormSrc.cpp", DeleteForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TDeleteForm), &DeleteForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
