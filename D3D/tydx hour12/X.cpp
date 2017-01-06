#include "X.h"

LPDIRECTDRAW7           DirectDraw        = NULL;
LPDIRECTDRAWSURFACE7    PrimarySurface    = NULL;
LPDIRECTDRAWSURFACE7    BackSurface       = NULL;
LPDIRECT3D7             Direct3D          = NULL;
LPDIRECT3DDEVICE7       D3DDevice         = NULL;

//---------------------------------------------------------------------------

X::X()
{
}
//---------------------------------------------------------------------------

bool X::InitGraphics(HWND hwnd, bool fullScreen, GUID* DisplayGUID)
{
    HRESULT ddrval = NULL;

	// initialze DirectDraw
    ddrval = InitDD(hwnd, fullScreen, DisplayGUID);
    if (FAILED(ddrval))
    {
        Cleanup();
        error->Display(ddrval);
        PostQuitMessage(0);
        return false;
	}

	// initialize Direct3D
	ddrval = InitD3D();
    if (FAILED(ddrval))
    {
        Cleanup();
        error->Display(ddrval);
        PostQuitMessage(0);
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------

X::~X()
{
    //this cleans all the DirectX interfaces
    Cleanup();
}
//---------------------------------------------------------------------------

Screen* X::GetDisplayDevices()
{
    //get all of the monitors first
    HRESULT ddrval = xUtil->EnumerateScreens();
    if(FAILED(ddrval))
    {
        Cleanup();
        error->Display(ddrval);
        PostQuitMessage(0);
    }

    return xUtil->GetScreenList();
}
//---------------------------------------------------------------------------

HRESULT X::InitDD(HWND hwnd, bool fullScreen, GUID* DisplayGUID)
{
	HRESULT ddrval;

    // Create the main DirectDraw object
    ddrval = DirectDrawCreateEx(DisplayGUID, (void **) &DirectDraw, IID_IDirectDraw7, NULL);
    if (FAILED(ddrval))
    	return ddrval;

    //---------------------------------------------------------------------------

    // Set our cooperative level

    //switch the coop level depending on fullScreen/windowed mode
    WORD coopFlags = NULL;
    if(fullScreen)
        coopFlags = DDSCL_SETFOCUSWINDOW
                  | DDSCL_CREATEDEVICEWINDOW
                  | DDSCL_EXCLUSIVE
                  | DDSCL_FULLSCREEN
                  | DDSCL_ALLOWREBOOT;
    else
        coopFlags = DDSCL_NORMAL;

    ddrval = DirectDraw->SetCooperativeLevel(hwnd, coopFlags);
    if (FAILED(ddrval))
		return ddrval;

    //---------------------------------------------------------------------------

	// Set the display mode, only if in fullScreen window mode
    if(fullScreen)
    {
    	ddrval = DirectDraw->SetDisplayMode(640, 480, 16, 0, 0);
    	if (FAILED(ddrval))
	    	return ddrval;
    }

    //---------------------------------------------------------------------------

    // Create the primary surface
    DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize = sizeof(ddsd);

    //change what the caps are depending on fullScreen/windowed mode
    DWORD capsFlags = DDSD_CAPS; // both modes have capabilities!
    DWORD surfaceCapsFlags = DDSCAPS_PRIMARYSURFACE; //both use the primarySurface

    //add on more flags for fulScreen. windowed mode doesnt need any more
    if(fullScreen)
    {
        //only in fullScreen can we have a backbuffer, windowed mode had 'other'
        // surfaces which we 'think' of as the backbuffer, and blit them instead of fliping
        capsFlags |= DDSD_BACKBUFFERCOUNT;
        surfaceCapsFlags |= DDSCAPS_PRIMARYSURFACE |
                          DDSCAPS_FLIP | DDSCAPS_3DDEVICE |
                          DDSCAPS_COMPLEX;

        ddsd.dwBackBufferCount = 1;
    }

    ddsd.dwFlags = capsFlags;
    ddsd.ddsCaps.dwCaps = surfaceCapsFlags;

    ddrval = DirectDraw->CreateSurface(&ddsd, &PrimarySurface, NULL);
	if (FAILED(ddrval))
		return ddrval;

    //---------------------------------------------------------------------------

    //if in fullScreen mode, we ask for the back surface we created during the
    // creation of the primary. But in windowed mode, we have to create another surface
    if(fullScreen)
    {
        // Fetch back buffer interface
        DDSCAPS2 ddscaps;
        ZeroMemory(&ddscaps,sizeof(ddscaps));

        ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

        ddrval = PrimarySurface->GetAttachedSurface(&ddscaps, &BackSurface);
        if (FAILED(ddrval))
            return ddrval;
    }
    else
    {
        // Create the backbuffer.

        //first off clear the struct cos we used it earlier
        ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
        ddsd.dwSize = sizeof(ddsd);

        //then set the flags
        ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
        ddsd.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN;

        // Set the dimensions of the back buffer. Note that if our window changes
        // size, we need to destroy this surface and create a new one.
        GetClientRect(hwnd, &screenRect);
        GetClientRect(hwnd, &viewportRect);
        ClientToScreen(hwnd, (POINT*)&screenRect.left);
        ClientToScreen(hwnd, (POINT*)&screenRect.right);
        ddsd.dwWidth  = screenRect.right - screenRect.left;
        ddsd.dwHeight = screenRect.bottom - screenRect.top;

        ddrval = DirectDraw->CreateSurface(&ddsd, &BackSurface, NULL);
        if(FAILED(ddrval))
            return ddrval;
    }

    //---------------------------------------------------------------------------

    //After creating the primary and render target surface, create and attach a
    // DirectDrawClipper object to the display surface.
    //Clippers aren't needed for applications that run in full-screen mode.
    if(!fullScreen)
    {
        LPDIRECTDRAWCLIPPER clipper;
        ddrval = DirectDraw->CreateClipper(0, &clipper, NULL);
        if(FAILED(ddrval))
            return ddrval;

        // Assign it to the window handle, then set
        // the clipper to the desired surface.
        clipper->SetHWnd(0, hwnd);
        PrimarySurface->SetClipper(clipper);
        clipper->Release();
    }

    //---------------------------------------------------------------------------
	// return success to caller
	return DD_OK;
}
//---------------------------------------------------------------------------

HRESULT X::InitD3D()
{
    HRESULT ddrval;

	// get master 3D interface
    ddrval = DirectDraw->QueryInterface(IID_IDirect3D7, (LPVOID *)&Direct3D);
	if (FAILED(ddrval))
		return ddrval;

	// set up the best device interface
	if ((ddrval = Direct3D->CreateDevice(IID_IDirect3DTnLHalDevice, BackSurface, &D3DDevice)) !=D3D_OK) {
		if ((ddrval = Direct3D->CreateDevice(IID_IDirect3DHALDevice, BackSurface, &D3DDevice)) !=D3D_OK) {
			if ((ddrval = Direct3D->CreateDevice(IID_IDirect3DMMXDevice, BackSurface, &D3DDevice)) !=D3D_OK) {
				if ((ddrval = Direct3D->CreateDevice(IID_IDirect3DRGBDevice, BackSurface, &D3DDevice)) !=D3D_OK) {
					return ddrval;
				}
			}
		}
	}

	// set up the viewport
	D3DVIEWPORT7 view;
	view.dwX = 0;
	view.dwY = 0;
	view.dwWidth = screenRect.right - screenRect.left;//640;
	view.dwHeight = screenRect.bottom - screenRect.top;//480;
	view.dvMinZ = 0.0f;
	view.dvMaxZ = 1.0f;
    ddrval = D3DDevice->SetViewport(&view);
	if (ddrval!=D3D_OK)
		return ddrval;

//	D3DMATRIX proj_m;
//	D3DUtil_SetProjectionMatrix(proj_m, 0.785f, 1.333f, 10.0f, 2000.0f );
//	D3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION,&proj_m);

	// disable Direct3D lighting, since we will provide our own
//	D3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING, FALSE);

	// return success to caller
	return DD_OK;
}
//---------------------------------------------------------------------------

void X::Cleanup()
{
	// release 3D interfaces
	SafeRelease(D3DDevice);
	SafeRelease(Direct3D);

	// release DirectDraw interfaces
	SafeRelease(PrimarySurface);
	SafeRelease(DirectDraw);
}
//---------------------------------------------------------------------------

bool X::Update(bool fullScreen)
{
    HRESULT ddrval = NULL;

    if(PrimarySurface == NULL)
        return E_FAIL;

    // Clear the viewport to a blue color.
    D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0xff00ffff, 0L, 0L );

    if(fullScreen)
    {
        PrimarySurface->Flip(0, DDFLIP_WAIT);
    }
    else
    {
        // We are in windowed mode, so perform a blit from the backbuffer to the
        // correct position on the primary surface
        ddrval = PrimarySurface->Blt(&screenRect, BackSurface,
                                   &viewportRect, DDBLT_WAIT, NULL);

        if(FAILED(ddrval))
            return ddrval;

    }
    return true;
}
//---------------------------------------------------------------------------

