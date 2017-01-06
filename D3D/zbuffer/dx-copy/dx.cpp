//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "dx.h"

#define STRICT
#define D3D_OVERLOADS
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <d3d.h>
#include "resource.h"
#include "mmsystem.h"
#include "math.hpp"
#include "D3DUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Local variables for the DirectDraw and Direct3D interface.
//
// Note: A real programmer would not use global variables for these objects,
// and use encapsulation instead. As it turns out, after initialization, any
// Direct3D app can make do with only a LPDIRECT3DDEVICE7 parameter, and deduct
// all other interfaces from that.
//-----------------------------------------------------------------------------
static LPDIRECTDRAW7        g_pDD            = NULL;
static LPDIRECTDRAWSURFACE7 g_pddsPrimary    = NULL;
static LPDIRECTDRAWSURFACE7 g_pddsBackBuffer = NULL;
static LPDIRECTDRAWSURFACE7 g_pddsZBuffer    = NULL; // Z-buffer surface (new)
static LPDIRECT3D7          g_pD3D           = NULL;
static LPDIRECT3DDEVICE7    g_pd3dDevice     = NULL;
static RECT                 g_rcScreenRect;

//-----------------------------------------------------------------------------
// Local function-prototypes
//-----------------------------------------------------------------------------
HRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
HRESULT Initialize3DEnvironment( HWND, GUID*, const GUID* );
HRESULT Cleanup3DEnvironment();
HRESULT Render3DEnvironment();
HRESULT RestoreSurfaces();
HRESULT App_InitDeviceObjects( LPDIRECT3DDEVICE7 );
HRESULT App_FrameMove( LPDIRECT3DDEVICE7, FLOAT );
HRESULT App_Render( LPDIRECT3DDEVICE7 );

//LPDIRECT3DDEVICE7 pd3dDevice = NULL;

#define ORBIT			8.0f

//float time_scale=0.001f;
//LONGLONG last_time=0;	 // time of previous frame
//float rotAngle;
//float rotVel=0.0f;			// current velociy of spin
float lift = 0.0f;
//float elevation=0.0f;//350.0f;		// current elevation

float rotAngle = 0;


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything, and goes into a
//       message-processing loop. Idle time is used to render the scene.
//-----------------------------------------------------------------------------
HWND CWindow(HINSTANCE hInst)//, HINSTANCE, LPSTR strCmdLine, INT )
{
	// Register the window class
    WNDCLASS wndClass = { CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInst,
                          NULL,//LoadIcon( hInst, MAKEINTRESOURCE(IDI_MAIN_ICON)),
                          NULL,//LoadCursor(NULL, IDC_ARROW),
                          (HBRUSH)GetStockObject(WHITE_BRUSH), NULL,
                          TEXT("Render Window") };
    RegisterClass( &wndClass );

    // Create our main window
    HWND hWnd = CreateWindow( TEXT("Render Window"),
		                      TEXT("D3D Tutorial: Adding a Z-buffer"),
                              WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                              CW_USEDEFAULT, 300, 300, 0L, 0L, hInst, 0L );
    ShowWindow( hWnd, SW_SHOWNORMAL );
    UpdateWindow( hWnd );

    return hWnd;
}

//-----------------------------------------------------------------------------
// Name: WndProc()
// Desc: This is the basic Windows-programming function that processes
//       Windows messages. We need to handle window movement, painting,
//       and destruction.
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
        case WM_KEYDOWN:

        switch(wParam)
        {
/*            case VK_UP: g_pd3dDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, FALSE ); break;
            case VK_DOWN: g_pd3dDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, TRUE ); break;
*/
           case VK_UP:
				lift+=0.1f;
				break;

			case VK_DOWN:
				lift-=0.1f;
				break;

            case VK_LEFT:
                rotAngle-=0.1f;
                break;

            case VK_RIGHT:
                rotAngle+=0.1f;
                break;
        }

        break;


       case WM_KEYUP:

       switch (wParam)
       {
			case VK_UP:
			case VK_DOWN:
//				lift=0.0f;
				break;

            case VK_RIGHT:
            case VK_LEFT:
//                rotAngle =0.0;
                break;
        }
        break;


        case WM_CLOSE:
            DestroyWindow( hWnd );
            return 0;
        
        case WM_DESTROY:
            Cleanup3DEnvironment();
            PostQuitMessage(0);
            return 0L;
    }

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Note: From this point on, the code is DirectX specific support for the app.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: EnumZBufferCallback()
// Desc: Enumeration function to report valid pixel formats for z-buffers.
//-----------------------------------------------------------------------------
static HRESULT WINAPI EnumZBufferCallback( DDPIXELFORMAT* pddpf,
                                           VOID* pddpfDesired )
{
	// For this tutorial, we are only interested in z-buffers, so ignore any
	// other formats (e.g. DDPF_STENCILBUFFER) that get enumerated. An app
	// could also check the depth of the z-buffer (16-bit, etc,) and make a
	// choice based on that, as well. For this tutorial, we'll take the first
	// one we get.
    if( pddpf->dwFlags == DDPF_ZBUFFER )
    {
        memcpy( pddpfDesired, pddpf, sizeof(DDPIXELFORMAT) );

        // Return with D3DENUMRET_CANCEL to end the search.
		return D3DENUMRET_CANCEL;
    }

    // Return with D3DENUMRET_OK to continue the search.
    return D3DENUMRET_OK;
}




//-----------------------------------------------------------------------------
// Name: Initialize3DEnvironment()
// Desc: This function initializes all the DirectDraw/Direct3D objects used for
//       3D-rendering. This code is expanded from the Step 1 tutorial, in that
//       it adds a z-buffer.
//-----------------------------------------------------------------------------
HRESULT Initialize3DEnvironment( HWND hWnd, GUID* pDriverGUID,
								 const GUID* pDeviceGUID )
{
	HRESULT hr;

	// Create the IDirectDraw interface. The first parameter is the GUID,
	// which is allowed to be NULL. If there are more than one DirectDraw
	// drivers on the system, a NULL guid requests the primary driver. For
	// non-GDI hardware cards like the 3DFX and PowerVR, the guid would need
	// to be explicity specified . (Note: these guids are normally obtained
	// from enumeration, which is convered in a subsequent tutorial.)
	hr = DirectDrawCreateEx( pDriverGUID, (VOID**)&g_pDD, IID_IDirectDraw7,
		                     NULL );
	if( FAILED( hr ) )
		return hr;

    // Set the Windows cooperative level. This is where we tell the system
	// whether wew will be rendering in fullscreen mode or in a window. Note
	// that some hardware (non-GDI) may not be able to render into a window.
	// The flag DDSCL_NORMAL specifies windowed mode. Using fullscreen mode
	// is the topic of a subsequent tutorial. The DDSCL_FPUSETUP flag is a 
	// hint to DirectX to optomize floating points calculations. See the docs
	// for more info on this. Note: this call could fail if another application
	// already controls a fullscreen, exclusive mode.
    hr = g_pDD->SetCooperativeLevel( hWnd, DDSCL_NORMAL );
	if( FAILED( hr ) )
		return hr;

	// Initialize a surface description structure for the primary surface. The
	// primary surface represents the entire display, with dimensions and a
	// pixel format of the display. Therefore, none of that information needs
	// to be specified in order to create the primary surface.
	DDSURFACEDESC2 ddsd;
	ZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
	ddsd.dwSize         = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags        = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	// Create the primary surface.
	hr = g_pDD->CreateSurface( &ddsd, &g_pddsPrimary, NULL );
	if( FAILED( hr ) )
		return hr;

	// Setup a surface description to create a backbuffer. This is an
	// offscreen plain surface with dimensions equal to our window size.
	// The DDSCAPS_3DDEVICE is needed so we can later query this surface
	// for an IDirect3DDevice interface.
	ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;

	// Set the dimensions of the backbuffer. Note that if our window changes
	// size, we need to destroy this surface and create a new one.
	GetClientRect( hWnd, &g_rcScreenRect );
	ClientToScreen( hWnd, (POINT*)&g_rcScreenRect.left );
	ClientToScreen( hWnd, (POINT*)&g_rcScreenRect.right );
	ddsd.dwWidth  = g_rcScreenRect.right - g_rcScreenRect.left;
	ddsd.dwHeight = g_rcScreenRect.bottom - g_rcScreenRect.top;

	// Create the backbuffer. The most likely reason for failure is running
	// out of video memory. (A more sophisticated app should handle this.)
	hr = g_pDD->CreateSurface( &ddsd, &g_pddsBackBuffer, NULL );
	if( FAILED( hr ) )
		return hr;

	// Note: if using a z-buffer, the zbuffer surface creation would go around
	// here. However, z-buffer usage is the topic of a subsequent tutorial.

	// Create a clipper object which handles all our clipping for cases when
	// our window is partially obscured by other windows. This is not needed
	// for apps running in fullscreen mode.
	LPDIRECTDRAWCLIPPER pcClipper;
	hr = g_pDD->CreateClipper( 0, &pcClipper, NULL );
	if( FAILED( hr ) )
		return hr;

	// Associate the clipper with our window. Note that, afterwards, the
	// clipper is internally referenced by the primary surface, so it is safe
	// to release our local reference to it.
	pcClipper->SetHWnd( 0, hWnd );
	g_pddsPrimary->SetClipper( pcClipper );
	pcClipper->Release();

    // Query DirectDraw for access to Direct3D
    g_pDD->QueryInterface( IID_IDirect3D7, (VOID**)&g_pD3D );
    if( FAILED( hr) )
		return hr;

	//-------------------------------------------------------------------------
	// Create the z-buffer AFTER creating the backbuffer and BEFORE creating
	// the d3ddevice.
	//
    // Note: before creating the z-buffer, apps may want to check the device
	// caps for the D3DPRASTERCAPS_ZBUFFERLESSHSR flag. This flag is true for
	// certain hardware that can do HSR (hidden-surface-removal) without a
	// z-buffer. For those devices, there is no need to create a z-buffer.
	//-------------------------------------------------------------------------

	DDPIXELFORMAT ddpfZBuffer;
	g_pD3D->EnumZBufferFormats( *pDeviceGUID,
		                        EnumZBufferCallback, (VOID*)&ddpfZBuffer );

	// If we found a good zbuffer format, then the dwSize field will be
	// properly set during enumeration. Else, we have a problem and will exit.
    if( sizeof(DDPIXELFORMAT) != ddpfZBuffer.dwSize )
        return E_FAIL;

    // Get z-buffer dimensions from the render target
    // Setup the surface desc for the z-buffer.
    ddsd.dwFlags        = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
	ddsd.dwWidth        = g_rcScreenRect.right - g_rcScreenRect.left;
	ddsd.dwHeight       = g_rcScreenRect.bottom - g_rcScreenRect.top;
    memcpy( &ddsd.ddpfPixelFormat, &ddpfZBuffer, sizeof(DDPIXELFORMAT) );

	// For hardware devices, the z-buffer should be in video memory. For
	// software devices, create the z-buffer in system memory
	if( IsEqualIID( *pDeviceGUID, IID_IDirect3DHALDevice ) )
		ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
	else
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

    // Create and attach a z-buffer. Real apps should be able to handle an
	// error here (DDERR_OUTOFVIDEOMEMORY may be encountered). For this 
	// tutorial, though, we are simply going to exit ungracefully.
    if( FAILED( hr = g_pDD->CreateSurface( &ddsd, &g_pddsZBuffer, NULL ) ) )
		return hr;

	// Attach the z-buffer to the back buffer.
    if( FAILED( hr = g_pddsBackBuffer->AddAttachedSurface( g_pddsZBuffer ) ) )
		return hr;

	//-------------------------------------------------------------------------
	// End of z-buffer creation code.
	//
	// Before rendering, don't forget to enable the z-buffer with the 
	// appropiate D3DRENDERSTATE's.
	//-------------------------------------------------------------------------

	// Before creating the device, check that we are NOT in a palettized
	// display. That case will cause CreateDevice() to fail, since this simple 
	// tutorial does not bother with palettes.
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	g_pDD->GetDisplayMode( &ddsd );
	if( ddsd.ddpfPixelFormat.dwRGBBitCount <= 8 )
		return DDERR_INVALIDMODE;

	// Create the device. The device is created off of our back buffer, which
	// becomes the render target for the newly created device. Note that the
	// z-buffer must be created BEFORE the device

    if( FAILED( hr = g_pD3D->CreateDevice( *pDeviceGUID, g_pddsBackBuffer,
                                           &g_pd3dDevice ) ) )
	{
		// This call could fail for many reasons. The most likely cause is
		// that we specifically requested a hardware device, without knowing
		// whether there is even a 3D card installed in the system. Another
		// possibility is the hardware is incompatible with the current display
		// mode (the correct implementation would use enumeration for this.)
		return hr;
	}

    // Create the viewport
	DWORD dwRenderWidth  = g_rcScreenRect.right - g_rcScreenRect.left;
	DWORD dwRenderHeight = g_rcScreenRect.bottom - g_rcScreenRect.top;
	D3DVIEWPORT7 vp = { 0, 0, dwRenderWidth, dwRenderHeight, 0.0f, 1.0f };
    hr = g_pd3dDevice->SetViewport( &vp );
	if( FAILED( hr ) )
		return hr;

	// Finish by setting up our scene
	return App_InitDeviceObjects(g_pd3dDevice);
}

//-----------------------------------------------------------------------------
// Name: Cleanup3DEnvironment()
// Desc: Releases all the resources used by the app. Note the check for
//       reference counts when releasing the D3DDevice and DDraw objects. If
//       these ref counts are non-zero, then something was not cleaned up
//       correctly.
//-----------------------------------------------------------------------------
HRESULT Cleanup3DEnvironment()
{
	// Cleanup any objects created for the scene
//	App_DeleteDeviceObjects( g_pd3dDevice );

	// Release the DDraw and D3D objects used by the app
    if( g_pddsZBuffer )    g_pddsZBuffer->Release();
	if( g_pD3D )           g_pD3D->Release();
	if( g_pddsBackBuffer ) g_pddsBackBuffer->Release();
	if( g_pddsPrimary )    g_pddsPrimary->Release();

    // Do a safe check for releasing the D3DDEVICE. RefCount should be zero.
    if( g_pd3dDevice )
        if( 0 < g_pd3dDevice->Release() )
			return E_FAIL;

	// Do a safe check for releasing DDRAW. RefCount should be zero.
    if( g_pDD )
        if( 0 < g_pDD->Release() )
			return E_FAIL;

    g_pddsZBuffer    = NULL;
	g_pd3dDevice     = NULL;
	g_pD3D           = NULL;
	g_pddsBackBuffer = NULL;
	g_pddsPrimary    = NULL;
	g_pDD            = NULL;

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Render3DEnvironment()
// Desc: Draws the scene. There are three steps here:
//       (1) Animate the scene
//       (2) Render the scene
//       (3) Show the frame (copy backbuffer contents to the primary).
//-----------------------------------------------------------------------------
HRESULT Render3DEnvironment()
{
	// Call the app specific function to framemove (animate) the scene
    App_FrameMove( g_pd3dDevice, ((FLOAT)clock())/CLOCKS_PER_SEC );

    // Call the app specific function to render the scene
    App_Render( g_pd3dDevice );

    // Show the frame on the primary surface. Note: this is the best place to
	// check for "lost" surfaces. Surfaces can be lost if something caused
	// them to temporary lose their video memory. "Lost" surfaces simply
	// need to be restored before continuing.

    //******************************************************************************

//    float cur_time=timeGetTime();

    // calculate elapsed time

//    float elapsed=(cur_time-last_time)*time_scale;

//  	elevation+=lift*elapsed;
//	rotAngle+=rotVel*elapsed;

	// calculate current viewer position

	D3DVECTOR view_loc;
	view_loc.y=lift;//elevation;				// set elevation
	view_loc.x=sin(rotAngle)*ORBIT;		// calculate position on x,z plane
	view_loc.z=cos(rotAngle)*ORBIT;

	// create and set the view matrix

	D3DMATRIX view_matrix;
    view_matrix = ViewMatrix(
						  view_loc,
						  D3DVECTOR(0.0f,0.0f,0.0f),
						  D3DVECTOR(0.0f,1.0f,0.0f));

	g_pd3dDevice->SetTransform(D3DTRANSFORMSTATE_VIEW,&view_matrix);

    //******************************************************************************

    if( NULL == g_pddsPrimary )
		return E_FAIL;

    // We are in windowed mode, so perform a blit from the backbuffer to the
	// correct position on the primary surface
    HRESULT hr = g_pddsPrimary->Blt(&g_rcScreenRect, g_pddsBackBuffer, NULL, DDBLT_WAIT, NULL);

    if( DDERR_SURFACELOST == hr )
		RestoreSurfaces();

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: RestoreSurfaces()
// Desc: Checks for lost surfaces and restores them if lost.
//-----------------------------------------------------------------------------
HRESULT RestoreSurfaces()
{
    // Check/restore the primary surface
    if( g_pddsPrimary )
        if( g_pddsPrimary->IsLost() )
            g_pddsPrimary->Restore();
    
    // Check/restore the back buffer
    if( g_pddsBackBuffer )
        if( g_pddsBackBuffer->IsLost() )
            g_pddsBackBuffer->Restore();

    // Check/restore the z-buffer
    if( g_pddsZBuffer )
        if( g_pddsZBuffer->IsLost() )
            g_pddsZBuffer->Restore();

    return S_OK;
}

//-----------------------------------------------------------------------------
// Desc: Simple tutorial code to show how to enable z-buffering. The z-buffer
//       itself is created in the winmain.cpp file. This file controls
//       rendering and the setting of renderstates (some of which affect
//       z-buffering).

//-----------------------------------------------------------------------------

#define STRICT
#define D3D_OVERLOADS
#include <math.h>
#include <d3d.h>


//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define NUM_OBJECTS 2
D3DMATRIX           g_matLocal[2];
D3DVERTEX           g_pvTriangleVertices[6];


//-----------------------------------------------------------------------------
// Name: App_InitDeviceObjects()
// Desc: Initialize scene objects. This function is called after all the
//       DirectDraw and Direct3D objects have been initialized. It makes sense
//       to structure code this way, separating the DDraw/D3D initialization
//       code from the app-specific intialization code.
//-----------------------------------------------------------------------------
HRESULT App_InitDeviceObjects( LPDIRECT3DDEVICE7 pd3dDevice )
{
	// Data for the geometry of the triangle. Note that this tutorial only
	// uses ambient lighting, so the vertices' normals are not actually used.
	D3DVECTOR p1( 0.0f, 3.0f, 0.0f );
	D3DVECTOR p2( 3.0f,-3.0f, 0.0f );
	D3DVECTOR p3(-3.0f,-3.0f, 0.0f );
	D3DVECTOR vNormal( 0.0f, 0.0f, 1.0f );

	// Initialize the 3 vertices for the front of the triangle
	g_pvTriangleVertices[0] = D3DVERTEX( p1, vNormal, 0.0f, 0.0f );
	g_pvTriangleVertices[1] = D3DVERTEX( p2, vNormal, 0.0f, 0.0f );
	g_pvTriangleVertices[2] = D3DVERTEX( p3, vNormal, 0.0f, 0.0f );
    
	// Initialize the 3 vertices for the back of the triangle
	g_pvTriangleVertices[3] = D3DVERTEX( p1, -vNormal, 0.0f, 0.0f );
	g_pvTriangleVertices[4] = D3DVERTEX( p3, -vNormal, 0.0f, 0.0f );
	g_pvTriangleVertices[5] = D3DVERTEX( p2, -vNormal, 0.0f, 0.0f );
    
	// Set the material as yellow. We're setting the ambient color here
	// since this tutorial only uses ambient lighting. For apps that use real
	// lights, the diffuse and specular values should be set. (In addition, the
	// polygons' vertices need normals for true lighting.)
    D3DMATERIAL7 mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.ambient.r = 1.0f;
    mtrl.ambient.g = 1.0f;
    mtrl.ambient.b = 1.0f;
    pd3dDevice->SetMaterial( &mtrl );

	// The ambient lighting value is another state to set. Here, we are turning
	// ambient lighting on to full white.
    pd3dDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xffffffff );

    // Set the transform matrices. Direct3D uses three independant matrices:
	// the world matrix, the view matrix, and the projection matrix. For
	// convienence, we are first setting up an identity matrix.
    D3DMATRIX mat;
	mat._11 = mat._22 = mat._33 = mat._44 = 1.0f;
	mat._12 = mat._13 = mat._14 = mat._41 = 0.0f;
	mat._21 = mat._23 = mat._24 = mat._42 = 0.0f;
	mat._31 = mat._32 = mat._34 = mat._43 = 0.0f;

	// The world matrix controls the position and orientation of the polygons
	// in world space. We'll use it later to spin the triangle.
	D3DMATRIX matWorld = mat;
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &matWorld );

	// The view matrix defines the position and orientation of the camera.
	// Here, we are just moving it back along the z-axis by 10 units.
	D3DMATRIX matView = mat;
	matView._43 = 10.0f;
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_VIEW, &matView );

	// The projection matrix defines how the 3D scene is "projected" onto the
	// 2D render target (the backbuffer surface). Refer to the docs for more
	// info about projection matrices.
	D3DMATRIX matProj = mat;
	matProj._11 =  2.0f;
	matProj._22 =  2.0f;
	matProj._34 =  1.0f;
	matProj._43 = -1.0f;
	matProj._44 =  0.0f;
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProj );

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_FrameMove()
// Desc: Called once per frame, the call is used for animating the scene. The
//       device is used for changing various render states, and the timekey is
//       used for timing of the dynamics of the scene.
//-----------------------------------------------------------------------------
HRESULT App_FrameMove( LPDIRECT3DDEVICE7 pd3dDevice, FLOAT fTimeKey )
{
    // For this tutorial, we are rotating several triangles about the y-axis.
	// (Note: the triangles are meant to intersect, to show how z-buffering
	// handles hidden-surface removal.)

	// For each object, set up a local rotation matrix to be applied right
	// before rendering the object's polygons.
	for( int i=0; i<NUM_OBJECTS; i++ )
	{
		ZeroMemory( &g_matLocal[i], sizeof(D3DMATRIX) );
		g_matLocal[i]._11 = (FLOAT)cos( fTimeKey + (3.14159*i)/NUM_OBJECTS );
		g_matLocal[i]._33 = (FLOAT)cos( fTimeKey + (3.14159*i)/NUM_OBJECTS );
		g_matLocal[i]._13 = (FLOAT)sin( fTimeKey + (3.14159*i)/NUM_OBJECTS );
		g_matLocal[i]._31 = (FLOAT)sin( fTimeKey + (3.14159*i)/NUM_OBJECTS );
		g_matLocal[i]._22 = g_matLocal[i]._44 = 1.0f;
	}

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_Render()
// Desc: Renders the scene. This tutorial draws a bunch of intersecting
//       triangles that are rotating about the y-axis. Without z-buffering,
//       the polygons could not be drawn correctly (unless the app performed
//       complex polygon-division routines and sorted the polygons in back-to-
//       front order.)
//-----------------------------------------------------------------------------
HRESULT App_Render( LPDIRECT3DDEVICE7 pd3dDevice )
{
    // Clear the viewport to a blue color. Also "clear" the z-buffer to the
	// value 1.0 (which represents the far clipping plane).
    pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		               0x000000ff, 1.0f, 0L );

    // Begin the scene
    if( FAILED( pd3dDevice->BeginScene() ) )
		return E_FAIL;

	// Enable z-buffering. (Note: we don't really need to do this every frame.)
//    pd3dDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, FALSE );

	// Draw all the objects. Note: you can tweak the above statement to disable
	// the z-buffer, and compare the difference in output. With z-buffering,
	// the inter-penetrating triangles are drawn correctly.
	for( int i=0; i<NUM_OBJECTS; i++ )
	{
		// Alternate the color of every other object
		DWORD dwColor = ( i%2 ) ? 0x0000ff00 : 0x00ffff00;
	    pd3dDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, dwColor );

		// Set the local matrix for the object
		pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &g_matLocal[i] );

		// Draw the object. (Note: Subsequent tutorials will go into more
		// detail on the various calls for drawing polygons.)
		pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, D3DFVF_VERTEX,
			                       g_pvTriangleVertices, 6, NULL );
	}

    // End the scene.
    pd3dDevice->EndScene();

    return S_OK;
}



//******************************************************************************
//*

void __fastcall TForm1::FormShow(TObject *Sender)
{
//last_time=timeGetTime();
//time_scale=0.001f;

    Initialize3DEnvironment( CWindow(HInstance) , NULL, &IID_IDirect3DRGBDevice );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    Render3DEnvironment();
}
//---------------------------------------------------------------------------


