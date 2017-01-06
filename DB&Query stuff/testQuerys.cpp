//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("testQuerys.res");
USEFORM("testQ.cpp", Form1);
USEFORM("SIDsrc.cpp", SIDform);
USEFORM("DMsrc.cpp", DMform); /* TDataModule: DesignClass */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TForm1), &Form1);
        Application->CreateForm(__classid(TSIDform), &SIDform);
        Application->CreateForm(__classid(TDMform), &DMform);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
