//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("MusicList.res");
USEFORM("MusicListSrc.cpp", MusicList);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TMusicList), &MusicList);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
