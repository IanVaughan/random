//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "test1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TX *X;

#define INITGUID
#include "ddraw.h"

LPDIRECTDRAW7 DirectDraw = NULL;
LPDIRECTDRAWSURFACE7 PrimarySurface = NULL;
LPDIRECTDRAWSURFACE7 BackSurface = NULL;
LPDIRECT3D7 Direct3D = NULL;
LPDIRECT3DDEVICE7 D3DDevice = NULL;

//---------------------------------------------------------------------------

__fastcall TX::TX(TComponent* Owner) : TForm(Owner)
{
    err = new TD3DError;

    HRESULT hres = NULL;

    hres = CreateDD();
    if(hres != DD_OK)
    {
        err->Display(hres);
        return;
    }

    hres = CreateSurfaces();
    if(hres != DD_OK)
    {
        err->Display(hres);
        return;
    }

    hres = Create3D();
    if(hres != DD_OK)
    {
        err->Display(hres);
        return;
    }

}
//---------------------------------------------------------------------------

__fastcall TX::~TX()
{
    //release in reverse order...
    SafeRelease(D3DDevice);
    SafeRelease(Direct3D);
    SafeRelease(BackSurface);
    SafeRelease(PrimarySurface);
    SafeRelease(DirectDraw);

    delete err;
}
//---------------------------------------------------------------------------

HRESULT TX::CreateDD()
{
    HRESULT hres;

    //create the main 'root' Direct Draw object
    hres = DirectDrawCreateEx(NULL, (void**)&DirectDraw, IID_IDirectDraw7, NULL);
    if(FAILED(hres))
        return hres;


    hres = DirectDraw->SetCooperativeLevel(Handle,
                                           DDSCL_ALLOWREBOOT  |
                                           DDSCL_EXCLUSIVE |
                                           DDSCL_FULLSCREEN
                                            );
    if(FAILED(hres))
        return hres;

    //got to here, so all ok...
    return DD_OK;
}


HRESULT TX::CreateSurfaces()
{
    HRESULT hres;

	// Set the display mode
	hres = DirectDraw->SetDisplayMode(640, 480, 16, 0, 0);
	if (hres !=DD_OK)
		return hres;

    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd,sizeof(DDSURFACEDESC2));
    ddsd.dwSize = sizeof(DDSURFACEDESC2);

    // Tell DirectDraw which members are valid.
    ddsd.dwFlags = DDSD_CAPS
                 | DDSD_BACKBUFFERCOUNT;
    // Request a primary surface with a single back buffer
    ddsd.ddsCaps.dwCaps = DDSCAPS_COMPLEX
                        | DDSCAPS_FLIP
                        | DDSCAPS_PRIMARYSURFACE
                        | DDSCAPS_3DDEVICE;
    ddsd.dwBackBufferCount = 1;
    hres = DirectDraw->CreateSurface(&ddsd, &PrimarySurface, NULL);
    if(FAILED(hres))
        return hres;


	// Fetch back buffer interface
	DDSCAPS2 ddscaps;
	ZeroMemory(&ddscaps,sizeof(DDSCAPS2));
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	hres = PrimarySurface->GetAttachedSurface(&ddscaps,&BackSurface);
	if (hres!=DD_OK)
		return hres;
/* either works?
    DDSCAPS2 ddscaps;
    ZeroMemory(&ddscaps, sizeof(DDSCAPS2));
    ddscaps.dwCaps = DDSCAPS_3DDEVICE
                   | DDSCAPS_BACKBUFFER
                   | DDSCAPS_COMPLEX
                   | DDSCAPS_FLIP ;

    hres = PrimarySurface->GetAttachedSurface(&ddscaps, &BackSurface);
    if(FAILED(hres))
        return hres;
*/

    return DD_OK;
}

/*

    //primary surface
    DDSURFACEDESC2 ddsd;
    ZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    // Create the primary surface.
    hres = DirectDraw->CreateSurface(&ddsd, &PrimarySurface, NULL);
    if(FAILED(hres))
        return hres;

*/


HRESULT TX::Create3D()
{
    HRESULT hres;

	// get master 3D interface
    hres = DirectDraw->QueryInterface(IID_IDirect3D7, (void**)&Direct3D);
	if (FAILED(hres))
		return hres;

	// set up the best device interface
	if ((hres = Direct3D->CreateDevice(IID_IDirect3DTnLHalDevice, BackSurface, &D3DDevice)) != D3D_OK)
		if (hres = Direct3D->CreateDevice(IID_IDirect3DHALDevice,   BackSurface, &D3DDevice) != D3D_OK)
			if (hres = Direct3D->CreateDevice(IID_IDirect3DMMXDevice, BackSurface, &D3DDevice) != D3D_OK)
				if (hres = Direct3D->CreateDevice(IID_IDirect3DRGBDevice, BackSurface, &D3DDevice) != D3D_OK)
					return hres;

    return DD_OK;
}
