//---------------------------------------------------------------------------
#ifndef XH
#define XH

//directX includes
//#define D3D_OVERLOADS
//#define INITGUID
//#include <ddraw.h>
//#include <d3d.h>

//other includes
#include "DXError.h"
#include "XUtil.h"

#define SafeRelease(x) if (x) { x->Release(); x=NULL;}
#define SafeDelete(x) if (x) {delete x;x=NULL;}

//---------------------------------------------------------------------------
class X
{
public:
    X();
    ~X();

    //returns a struct Screen which holds a list of all enum devices on this system
    Screen* GetDisplayDevices();

    //InitGraphics - used to start the whole 3D engine
    // inputs:
    //  HWND hwnd - the handle to the window to create a direct draw/3D surface on
    //  bool fullscreen - wether or not you want the engine to run in full screen
    //  GUID DisplayGUID - a pointer, if you want, to a monitor GUID device to run the full screen app on
    // returns:
    //  HRESULT of a DirectX type, DD_OK if all OK
    bool InitGraphics(HWND hwnd, bool fullScreen = false, GUID *DisplayGUID = NULL);

    /*
protected:

    //this if the rending loop
    virtual */bool Update(bool fullScreen);// = 0;


private:
    HRESULT InitDD(HWND hwnd, bool fullScreen, GUID* DisplayGUID);
    HRESULT InitD3D();

    void Cleanup();

    DXError* error;
    XUtil* xUtil;

    RECT screenRect;
    RECT viewportRect;

};
#endif
 