//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DrawMesh.res");
USEFORM("DrawMeshSrc.cpp", DrawMeshForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TDrawMeshForm), &DrawMeshForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
