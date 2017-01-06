//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
HINSTANCE g_hinst;
//---------------------------------------------------------------------------
USEFILE("readme.txt");
USEFORM("traymain.cpp", Form1);
USERES("trayicon.res");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE hInstance, LPSTR, int)
{
    Application->Initialize();
    g_hinst = hInstance;
    Application->CreateForm(__classid(TForm1), &Form1);
        Application->Run();

    return 0;
}
//---------------------------------------------------------------------------

