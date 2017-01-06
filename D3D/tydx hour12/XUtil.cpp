//---------------------------------------------------------------------------
//#include <vcl.h>
//#pragma hdrstop

#include "XUtil.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)

    // Linked list of Screens
Screen* XUtil::s_pScreenFirst = NULL; 


//-----------------------------------------------------------------------------
// Name: EnumerateScreens()
// Desc: Creates a Screen structure for every appropriate screen in the user's
//       computer.  This function is written in such a way that it will work on
//       systems that do not necessarily have DX6 (and thus DirectDrawEnumerateEx)
//       installed.  If your application has already ensured that DX6 is present,
//       you won't need to handle calling DirectDrawEnumerate and providing a
//       DDEnumCallback function.  If your application has already ensured that
//       DX7 is present, you don't even need to use LoadLibrary and 
//       GetProcAddress.  Just call DirectDrawEnumerateEx directly.
//
//-----------------------------------------------------------------------------

HRESULT XUtil::EnumerateScreens()
{
    HRESULT hr;
    HMODULE hModule = NULL;
    LPDIRECTDRAWENUMERATEEX pDDEnumEx = NULL;
    EnumInfo enumInfo;

    ZeroMemory(&enumInfo, sizeof(enumInfo));

    hModule = LoadLibrary( TEXT("ddraw.dll") );
    // If ddraw.dll doesn't exist in the search path,
    // then DirectX probably isn't installed, so fail.
    if (hModule == NULL)
        return E_FAIL;

    pDDEnumEx = (LPDIRECTDRAWENUMERATEEX) GetProcAddress(hModule,
#ifdef UNICODE
        "DirectDrawEnumerateExW"
#else
        "DirectDrawEnumerateExA"
#endif
        );

    enumInfo.bMultimonSupported = TRUE;
    hr = pDDEnumEx(DDEnumCallbackEx, &enumInfo, DDENUM_ATTACHEDSECONDARYDEVICES);

    // If something failed inside the enumeration, be sure to return that HRESULT
    if (SUCCEEDED(hr) && FAILED(enumInfo.hr))
        hr = enumInfo.hr;

//    FreeLibrary(hModule);
    return hr;
}


//-----------------------------------------------------------------------------
// Name: DDEnumCallbackEx()
// Desc: This callback function is called by DirectDraw once for each 
//       available DirectDraw device.  In this implementation, it saves the
//       GUID, device description, and hmon in a Screen structure for later use.
//-----------------------------------------------------------------------------
BOOL WINAPI XUtil::DDEnumCallbackEx( GUID* pGuid, LPTSTR pszDesc, LPTSTR /*pszDriverName*/,
                              VOID* pContext, HMONITOR hmon )
{
    Screen* pScreenNew;
    EnumInfo* pEnumInfo = (EnumInfo*)pContext;
    GUID guidNull;
    ZeroMemory(&guidNull, sizeof(GUID));

    if (s_pScreenFirst != NULL && s_pScreenFirst->guid == guidNull)
    {
        // We must be running on a multimon system, so get rid of the 
        // guidNull Screen -- we want Screens with specific GUIDs.
        delete s_pScreenFirst;
        s_pScreenFirst = NULL;
    }

    // Store all the info in a Screen structure
    pScreenNew = new Screen;
    if (pScreenNew == NULL)
    {
        pEnumInfo->hr = E_OUTOFMEMORY;
        return FALSE; // fatal error, stop enumerating
    }
    ZeroMemory(pScreenNew, sizeof(Screen));
    if (pGuid == NULL)
        pScreenNew->guid = guidNull;
    else
        pScreenNew->guid = *pGuid;
    lstrcpy(pScreenNew->szDesc, pszDesc);
    pScreenNew->hmon = hmon;

    // Insert Screen into global linked list
    if (s_pScreenFirst == NULL)
        s_pScreenFirst = pScreenNew;
    else
    {
        // Insert at end of list
        Screen* pScreen = s_pScreenFirst; 
        while (pScreen->pScreenNext != NULL)
            pScreen = pScreen->pScreenNext;
        pScreen->pScreenNext = pScreenNew;
    }

    return TRUE; // Keep enumerating
}
//---------------------------------------------------------------------------

Screen* XUtil::GetScreenList()
{
    return XUtil::s_pScreenFirst;
}

//******************************************************************************
//* String utils

int XUtil::length(char* in)
{
    int length = 0;
    while(in[length] != '\0')
        length++;

    return length;
}

int XUtil::getPos(char* charIn, char searchChar)
{
    int pos = 0;
    while(charIn[pos] != searchChar)
        pos++;

    return pos;
}


