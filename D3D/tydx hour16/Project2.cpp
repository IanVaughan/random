
//#include <windows.h>
#pragma hdrstop
#include <condefs.h>

//---------------------------------------------------------------------------
USEUNIT("Car.cpp");
USEUNIT("Cube.cpp");
USEUNIT("d3dmath.cpp");
USEUNIT("d3dtextr.cpp");
USEUNIT("d3dutil.cpp");
USEUNIT("Helicopter.cpp");
USEUNIT("Obj.cpp");
USEUNIT("Scene.cpp");
USEUNIT("StdAfx.cpp");
USEUNIT("xfile.cpp");
USELIB("..\..\..\..\mssdk\lib\Borland\dxguid.lib");
USELIB("..\..\..\..\mssdk\lib\Borland\ddraw.lib");
USELIB("..\..\..\..\mssdk\lib\Borland\d3dim.lib");

#include "d3DFile.h"
//---------------------------------------------------------------------------
#pragma argsused
/*
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        return 0;
}
*/


/*--------------------------------------------------------------------------*/
// Sample Application													
//																			
// Chapter 16																
//																			
// Learn DirectX in 24 Hours												
// by Robert Dunlop															
//																			
// Copyright (C) 1999														
/*--------------------------------------------------------------------------*/

//------ Include Files ------//

#include "stdafx.h"
#define D3D_OVERLOADS
#define INITGUID
#include "windef.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <d3d.h>
#include <d3dtypes.h>
#include "d3dutil.h"
#include "d3dmath.h"
#include "d3dtextr.h"
#include "obj.h"
#include "cube.h"
#include "helicopter.h"
#include "car.h"
#include "scene.h"
#include "d3dfile.h"

#define SafeRelease(x) if (x) { x->Release(); x=NULL;}
#define SafeDelete(x) if (x) {delete x; x=NULL;}

//------ Window Class Information ------//

static char szClass[] = "XmplHr16Class";
static char szCaption[] = "Example - Hour 16";

//------ Global Interface Pointers ------//

LPDIRECTDRAW7 lpDD=NULL;
LPDIRECTDRAWSURFACE7 lpDDSPrimary=NULL;
LPDIRECTDRAWSURFACE7 lpDDSBack=NULL;
LPDIRECT3D7 lpD3D=NULL;
LPDIRECT3DDEVICE7 lpDevice=NULL;
LPDIRECTDRAWSURFACE7 lpDDSZBuf=NULL;
LPDIRECTDRAWSURFACE7 lpBuildText[4]={NULL,NULL,NULL,NULL};
LPDIRECTDRAWSURFACE7 lpClouds=NULL;

//----- X File Object Pointers for 3D Models -----//

CD3DFile * lpXFileHelo=NULL;		// helicopter model
CD3DFile * lpXFileCar=NULL;			// car model

//----- Rotation angle and speed -----//

float rotAngle=g_PI;		// current angle
float rotVel=0.0f;			// current velociy of spin

//----- Elevation of viewer and vertical speed -----//

float elevation=1050.0f;		// current elevation
float liftVel=0.0f;			// rate of rise / decent

//----- Define distance of viewer orbit from target ------//

#define ORBIT			6000.0f

//------ Storage for Cube Objects -----//

#define MAX_CUBES		4000

WORD cube_cnt=0;
CCube *cubes[MAX_CUBES];

//------ Moving Objects -----//

CHelicopter *chopper=NULL;

//------ Scene Handling -----//

CScene *scene=NULL;

//------ Error Return String ------//

const char *ErrStr=NULL;	

//------ Error Messages ------//

const char Err_Reg_Class[]			= "Error Registering Window Class";
const char Err_Create_Win[]			= "Error Creating Window";
const char Err_DirectDrawCreate[]	= "DirectDrawCreate FAILED";
const char Err_Query[]				= "QueryInterface FAILED";
const char Err_Coop[]				= "SetCooperativeLevel FAILED";
const char Err_CreateSurf[]			= "CreateSurface FAILED";
const char Err_DispMode[]			= "Error Setting Display Mode";
const char Err_Device[]				= "Device Creation Failed";
const char Err_SetView[]			= "Viewport settings failed";

//------ Function Prototypes -----//

void Cleanup();
void create_objects();
static BOOL Init(HINSTANCE hInstance, int nCmdShow);
BOOL init_d3d();
BOOL init_ddraw(HWND hWnd);
void render_frame(float elapsed);
static HRESULT WINAPI EnumZBufferFormatsCallback( DDPIXELFORMAT* pddpf,
                                                  VOID* pddpfDesired );

// ----- Function Definitions -----//

void Cleanup()
{
	// unload animated object classes

	SafeDelete(chopper);

	// unload 3D models

	SafeDelete(lpXFileCar);
	SafeDelete(lpXFileHelo);

	// de-allocate the player vehicle instance

	SafeDelete(scene);

	// de-allocate the cubes

	for (int i=0;i<cube_cnt;i++)
		SafeDelete(cubes[i]);

	D3DTextr_InvalidateAllTextures();

	// release z-buffer

	if (lpDDSZBuf&&lpDDSBack) {
		lpDDSBack->DeleteAttachedSurface(0,lpDDSZBuf);
		lpDDSZBuf=NULL;
	}

	// release 3D interfaces

	SafeRelease(lpDevice);
	SafeRelease(lpD3D);
	
	// release DirectDraw interfaces

	SafeRelease(lpDDSPrimary);
	SafeRelease(lpDD);

	// display error if one thrown

	if (ErrStr) {
		MessageBox(NULL, ErrStr, szCaption, MB_OK);
		ErrStr=NULL;
	}

}

LRESULT CALLBACK 
WindowProc(HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
		case WM_DESTROY:

			Cleanup();
            PostQuitMessage(0);
            break;

	    case WM_KEYDOWN: 

	        switch (wParam) { 

			case VK_UP:
			
				// pith up
				
				if (scene)
					scene->set_pitch(-1.0f);
				break;

			case VK_DOWN:

				// pitch down

				if (scene)
					scene->set_pitch(1.0f);
				break;

			case VK_RIGHT:

				// rotate to the right

				if (scene)
					scene->set_steer(-1.0f);
				break;

			case VK_LEFT:

				// rotate to the left

				if (scene)
					scene->set_steer(1.0f);
				break; 

			case 'z':
			case 'Z':

				// rotate to the right

				if (scene)
					scene->set_lift(-1.0f);
				break;

			case 'a':
			case 'A':

				// rotate to the left

				if (scene)
					scene->set_lift(1.0f);
				break; 

			}
			break;

	    case WM_KEYUP: 

	        switch (wParam) { 

			case VK_ESCAPE:

				// exit the program on escape

				DestroyWindow(hWnd);
				break;

			}
			break;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
	
	return 0L;
}

BOOL init_ddraw(HWND hWnd)
{
	HRESULT ddrval;

    // Create the main DirectDraw object

    ddrval = DirectDrawCreateEx(NULL, (void **) &lpDD, IID_IDirectDraw7, NULL);
    if (ddrval != DD_OK) {
		ErrStr=Err_DirectDrawCreate;
		return FALSE;
	}

    // Set our cooperative level

    ddrval = lpDD->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
    if (ddrval != DD_OK) {
		ErrStr=Err_Coop;
		return FALSE;
	}

	// Set the display mode

	ddrval = lpDD->SetDisplayMode( 640, 480, 16, 0, 0);
	if (ddrval !=DD_OK) {
		ErrStr=Err_DispMode;
		return FALSE;
	}

    // Create the primary surface with 1 back buffer

    DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
                          DDSCAPS_FLIP | DDSCAPS_3DDEVICE |
                          DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
	if (ddrval!=DD_OK) {
		ErrStr=Err_CreateSurf;
		return FALSE;
	}

	// Fetch back buffer interface

	DDSCAPS2 ddscaps;
	ZeroMemory(&ddscaps,sizeof(ddscaps));
	ddscaps.dwCaps=DDSCAPS_BACKBUFFER;
	ddrval=lpDDSPrimary->GetAttachedSurface(&ddscaps,&lpDDSBack);
	if (ddrval!=DD_OK) {
		ErrStr=Err_CreateSurf;
		return FALSE;
	}

	// return success to caller

	return TRUE;
}

BOOL zbuf_flag=FALSE;
char zbuf_format=0;

static HRESULT WINAPI EnumZBufferFormatsCallback( DDPIXELFORMAT* pddpf,
                                                  VOID* pddpfDesired )
{
    if( NULL==pddpf || NULL==pddpfDesired )
        return D3DENUMRET_CANCEL;

    // If the current pixel format's match the desired ones (DDPF_ZBUFFER and
    // possibly DDPF_STENCILBUFFER), lets copy it and return. This function is
    // not choosy...it accepts the first valid format that comes along.
    if( pddpf->dwFlags == ((DDPIXELFORMAT*)pddpfDesired)->dwFlags )
    {
        memcpy( pddpfDesired, pddpf, sizeof(DDPIXELFORMAT) );
		zbuf_flag=TRUE;
        return D3DENUMRET_CANCEL;
    }

    return D3DENUMRET_OK;
}

BOOL init_d3d()
{
	// get master 3D interface

	if (FAILED(lpDD->QueryInterface(IID_IDirect3D7, (LPVOID *)&lpD3D))) {
		ErrStr=Err_Query;
		return FALSE;
	}
	
	// enumerate the Z-buffer formats

	DDPIXELFORMAT m_ddpfZBuffer;
	ZeroMemory(&m_ddpfZBuffer,sizeof(m_ddpfZBuffer));
	m_ddpfZBuffer.dwSize=sizeof(m_ddpfZBuffer);
	m_ddpfZBuffer.dwFlags = DDPF_ZBUFFER ;
	lpD3D->EnumZBufferFormats( IID_IDirect3DTnLHalDevice, 
							   EnumZBufferFormatsCallback,
							   (VOID*)&m_ddpfZBuffer);
	if (zbuf_flag) {
		zbuf_format=1;
	} else {
		lpD3D->EnumZBufferFormats( IID_IDirect3DHALDevice, EnumZBufferFormatsCallback,
		                            (VOID*)&m_ddpfZBuffer );
		if (zbuf_flag) {
			zbuf_format=2;
		} else {
			lpD3D->EnumZBufferFormats( IID_IDirect3DMMXDevice, EnumZBufferFormatsCallback,
			                            (VOID*)&m_ddpfZBuffer );
			if (zbuf_flag) {
				zbuf_format=3;
			} else {
				lpD3D->EnumZBufferFormats( IID_IDirect3DRGBDevice, EnumZBufferFormatsCallback,
				                            (VOID*)&m_ddpfZBuffer );
				if (zbuf_flag) 
					zbuf_format=4;
			}
		}
	}

	// create the zbuffer

	DDSURFACEDESC2 ddsd;
	HRESULT ddrval;
	ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
	if (zbuf_format<3)
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER|DDSCAPS_VIDEOMEMORY;
	else
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER|DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth=640;
	ddsd.dwHeight=480;
	ddsd.ddpfPixelFormat.dwSize=sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags=DDPF_ZBUFFER;
	memcpy(&ddsd.ddpfPixelFormat,&m_ddpfZBuffer,sizeof(DDPIXELFORMAT));
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSZBuf, NULL );
	if (ddrval!=DD_OK) {
//		write_debug("zbuffer create failed");
	} else {
		lpDDSBack->AddAttachedSurface(lpDDSZBuf);
	}

	// set up the best device interface

	if (lpD3D->CreateDevice(IID_IDirect3DTnLHalDevice,lpDDSBack,&lpDevice)!=D3D_OK) {
		if (lpD3D->CreateDevice(IID_IDirect3DHALDevice,lpDDSBack,&lpDevice)!=D3D_OK) {
			if (lpD3D->CreateDevice(IID_IDirect3DMMXDevice,lpDDSBack,&lpDevice)!=D3D_OK) {
				if (lpD3D->CreateDevice(IID_IDirect3DRGBDevice,lpDDSBack,&lpDevice)!=D3D_OK) {
					ErrStr=Err_Device;
					return FALSE;
				}
			}
		}
	}

	// set up the viewport

	D3DVIEWPORT7 view;
	view.dwX=0;
	view.dwY=0; 
	view.dwWidth=640;
	view.dwHeight=480; 
	view.dvMinZ=0.0f;
	view.dvMaxZ=1.0f;
	if (lpDevice->SetViewport(&view)!=D3D_OK) {
		ErrStr=Err_SetView;
		return FALSE;
	}
	
	D3DMATRIX proj_m;
	D3DUtil_SetProjectionMatrix(proj_m, 0.8f, 1.333f, 10.0f, 5000.0f );
	lpDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION,&proj_m);

	// disable Direct3D lighting, since we will provide our own

	lpDevice->SetRenderState(D3DRENDERSTATE_LIGHTING,FALSE);
	lpDevice->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);

	// return success to caller
	
	return TRUE;
}

void create_objects()
{
	D3DTextr_CreateTextureFromFile( "build1.bmp", 0 );
	D3DTextr_CreateTextureFromFile( "build2.bmp", 0 );
	D3DTextr_CreateTextureFromFile( "build3.bmp", 0 );
	D3DTextr_CreateTextureFromFile( "build4.bmp", 0 );
	D3DTextr_CreateTextureFromFile( "clouds.bmp", 0 );
    D3DTextr_RestoreAllTextures( lpDevice );
	lpBuildText[0]=D3DTextr_GetSurface( "build1.bmp" );
	lpBuildText[1]=D3DTextr_GetSurface( "build2.bmp" );
	lpBuildText[2]=D3DTextr_GetSurface( "build3.bmp" );
	lpBuildText[3]=D3DTextr_GetSurface( "build4.bmp" );
    lpClouds=D3DTextr_GetSurface( "clouds.bmp" );

	// load the helicopter model

    lpXFileCar=new CD3DFile();
    if( FAILED( lpXFileCar->Load("car.x"))){
	
	} else {
		lpXFileCar->Scale(20.0f);
	};
    
	// load the car model

    lpXFileHelo=new CD3DFile();
    if( FAILED( lpXFileHelo->Load("heli.x"))){
	
	} else {
		lpXFileHelo->Scale(20.0f);
	};
    
	lpDevice->LightEnable(0,TRUE);

	// create underlying pavement

	cubes[cube_cnt]=new CCube(D3DVECTOR(-3250.0f,-10.0f,-3250.0f),
							   D3DVECTOR(6500.0f,10.0f,6500.0f),
							   0.2f,0.2f,0.2f);
	cube_cnt++;

	// create cubes on a grid

	for (int i=0;i<6;i++) { 
		for (int j=0;j<6;j++) {
			float x=-3250.0f+1100.0f*i;
			float z=-3250.0f+1100.0f*j;
			cubes[cube_cnt]=new CCube(D3DVECTOR(x,0.0f,z),
									  D3DVECTOR(800.0f,5.0f,800.0f),
									  0.6f,0.6f,0.6f);
			cube_cnt++;
			for (int k=0;k<4;k++) {
				for (int l=0;l<4;l++) {
					cubes[cube_cnt]=new CCube(D3DVECTOR(x+20.0f+195.0f*k,
														0.0f,
														z+20.0f+195.0f*l),
											  D3DVECTOR(150.0f,
														350.0f+250.0f*rand()/(float)RAND_MAX,
														150.0f),
											  0.8f,0.8f,0.65f,
											  lpBuildText[rand()&0x03]);
					cube_cnt++;
				}
			}
		}
	}

	// create hellicopter object

	chopper=new CHelicopter(D3DVECTOR(0,900,0),D3DVECTOR(0.0f,0.0f,0.0f),lpXFileHelo);

	// create user vehicle, which handles motion and 
	// determines te users view

	scene=new CScene(D3DVECTOR(0.0f,300.0f,0.0f),
					D3DVECTOR(0.0f,0.0f,0.0f));
}

	float cloud_ctr=0.0f;

void render_frame(float elapsed)
{
	// recover any lost surfaces

	if (lpDDSPrimary->IsLost()==DDERR_SURFACELOST)
		lpDDSPrimary->Restore();
	if (lpDDSBack->IsLost()==DDERR_SURFACELOST)
		lpDDSBack->Restore();

	// calculate viewer movement and positioning

	D3DMATRIX view_matrix=scene->calc_move(elapsed);

	lpDevice->SetTransform(D3DTRANSFORMSTATE_VIEW,&view_matrix);

	D3DTLVERTEX g_Background[4];
    g_Background[0] = D3DTLVERTEX( D3DVECTOR( 0.0f, 381.0f, 0.9999f ), 0.5f,D3DRGB(0.1f,0.5f,0.8f), 0, 0.0f, 1.0f );
    g_Background[1] = D3DTLVERTEX( D3DVECTOR( 0.0f, 0.0f, 0.9999f ), 0.5f, D3DRGB(0.2f,0.6f,0.6f), 0, 0.0f, 0.0f );
    g_Background[2] = D3DTLVERTEX( D3DVECTOR( 640.0f, 381.0f, 0.9999f ), 0.5f, D3DRGB(0.23f,0.6f,0.8f), 0, 1.0f, 1.0f );
    g_Background[3] = D3DTLVERTEX( D3DVECTOR( 640.0f, 0.0f, 0.9999f ), 0.5f, D3DRGB(0.15f,0.6f,0.76f), 0, 1.0f, 0.0f );
	g_Background[0].color=g_Background[1].color=
	g_Background[2].color=g_Background[3].color=D3DRGB(0.2f,0.6f,0.6f);

//	renderState.set_texture(cloud_texture);
		FLOAT u = -scene->cur_ang.y*0.64f+cloud_ctr;
		cloud_ctr+=0.003f*elapsed;
		g_Background[0].tu = u + 0.5f;
		g_Background[1].tu = u;
		g_Background[2].tu = u + 1.5f;
		g_Background[3].tu = u + 1.0f;
		u=-cloud_ctr*3.0f;
		g_Background[0].tv = g_Background[2].tv = u;
		g_Background[1].tv = g_Background[3].tv = u + 1.0f;

 	// clear the viewport

    lpDevice->Clear(0,NULL,D3DCLEAR_ZBUFFER|D3DCLEAR_TARGET,0,1.0f,0);

	// start the scene render

	if( SUCCEEDED( lpDevice->BeginScene() ) ) {

		lpDevice->SetTexture( 0, lpClouds );
		lpDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);
		lpDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX,
								   g_Background, 4, 0);
		lpDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);

		// loop through the cubes and draw

		for (int i=0;i<cube_cnt;i++) 
			cubes[i]->draw(lpDevice);

		scene->draw(lpDevice);

		if (chopper)
			chopper->draw(lpDevice,elapsed);
		D3DMATRIX world;
		if (lpXFileCar) {
			D3DUtil_SetTranslateMatrix(world,0,40,0);
			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD,&world);
			lpDevice->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE);
			lpXFileCar->Render(lpDevice);
			D3DUtil_SetIdentityMatrix(world);
			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD,&world);
			lpDevice->SetRenderState(D3DRENDERSTATE_LIGHTING,FALSE);
		}

		// end the scene

		lpDevice->EndScene();
	}

	// flip to the primary surface

	lpDDSPrimary->Flip(0,DDFLIP_WAIT);
}

//------ Function to Initialize DirectDraw and the Application ------//

static BOOL Init(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASS                    wc;

    // Set up and register window class

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC) WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(DWORD);
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClass;
    if (!RegisterClass(&wc)) {
		ErrStr=Err_Reg_Class;
        return FALSE;
	}

    // Get dimensions of display

    int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create a window and display

	HWND hWnd;

    hWnd = CreateWindow(szClass,							// class
                        szCaption,							// caption
						WS_VISIBLE|WS_POPUP,				// style 
						0,									// left
						0,									// top
						ScreenWidth,						// width
						ScreenHeight,						// height
                        NULL,								// parent window
                        NULL,								// menu 
                        hInstance,							// instance
                        NULL);								// parms
    if (!hWnd) {
		ErrStr=Err_Create_Win;
        return FALSE;
	}
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	// initialze DirectDraw

	if (!init_ddraw(hWnd)) return FALSE;

	// initialize Direct3D

	if (!init_d3d()) return FALSE;

	// create 3D objects

	create_objects();

	// return success to caller

	return TRUE;
}

//------ Application Loop ------//

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	LONGLONG cur_time;       // current time
	LONGLONG perf_cnt;       // performance timer frequency
	BOOL perf_flag=FALSE;    // flag determining which timer to use
	LONGLONG last_time=0;	 // time of previous frame
	float time_elapsed;	 // time since previous frame
	float time_scale;		 // scaling factor for time

	// initialize the application, exit on failure

    if (!Init(hInstance, nCmdShow)) {
		Cleanup();
        return FALSE;
	}

	// is there a performance counter available? 

	if (QueryPerformanceFrequency((LARGE_INTEGER *) &perf_cnt)) { 

		// yes, set timer info and get starting time

		perf_flag=TRUE;
		QueryPerformanceCounter((LARGE_INTEGER *) &last_time); 
		time_scale=1.0f/perf_cnt;

	} else { 

		// no performance counter, read in using timeGetTime 

		last_time=timeGetTime(); 
		time_scale=0.001f;
	} 

    // Now we're ready to recieve and process Windows messages.

    BOOL bGotMsg;
    MSG  msg;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	
    while( WM_QUIT != msg.message  )
    {
        bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
        if( bGotMsg )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        } else {
			
			// use the appropriate method to get time 
			// and calculate elapsed time since last frame

			if (perf_flag) 
				QueryPerformanceCounter((LARGE_INTEGER *) &cur_time); 
			else 
				cur_time=timeGetTime(); 

			// calculate elapsed time

			time_elapsed=(cur_time-last_time)*time_scale;

			// save frame time

			last_time=cur_time;
				
			// render the frame
			
			render_frame(time_elapsed);
		}
    }

	// return final message

    return msg.wParam;
}


