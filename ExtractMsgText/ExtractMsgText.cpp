//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ExtractMsgText.res");
USEFORM("extactMsgBoxTextSrc.cpp", extractMsgTextForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TextractMsgTextForm), &extractMsgTextForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
