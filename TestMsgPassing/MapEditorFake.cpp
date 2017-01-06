//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------

USEFILE("MapEditorFake.h");
USEFORM("DPInterface.cpp", MapEditorFormFake);
USELIB("..\..\..\Program Files\Borland\CBuilder3\Lib\memmgr.lib");
//---------------------------------------------------------------------------
#include "MapEditorFake.h"
#include "DPInterface.h"
// -----------------------------------------------------------------------------

CallMeBack MethodToCall;
TDPInterface *meForm;
// -----------------------------------------------------------------------------

int WINAPI DllEntryPoint(   HINSTANCE hinst,        //DLL module handle
                            unsigned long reason,   //reason called (DWORD)
                            void* lpvReserved)      //reserved  (LPVOID)
{
    return 1;
}
//---------------------------------------------------------------------------

void __EXPORT_TYPE RegCallback(CallMeBack method)
{
    MethodToCall = method;

    meForm = new TDPInterface(NULL);
    meForm->Show();
}
// -----------------------------------------------------------------------------

void SendMsg(DPFormShowData *fd)
{
    MethodToCall(fd);
}
// -----------------------------------------------------------------------------


