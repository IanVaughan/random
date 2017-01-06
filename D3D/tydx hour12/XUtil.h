//---------------------------------------------------------------------------
#ifndef XUtilH
#define XUtilH
//---------------------------------------------------------------------------
#include <Windows.h>
// Multimon.h implements support of the multimon APIs for when your program
// runs on Windows 95 systems.  You can #include multimon.h in all your source
// files that use multimon APIs, and you should #define COMPILE_MULTIMON_STUBS
// in only one of your source files.
#define COMPILE_MULTIMON_STUBS
//#include <multimon.h>

#include <ddraw.h>

// An EnumInfo contains extra enumeration information that is passed
// into the the DDEnumCallbackEx function.
struct EnumInfo
{
    BOOL bMultimonSupported;
    HRESULT hr;
};

// A Screen represents one display that images can be drawn to.
struct Screen
{
    GUID guid;
    TCHAR szDesc[200];
    HMONITOR hmon;
    LPDIRECTDRAW7 pdd;
    LPDIRECTDRAWSURFACE7 pddsFront;
    LPDIRECTDRAWSURFACE7 pddsBack;
    Screen* pScreenNext; // For linked list
};



class XUtil
{
public:
    HRESULT EnumerateScreens();
    Screen* GetScreenList();

    int length(char* in);
    int getPos(char* charIn, char searchChar);


private:
    static BOOL WINAPI DDEnumCallbackEx(GUID* pGuid, LPTSTR pszDesc, LPTSTR pszDriverName,
                                    VOID* pContext, HMONITOR hmon);

    static Screen* s_pScreenFirst;// = NULL; // Linked list of Screens
};
#endif
 