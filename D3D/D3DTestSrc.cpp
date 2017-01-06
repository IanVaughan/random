//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "D3DTestSrc.h"
#include <math.hpp>
#include "math.h"
#include <time.h>
#include "D3DError.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TD3DTestForm *D3DTestForm;

static LPDIRECTDRAW7        g_pDD            = NULL;
static LPDIRECTDRAWSURFACE7 g_pddsPrimary    = NULL;
static LPDIRECTDRAWSURFACE7 g_pddsBackBuffer = NULL;
static LPDIRECTDRAWSURFACE7 g_pddsZBuffer    = NULL; // Z-buffer surface (new)
static LPDIRECT3D7          g_pD3D           = NULL;
static LPDIRECT3DDEVICE7    g_pd3dDevice     = NULL;
static RECT                 g_rcScreenRect;

LPDIRECT3DMATERIAL3 g_pmtrlObjectMtrl = NULL;
D3DVERTEX           g_pvTriangleVertices[6];
D3DVERTEX           g_pvTriangleVertices2[6];

//static BOOL g_bActive  = FALSE; // Whether the app is active (not minimized)
//static BOOL g_bReady   = FALSE; // Whether the app is ready to render frames

static HRESULT WINAPI EnumZBufferCallback( DDPIXELFORMAT* pddpf, VOID* pddpfDesired );

//---------------------------------------------------------------------------

RECT g_rcViewportRect;
D3DRECT g_rcViewportRect3D;

//mine
LPDIRECT3DRMMESHBUILDER m_MeshBld;
LPDIRECT3DRMFRAME m_Frame;

TD3DError *err;

//---------------------------------------------------------------------------

__fastcall TD3DTestForm::TD3DTestForm(TComponent* Owner) : TForm(Owner)
{
    //timer
    TTimer* timer = new TTimer(this);
    timer->Interval = 10;
    timer->Enabled = false;
    timer->OnTimer = timerRunning;

    err=new TD3DError();

    //3d
    HRESULT res = CreateEverything();
    if(res!=DD_OK)
    {
        err->Display(res);
        exit(0);
    }

//    Initialize3DEnvironment( Handle );
//    App_InitDeviceObjects( g_pd3dDevice );

    //ready, go!
    timer->Enabled = true;
}
//---------------------------------------------------------------------------

__fastcall TD3DTestForm::~TD3DTestForm()
{
    Cleanup3DEnvironment();
}
//---------------------------------------------------------------------------

HRESULT TD3DTestForm::CreateEverything()
{
    HRESULT res;
    // Cleanup any objects that might've been created before
    res = Cleanup3DEnvironment();
    if(res!=DD_OK)
        return res;


	// Create the D3D environment, at first, trying the HAL
/*	if( SUCCEEDED( Initialize3DEnvironment( Handle, NULL,  &IID_IDirect3DHALDevice ) ) )
		return S_OK;

	// Else, cleanup objects potentially created during the failed
	// initialization attempt.
	Cleanup3DEnvironment();
*/
	res = Initialize3DEnvironment( Handle, NULL, &IID_IDirect3DRGBDevice );
    if(res!=DD_OK)
        return res;

    return S_OK;
}
//---------------------------------------------------------------------------

HRESULT TD3DTestForm::Initialize3DEnvironment( HWND hWnd, GUID* pDriverGUID,
								                const GUID* pDeviceGUID )
{
    HRESULT hr;

    hr = DirectDrawCreateEx( pDriverGUID,/*NULL, */(VOID**)&g_pDD, IID_IDirectDraw7, NULL );
    if( FAILED( hr ) )
        return hr;

    hr = g_pDD->SetCooperativeLevel( hWnd, DDSCL_ALLOWREBOOT | DDSCL_FULLSCREEN);// | DDSCL_EXCLUSIVE);//DDSCL_NORMAL );
    if( FAILED( hr ) )
        return hr;

    DDSURFACEDESC2 ddsd;
    ZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    // Create the primary surface.
    hr = g_pDD->CreateSurface( &ddsd, &g_pddsPrimary, NULL );
    if( FAILED( hr ) )
        return hr;

    ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE ;

    // Set the dimensions of the back buffer. Note that if our window changes
    // size, we need to destroy this surface and create a new one.
    ::GetClientRect( hWnd, &g_rcScreenRect );
    ::GetClientRect( hWnd, &g_rcViewportRect );

    ::ClientToScreen( hWnd, (POINT*)&g_rcScreenRect.left );
    ::ClientToScreen( hWnd, (POINT*)&g_rcScreenRect.right );
    ddsd.dwWidth  = g_rcScreenRect.right - g_rcScreenRect.left;
    ddsd.dwHeight = g_rcScreenRect.bottom - g_rcScreenRect.top;

    // Create the backbuffer. The most likely reason for failure is running
    // out of video memory. (A more sophisticated app should handle this.)
    hr = g_pDD->CreateSurface( &ddsd, &g_pddsBackBuffer, NULL );
    if( FAILED( hr ) )
        return hr;

    LPDIRECTDRAWCLIPPER pcClipper;
    hr = g_pDD->CreateClipper( 0, &pcClipper, NULL );
    if( FAILED( hr ) )
        return hr;

    // Assign it to the window handle, then set
    // the clipper to the desired surface.
    pcClipper->SetHWnd( 0, hWnd );
    g_pddsPrimary->SetClipper( pcClipper );
    pcClipper->Release();

    // Query DirectDraw for access to Direct3D
    g_pDD->QueryInterface( IID_IDirect3D7, (VOID**)&g_pD3D );
    if( FAILED( hr) )
        return hr;

    /*
    Step 1: Enumerate Depth-Buffer Formats  [Language: C++]
    Before you can create a depth buffer you must determine what depth-buffer formats,
    if any, are supported by the rendering device. Call the IDirect3D7::EnumZBufferFormats
    method to enumerate the depth-buffer formats that the device supports. The ZBuffer
    sample uses the following code to enumerate depth-buffer formats:
    */

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
    try{
        hr = g_pD3D->EnumZBufferFormats( *pDeviceGUID, EnumZBufferCallback, (VOID*)&ddpfZBuffer );
    }catch(...){
        if(hr==DD_OK) hr=-99548453156168487474;
        return hr;
    }
    /* Step 2: Create the Depth Buffer  [Language: C++]
    Now that you have chosen the depth-buffer format, you can create the DirectDrawSurface
    object that will become the depth buffer. The pixel format of the surface is
    the one determined through enumeration, but the surface dimensions must be
    identical to the render-target surface to which it will be attached. The ZBuffer
    sample uses the following code for this task:
    */

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

    /*
    The preceding code simply prepares a DDSURFACEDESC2 structure for the depth
    buffer, using the dimensions of the render-target surface calculated from previously
    set global variables. The pixel format information retrieved during the previous
    step, Step 1: Enumerate Depth-Buffer Formats, is copied into the surface description.

    Note  A hardware device can use a depth buffer regardless of its location in
    memory. When using a hardware device, it's best to let the device determine
    the best location for the buffer by omitting the DDSCAPS_VIDEOMEMORY and DDSCAPS_SYSTEMMEMORY
    surface capability flags. However, a software device can only be created if the
    depth buffer exists in system memory. The preceding code checks for this possibility
    and includes the DDSCAPS_SYSTEMMEMORY flag if necessary.

    Once the surface description is ready, the code calls the IDirectDraw7::CreateSurface
    method to create the new depth-buffer surface. After the depth buffer is created,
    it can be attached to the surface that will be used as the render target, as
    described in Step 3: Attach the Depth Buffer.
    */

    /* Step 3: Attach the Depth Buffer
    Once the depth buffer is created, you need to attach it to the surface that
    will be used as the render target. Do this by calling the IDirectDrawSurface7::AddAttachedSurface
    method of the render-target surface. The ZBuffer sample performs this with the following code:
    */

    // Attach the z-buffer to the back buffer.
    if( FAILED( hr = g_pddsBackBuffer->AddAttachedSurface( g_pddsZBuffer ) ) )
		return hr;

    /*
    Once the depth buffer is attached to the render-target surface, the system will
    automatically use the depth buffer whenever depth buffering is enabled, as
    discussed in Step 4: Enable Depth Buffering
    */

	//-------------------------------------------------------------------------
	// End of z-buffer creation code.
	//
	// Before rendering, don't forget to enable the z-buffer with the 
	// appropiate D3DRENDERSTATE's.
	//-------------------------------------------------------------------------

    // Check the display mode, and
    ddsd.dwSize = sizeof(DDSURFACEDESC2);
    g_pDD->GetDisplayMode( &ddsd );
    if( ddsd.ddpfPixelFormat.dwRGBBitCount <= 8 )
        return DDERR_INVALIDMODE;

    // The GUID here is hard coded. In a real-world application
    // this should be retrieved by enumerating devices.
    hr = g_pD3D->CreateDevice( *pDeviceGUID,/*IID_IDirect3DHALDevice, */g_pddsBackBuffer, &g_pd3dDevice );
    if( FAILED( hr ) )
    {
        // If the hardware GUID doesn't work, try a software device.
//        hr = g_pD3D->CreateDevice( IID_IDirect3DRGBDevice, g_pddsBackBuffer, &g_pd3dDevice );
//        if( FAILED( hr ) )
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
	return App_InitDeviceObjects( g_pd3dDevice );

//    return S_OK;
}
//---------------------------------------------------------------------------

HRESULT TD3DTestForm::App_InitDeviceObjects( LPDIRECT3DDEVICE7 pd3dDevice )
{
    // Data for the geometry of the triangle. Note that this tutorial only
    // uses ambient lighting, so the vertices' normals are not actually used.
    D3DVECTOR p1( 0.0f, 3.0f, 0.0f );
    D3DVECTOR p2( 3.0f,-3.0f, 0.0f );
    D3DVECTOR p3(-3.0f,-3.0f, 0.0f );
    D3DVECTOR vNormal( 0.0f, 0.0f, 0.0f );

    g_pvTriangleVertices[0] = D3DVERTEX( p1, vNormal, 0, 0 );
    g_pvTriangleVertices[1] = D3DVERTEX( p2, vNormal, 0, 0 );
    g_pvTriangleVertices[2] = D3DVERTEX( p3, vNormal, 0, 0 );

    g_pvTriangleVertices[3] = D3DVERTEX( p1, -vNormal, 0, 0 );
    g_pvTriangleVertices[4] = D3DVERTEX( p3, -vNormal, 0, 0 );
    g_pvTriangleVertices[5] = D3DVERTEX( p2, -vNormal, 0, 0 );


/*    D3DMATERIAL7 mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.ambient.r = 0.0f;
    mtrl.ambient.g = 1.0f;
    mtrl.ambient.b = 0.0f;
    pd3dDevice->SetMaterial( &mtrl );

    pd3dDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xffffffff );
*/

    //second triangle, infront a bit
    D3DVECTOR p21( 1.0f, 4.0f, 0.01f );
    D3DVECTOR p22( 4.0f,-2.0f, 0.01f );
    D3DVECTOR p23(-2.0f,-2.0f, 0.01f );

    g_pvTriangleVertices2[0] = D3DVERTEX( p21, vNormal, 0, 0 );
    g_pvTriangleVertices2[1] = D3DVERTEX( p22, vNormal, 0, 0 );
    g_pvTriangleVertices2[2] = D3DVERTEX( p23, vNormal, 0, 0 );
    g_pvTriangleVertices2[3] = D3DVERTEX( p21, -vNormal, 0, 0 );
    g_pvTriangleVertices2[4] = D3DVERTEX( p23, -vNormal, 0, 0 );
    g_pvTriangleVertices2[5] = D3DVERTEX( p22, -vNormal, 0, 0 );


//    /*D3DMATERIAL7 */mtrl;
/*    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.ambient.r = 0.0f;
    mtrl.ambient.g = 1.0f;
    mtrl.ambient.b = 1.0f;
    pd3dDevice->SetMaterial( &mtrl );

    // The ambient lighting value is another state to set. Here, we are turning
    // ambient lighting on to full white.
    pd3dDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xffffffff );
*/

    // Start by setting up an identity matrix.
    D3DMATRIX mat;
    mat._11 = mat._22 = mat._33 = mat._44 = 1.0f;
    mat._12 = mat._13 = mat._14 = mat._41 = 0.0f;
    mat._21 = mat._23 = mat._24 = mat._42 = 0.0f;
    mat._31 = mat._32 = mat._34 = mat._43 = 0.0f;
    
    // The world matrix controls the position and orientation 
    // of the polygons in world space. We'll use it later to 
    // spin the triangle.
    D3DMATRIX matWorld = mat;
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &matWorld );

    // The view matrix defines the position and orientation of
    // the camera. Here, we are just moving it back along the z-
    // axis by 10 units.
    D3DMATRIX matView = mat;
    matView._43 = 10.0f;
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_VIEW, &matView );
 
    // The projection matrix defines how the 3-D scene is "projected" 
    // onto the 2-D render target surface. For more information,
    // see "What Is the Projection Transformation?"
 
    // Set up a very simple projection that scales x and y 
    // by 2, and translates z by -1.0.
    D3DMATRIX matProj = mat;
    matProj._11 =  1.0f;
    matProj._22 =  2.0f;
    matProj._34 =  1.0f;
    matProj._43 = -1.0f;
    matProj._44 =  0.0f;
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProj );

     return S_OK;
}
//---------------------------------------------------------------------------

HRESULT TD3DTestForm::App_FrameMove( LPDIRECT3DDEVICE7 pd3dDevice, FLOAT fTimeKey )
{
    // For this simple tutorial, we are rotating the triangle about the y-axis.
    // To do this, just set up a 4x4 matrix defining the rotation, and set it
    // as the new world transform.
    D3DMATRIX matSpin;
    matSpin._11 = matSpin._22 = matSpin._33 = matSpin._44 = 1.0f;
    matSpin._12 = matSpin._13 = matSpin._14 = matSpin._41 = 0.0f;
    matSpin._21 = matSpin._23 = matSpin._24 = matSpin._42 = 0.0f;
    matSpin._31 = matSpin._32 = matSpin._34 = matSpin._43 = 0.0f;
    
    matSpin._11 = (FLOAT)cos( fTimeKey );
    matSpin._33 = (FLOAT)cos( fTimeKey );
    matSpin._13 = -(FLOAT)sin( fTimeKey );
    matSpin._31 = (FLOAT)sin( fTimeKey );
 
//    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &matSpin );

    return S_OK;
}
//---------------------------------------------------------------------------

HRESULT TD3DTestForm::App_Render( LPDIRECT3DDEVICE7 pd3dDevice, D3DRECT* prcViewRect )
{
D3DMATERIAL7 mtrl;
    // Clear the viewport to a blue color.
    pd3dDevice->Clear( 1UL, prcViewRect, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0x000000ff, 1.0f, 0L );

    // Begin the scene
    if( FAILED( pd3dDevice->BeginScene() ) )
        return E_FAIL;
 
    // Draw the triangle using a DrawPrimitive() call. Subsequent
    // tutorials will go into more detail on the various calls for
    // drawing polygons.

 

    // The ambient lighting value is another state to set. Here, we are turning
    // ambient lighting on to full white.
    pd3dDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xffffffff );

    /* Step 4: Enable Depth Buffering  [Language: C++]
    After attaching the depth buffer to the render-target surface, you can create
    a rendering device from the render target. Given a rendering device, you enable
    depth buffering by setting the D3DRENDERSTATE_ZENABLE render state for the device.
    The D3DZBUFFERTYPE enumerated type includes members to set the depth-buffer render
    state. The D3DZB_TRUE member (or TRUE) enables z-buffering. The ZBuffer sample
    enables z-buffering during scene rendering in the App_Render application-defined
    function. The following is the appropriate excerpt from App_Render:
    */

    // Enable z-buffering. (Note: we don't really need to do this every frame.)
    pd3dDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, TRUE );
    mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.ambient.r = 0.0f;
    mtrl.ambient.g = 1.0f;
    mtrl.ambient.b = 1.0f;
    pd3dDevice->SetMaterial( &mtrl );

    pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, D3DFVF_VERTEX,
                               g_pvTriangleVertices2, 6, NULL );

//    DrawAnythingPlease(pd3dDevice);
    /*
    Although this tutorial enables depth-buffering each frame, it is not necessary
    to do so. A real-world application would likely set the D3DRENDERSTATE_ZENABLE
    render state during scene initialization, only changing to disable depth buffering
    or to choose another type of depth buffering.

    Note  The D3DZBUFFERTYPE enumerated type includes the D3DZB_USEW value to
    enable w-based depth comparisons on compliant hardware. For more information,
    see Depth Buffers.
    */
   mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.ambient.r = 1.0f;
    mtrl.ambient.g = 1.0f;
    mtrl.ambient.b = 0.0f;
    pd3dDevice->SetMaterial( &mtrl );

    pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, D3DFVF_VERTEX,
                               g_pvTriangleVertices, 6, NULL );


//    ShapeCreateWall(10,20);

    // End the scene.
    pd3dDevice->EndScene();

    return S_OK;
}
//---------------------------------------------------------------------------

HRESULT TD3DTestForm::ShowFrame()
{
    if( NULL == g_pddsPrimary )
        return E_FAIL;

    // We are in windowed mode, so perform a blit from the backbuffer to the
    // correct position on the primary surface
    return g_pddsPrimary->Blt( &g_rcScreenRect, g_pddsBackBuffer,
                               /*&g_rcViewportRect*/NULL, DDBLT_WAIT, NULL );
}
//---------------------------------------------------------------------------

HRESULT TD3DTestForm::Cleanup3DEnvironment()
{
    // Cleanup any objects created for the scene
    App_DeleteDeviceObjects( g_pd3dDevice );

//    if(g_pd3dDevice) g_pd3dDevice->Release();

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
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: Render3DEnvironment()
// Desc: Draws the scene. There are three steps here:
//       (1) Animate the scene
//       (2) Render the scene
//       (3) Show the frame (copy backbuffer contents to the primary).
//-----------------------------------------------------------------------------
HRESULT TD3DTestForm::Render3DEnvironment()
{
	// Call the app specific function to framemove (animate) the scene
    App_FrameMove( g_pd3dDevice, ((FLOAT)clock())/CLOCKS_PER_SEC );

    g_rcViewportRect3D.x1 = g_rcViewportRect.left;
    g_rcViewportRect3D.y1 = g_rcViewportRect.top;
    g_rcViewportRect3D.x2 = g_rcViewportRect.right;
    g_rcViewportRect3D.y2 = g_rcViewportRect.bottom;

    // Call the app specific function to render the scene
    App_Render( g_pd3dDevice, &g_rcViewportRect3D );

    // Show the frame on the primary surface. Note: this is the best place to
	// check for "lost" surfaces. Surfaces can be lost if something caused
	// them to temporary lose their video memory. "Lost" surfaces simply
	// need to be restored before continuing.
    if( DDERR_SURFACELOST == ShowFrame() )
		RestoreSurfaces();

    return S_OK;
}
//---------------------------------------------------------------------------

void __fastcall TD3DTestForm::timerRunning(TObject *Sender)
{
    Render3DEnvironment();
}
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: RestoreSurfaces()
// Desc: Checks for lost surfaces and restores them if lost.
//-----------------------------------------------------------------------------
HRESULT TD3DTestForm::RestoreSurfaces()
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
// Name: App_DeleteDeviceObjects()
// Desc: Called when the device is being deleted, this function deletes any
//       device dependant objects.
//-----------------------------------------------------------------------------
VOID TD3DTestForm::App_DeleteDeviceObjects( LPDIRECT3DDEVICE7 pd3dDevice )
{
	// Release the material that was created earlier.
    if( g_pmtrlObjectMtrl )
		g_pmtrlObjectMtrl->Release();
	g_pmtrlObjectMtrl = NULL;
}
//---------------------------------------------------------------------------

BOOL TD3DTestForm::MyCreate(D3DVECTOR* pVectors, int nVectors, D3DVECTOR* pNormals,  int nNormals, int* pFaceData, BOOL bAutoGen)
{
	HRESULT rval;

	rval = m_MeshBld->AddFaces(nVectors, pVectors, nNormals, pNormals, (ULONG*)pFaceData, NULL);

	if(rval != D3DRM_OK) return FALSE;

	if((nNormals == 0) && bAutoGen) m_MeshBld->GenerateNormals();

	m_MeshBld->SetPerspective(TRUE);
	m_Frame->AddVisual(m_MeshBld);

	return TRUE;
}

BOOL TD3DTestForm::ShapeCreateWall(double x, double y)
{
/*	D3DVALUE x1 = D3DVAL(x / 2);
	D3DVALUE y1 = D3DVAL(y / 2);

	D3DVECTOR vert[] =
	{
		{-x1, -y1, 0.0},
		{-x1,  y1, 0.0},
		{ x1,  y1, 0.0},
		{ x1, -y1, 0.0}
	};

	D3DVECTOR nlist [] =
	{
		{ 0,  0,  -1}
	};

	int flist [] = {4, 0, 0, 1, 0, 2, 0, 3, 0, 0};

//	BOOL rval = MyCreate(vert, 4, nlist, 1, flist);
	HRESULT rval = m_MeshBld->AddFaces(4, vert, 1, nlist, (ULONG*)flist, NULL);

	if(rval != D3DRM_OK) return FALSE;

//	if((nNormals == 0) && bAutoGen) m_MeshBld->GenerateNormals();

	m_MeshBld->SetPerspective(TRUE);
	m_Frame->AddVisual(m_MeshBld);
*/
	return false;
}
//---------------------------------------------------------------------------


BOOL TD3DTestForm::DrawAnythingPlease(LPDIRECT3DDEVICE7 d3dd)
{
    d3dd->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_VERTEX, g_pvTriangleVertices, 6, NULL );
    return true;
}
//---------------------------------------------------------------------------

void __fastcall TD3DTestForm::FormResize(TObject *Sender)
{
//    if(!Ready) return;


    // Check to see if we are losing or gaining our window.
    // Set the active flag to match.
//    if( SIZE_MAXHIDE==wParam || SIZE_MINIMIZED==wParam )
//        g_bActive = FALSE;
//    else g_bActive = TRUE;

    // A new window size will require a new back buffer size. The
    // easiest way to achieve this is to release and re-create
    // everything. Note: if the window gets too big, we may run out
    // of video memory and need to exit. This simple app exits
    // without displaying error messages, but a real app would
    // behave itself much better.
//    if( g_bActive && g_bReady )
    {
//        g_bReady = FALSE;
        if( FAILED( Cleanup3DEnvironment() ) )
            DestroyWindow( Handle );
//        if( FAILED( Initialize3DEnvironment( Handle ) ) )
    if( FAILED( CreateEverything( ) ) )
            DestroyWindow( Handle );
//        App_InitDeviceObjects(g_pd3dDevice);
//        g_bReady = TRUE;
    }
}
//---------------------------------------------------------------------------

/*
The EnumZBufferFormats method accepts the globally unique identifier (GUID) of the
device for which the formats will be enumerated, the address of a callback function,
and the address of an arbitrary data structure that will be passed to the callback
function. The callback function you provide must conform to the D3DEnumPixelFormatsCallback
function prototype. The system calls the specified callback function once for each
supported depth-buffer format, unless the callback function returns D3DENUMRET_CANCEL.
The ZBuffer sample processes callbacks as follows:
*/

//-----------------------------------------------------------------------------
// Name: EnumZBufferCallback()
// Desc: Enumeration function to report valid pixel formats for z-buffers.
//-----------------------------------------------------------------------------
static HRESULT WINAPI EnumZBufferCallback( DDPIXELFORMAT* pddpf, VOID* pddpfDesired )
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
/*
When the system calls the callback function, it passes the address of a DDPIXELFORMAT
structure that describes the pixel format of the depth buffer. The dwFlags member
will contain DDPF_ZBUFFER for any pixel formats that include depth-buffer bits. If
so, the dwZBufferBitDepth member includes an integer that represents the number of
bits in the pixel format reserved for depth information, and the dwZBitMask member
masks the relevant bits.

For simplicity, this tutorial only uses z-buffers, which are the most common type
of depth buffer. It ignores any other formats (such as DDPF_STENCILBUFFER) that the
system enumerates. Applications could also check the bit depth of the z-buffer
(8-, 16-, 24-, 32-bit) and make a choice based on that as well. If a suitable
format is found, the function copies the provided DDPIXELFORMAT structure to the
address passed in the second parameter (also a DDPIXELFORMAT structure), and
returns D3DENUMRET_CANCEL to stop the enumeration.

After you determine the format of the depth buffer, you can create a DirectDrawSurface
that uses that format, which is the topic of Step 2: Create the Depth Buffer.
*/
//---------------------------------------------------------------------------


