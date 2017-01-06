//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("CodeViewCreator.res");
USEFORM("CodeViewCreatorSrc.cpp", CodeViewCreator);
USEFORM("CreatorSrc.cpp", Creator);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TCodeViewCreator), &CodeViewCreator);
        Application->CreateForm(__classid(TCreator), &Creator);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------

