//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("CreateLists.res");
USEFORM("CreateList.cpp", ListProg);
USEFORM("addItem.cpp", addItemForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TListProg), &ListProg);
        Application->CreateForm(__classid(TaddItemForm), &addItemForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
