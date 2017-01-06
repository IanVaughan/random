//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "D3DTestSrc.h"
#include <math.hpp>
#include "math.h"
#include <time.h>

#pragma package(smart_init)
#pragma resource "*.dfm"
TD3DTestForm *D3DTestForm;

//#if defined( __BORLANDC__ ) && defined( __WIN32__ )
//#define _WIN32_

static LPDIRECTDRAW7        g_pDD            = NULL;
static LPDIRECTDRAWSURFACE7 g_pddsPrimary    = NULL;
static LPDIRECTDRAWSURFACE7 g_pddsBackBuffer = NULL;
static LPDIRECT3D7          g_pD3D           = NULL;
static LPDIRECT3DDEVICE7    g_pd3dDevice     = NULL;
static RECT                 g_rcScreenRect;

LPDIRECT3DMATERIAL3 g_pmtrlObjectMtrl = NULL;
D3DVERTEX           g_pvTriangleVertices[6];

//---------------------------------------------------------------------------

static BOOL g_bActive  = FALSE; // Whether the app is active (not minimized)
static BOOL g_bReady   = FALSE; // Whether the app is ready to render frames

//static LPDIRECTDRAWSURFACE7 g_pddsZBuffer    = NULL;
RECT g_rcViewportRect;
D3DRECT g_rcViewportRect3D;

//mine
LPDIRECT3DRMMESHBUILDER m_MeshBld;
LPDIRECT3DRMFRAME m_Frame;

//---------------------------------------------------------------------------

__fastcall TD3DTestForm::TD3DTestForm(TComponent* Owner) : TForm(Owner)
{
  OSVERSIONINFO info ;
  info.dwOSVersionInfoSize = sizeof (info) ;
  GetVersionEx (&info) ;

  switch (info.dwPlatformId)
  {
  case VER_PLATFORM_WIN32s:
//    Label1->Caption = "System:  Windows Win 32s" ;
    break ;
  case VER_PLATFORM_WIN32_WINDOWS:
//    Label1->Caption = "System:  Windows 95" ;
    break ;
  case VER_PLATFORM_WIN32_NT:
//    Label1->Caption = "System:  Windows NT" ;
    break ;
  default:
//    Label1->Caption = "System:  Unknown" ;
    break ;
  }

   //IV
//    g_pvTriangleVertices[6] = new D3DVERTEX;

    //---------------------------------------------------------------------------
    //timer
    TTimer* timer = new TTimer(this);
    timer->Interval = 10;
    timer->Enabled = false;
    timer->OnTimer = timerRunning;

    //---------------------------------------------------------------------------
    //3d

    Initialize3DEnvironment( Handle );
    App_InitDeviceObjects( g_pd3dDevice );

    timer->Enabled = true;
//    Ready = true;
}
//---------------------------------------------------------------------------

__fastcall TD3DTestForm::~TD3DTestForm()
{
    Cleanup3DEnvironment();
}
//---------------------------------------------------------------------------

HRESULT TD3DTestForm::Initialize3DEnvironment( HWND hWnd )
{
    /*
    Step 2.1: Initialize DirectDraw

    After creating the application window, the first object you will create is
    the DirectDraw object, which is required to set your application's
    cooperative level, and to create the surfaces for display and for use as the
    render target of a rendering device.

    The Triangle sample starts performing initialization by creating a DirectDraw
    object and setting the application's cooperative level, as shown in the
    following code:
    */

    HRESULT hr;

    hr = DirectDrawCreateEx( NULL, (VOID**)&g_pDD, IID_IDirectDraw7, NULL );
    if( FAILED( hr ) )
        return hr;

    /*
    The preceding code creates a DirectDraw object by calling the DirectDrawCreateEx
    DirectDraw global function. It passes NULL in the first parameter to request
    that the function create a DirectDraw object for the active display driver.
    For hardware that doesn't support GDI, such as 3-D only hardware, you should
    explicitly specify the globally unique identifier (GUID) of the desired driver
    in the first parameter. These GUIDs are normally obtained through enumeration.
    The second parameter is the address of a global variable that DirectDrawCreateEx
    fills with the address of the IDirectDraw7 interface for the DirectDraw object,
    and the last parameter is set to NULL to indicate that the new object will not
    be used with COM aggregation features.

    The sample continues by setting the application's cooperative level, as follows:
    */

    hr = g_pDD->SetCooperativeLevel( hWnd, DDSCL_NORMAL );
    if( FAILED( hr ) )
        return hr;



    /*
    After you create a DirectDraw object and set the cooperative level, you can
    create the surfaces that your application will use to render and display a
    scene. Exactly how you create your surfaces depends largely on whether or not
    your application will run in a window or in full-screen mode.

    Full-screen Application Note  Applications that will run in full-screen mode
    can create surfaces as shown in the preceding code examples. More often, these
    applications should take advantage of page-flipping, a feature only available
    in full-screen, exclusive mode. In this case, instead of explicitly creating
    two surfaces, you can create a flipping chain of surfaces with a single call.
    For more information, see Creating Complex Surfaces and Flipping Chains.

    The Triangle sample, designed to run in a window, starts by creating a primary
    surface, which represents the display:
    */

    DDSURFACEDESC2 ddsd;
    ZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    // Create the primary surface.
    hr = g_pDD->CreateSurface( &ddsd, &g_pddsPrimary, NULL );
    if( FAILED( hr ) )
        return hr;


    /*
    The description for the primary surface doesn't contain information about
    dimensions or pixel format, as these traits are assumed to be the same as the
    display mode. If the current display mode is 800x600, 16-bit color, DirectDraw
    ensures that the primary surface matches. After creating the primary surface,
    you can create the render target surface. In the case of Triangle, this is a
    separate off-screen surface created as follows:
    */

    ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
 
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

    /*
    The preceding code creates an off-screen surface that is equal to the dimensions
    of the program window. There is no need to create a larger surface, because the
    dimensions of the window dictate what is visible to the user. (This code also
    initializes two global variables that are later used to set up the viewport and
    track the application window size and position.) As the preceding excerpt shows,
    you must include the DDSCAPS_3DDEVICE capability for any surface that will be
    used as a render target. This capability causes the system to allocate additional
    internal data structures that are used only for 3-D rendering. As when creating
    the primary surface, the pixel format for the off-screen surface is assumed to
    be the same as the display mode when it isn't provided in the surface description.

    Note  Applications that will use a depth buffer should create one and attach
    it to the render target surface at this point. For simplicity, this tutorial
    doesn't employ a depth buffer, but they are covered in Tutorial 2: Adding a
    Depth Buffer and in Depth Buffers.

    After creating the primary and render target surface, you can create and
    attach a DirectDrawClipper object to the display surface. Using a clipper
    frees you from attempting to handle cases when the window is partially
    obscured by other windows, or when the window is partially outside the
    display area. Clippers aren't needed for applications that run in full-screen
    mode. The Triangle sample uses the following code to create a clipper and
    associate it with the display window:
    */


    LPDIRECTDRAWCLIPPER pcClipper;
    hr = g_pDD->CreateClipper( 0, &pcClipper, NULL );
    if( FAILED( hr ) )
        return hr;

    // Assign it to the window handle, then set
    // the clipper to the desired surface.
    pcClipper->SetHWnd( 0, hWnd );
    g_pddsPrimary->SetClipper( pcClipper );
    pcClipper->Release();

    /*
    Having created the basic DirectDraw objects, you can move on to setting up
    the essential Direct3D objects that will render the scene. The Triangle
    sample performs this task in Step 2.3: Initialize Direct3D.
    */


    /*
    Step 2.3: Initialize Direct3D
    After you create the surfaces your application will need to render and
    display a scene, you can begin initializing Direct3D objects by retrieving
    a pointer to the IDirect3D7 interface for the DirectDraw object, which is
    used to create all the objects you'll need to render a scene. Note that this
    interface is exposed by the DirectDraw object, and represents a separate set
    of features, not a separate object. You retrieve the IDirect3D7 interface by
    calling the IUnknown::QueryInterface method of the DirectDraw object. The
    following code from Triangle performs this task:
    */

    // Query DirectDraw for access to Direct3D
    g_pDD->QueryInterface( IID_IDirect3D7, (VOID**)&g_pD3D );
    if( FAILED( hr) )
        return hr;

    /*
    After retrieving a pointer to the IDirect3D7 interface, you can create a
    rendering device by calling the IDirect3D7::CreateDevice method. The
    CreateDevice method accepts the globally unique identifier (GUID) of the
    desired device, the address of the IDirectDrawSurface7 interface for the
    surface that the device will render to, and the address of a variable that
    the method will set to an IDirect3DDevice7 interface pointer if the device
    object is created successfully. Although the tutorial uses hard-coded GUID
    values, a real application should enumerate devices to get a GUID. For
    information about device enumeration, see Enumerating Direct3D Devices.

    (The Triangle sample checks the display mode prior to creating the device.
    If the display is set to a palettized mode, it exits. Attempting to create
    a device for a palettized surface that doesn't have an associated palette
    will cause the CreateDevice method to fail. This is done for simplicity. A
    real-world application should create a render target surface and attach a
    palette, or require that the user set their display mode to 16-bit color or
    higher.)

    The following code, taken from Triangle, checks the display mode, and creates
    a rendering device:
    */

    // Check the display mode, and
    ddsd.dwSize = sizeof(DDSURFACEDESC2);
    g_pDD->GetDisplayMode( &ddsd );
    if( ddsd.ddpfPixelFormat.dwRGBBitCount <= 8 )
        return DDERR_INVALIDMODE;
 
    // The GUID here is hard coded. In a real-world application
    // this should be retrieved by enumerating devices.
    hr = g_pD3D->CreateDevice( IID_IDirect3DHALDevice, g_pddsBackBuffer,
                               &g_pd3dDevice );
    if( FAILED( hr ) )
    {
        // If the hardware GUID doesn't work, try a software device.
        hr = g_pD3D->CreateDevice( IID_IDirect3DRGBDevice, g_pddsBackBuffer,
                                   &g_pd3dDevice );
        if( FAILED( hr ) )
            return hr;
    }

    /*
    The CreateDevice method can fail for many reasons. The most likely cause is
    when the primary display device doesn't support 3-D features. Another
    possibility is if the display hardware cannot render in the current display
    mode. These possibilities should be checked during device enumeration. To
    keep the code simple, Triangle attempts to create a software rendering device
    if the hardware device cannot be created.

    Note  Even though the CreateDevice method accepts a pointer to a
    DirectDrawSurface object, a rendering device is not a surface. Rather, it is
    a discrete COM object that uses a surface to contain graphics for a rendered
    scene.

    After the device is created, you can create a viewport and assign it to the
    device, as described in Step 2.4: Prepare the Viewport.
    */

    /*
    Step 2.4: Prepare the Viewport  [Language: C++]

    After you create a rendering device, you can create a viewport and assign it
    to the device. In short, the viewport determines how the geometry in a 3-D
    scene is clipped and then represented in the 2-D space of a display screen.
    (For a conceptual overview about viewports, see Viewports and Clipping.)

    Setting up a viewport is a straight-forward process that starts with preparing
    the viewport parameters in a D3DVIEWPORT7 structure. The Triangle sample
    sets the viewport parameters to the dimensions of the render target surface:
    */

    // Create the viewport
    DWORD dwRenderWidth  = g_rcScreenRect.right - g_rcScreenRect.left;
    DWORD dwRenderHeight = g_rcScreenRect.bottom - g_rcScreenRect.top;
    D3DVIEWPORT7 vp = { 0, 0, dwRenderWidth, dwRenderHeight, 0.0f, 1.0f };

    /*
    Once the viewport structure is prepared, the Triangle application assigns it
    to the rendering device:
    */

    hr = g_pd3dDevice->SetViewport( &vp );
    if( FAILED( hr ) )
        return hr;

    /*
    Now that the basic DirectX objects have been created, you can start preparing
    the subordinate objects required to render scene, which is the topic of
    Step 3: Initialize the Scene.
    */


//    m_MeshBld

    return S_OK;
}
//---------------------------------------------------------------------------
/*
Step 3.1: Prepare Geometry  [Language: C++]

After you create the primary system objects used with DirectDraw and Direct3D,
you can begin initializing the scene. The Triangle sample takes this opportunity
to initialize geometry by defining vertices in an array of D3DVERTEX structures.
Technically, you aren't required to set up the geometry at this time—you can do
it anytime prior to calling rendering methods:
*/
HRESULT TD3DTestForm::App_InitDeviceObjects( LPDIRECT3DDEVICE7 pd3dDevice )
{
    // Data for the geometry of the triangle. Note that this tutorial only
    // uses ambient lighting, so the vertices' normals are not actually used.

    D3DVECTOR p1( 0.0f, 3.0f, 0.0f );
    D3DVECTOR p2( 3.0f,-3.0f, 0.0f );
    D3DVECTOR p3(-3.0f,-3.0f, 0.0f );
    D3DVECTOR vNormal( 0.0f, 0.0f, 1.0f );

    // Initialize the 3 vertices for the front of the triangle
    g_pvTriangleVertices[0] = D3DVERTEX( p1, vNormal, 0, 0 );
    g_pvTriangleVertices[1] = D3DVERTEX( p2, vNormal, 0, 0 );
    g_pvTriangleVertices[2] = D3DVERTEX( p3, vNormal, 0, 0 );

    // Initialize the 3 vertices for the back of the triangle
    g_pvTriangleVertices[3] = D3DVERTEX( p1, -vNormal, 0, 0 );
    g_pvTriangleVertices[4] = D3DVERTEX( p3, -vNormal, 0, 0 );
    g_pvTriangleVertices[5] = D3DVERTEX( p2, -vNormal, 0, 0 );

    /*
    The preceding code fragment defines three points in 3-D space that define a
    triangle that sits upright in the z=0 plane. After defining the geometry to
    be displayed, the Triangle sample prepares material and lighting parameters
    in Step 3.2: Set Up Material and Initial Lighting States.
    */

    /*
    Step 3.2: Set Up Material and Initial Lighting States
    After you create the basic 3-D rendering objects (a DirectDraw object, a
    rendering device, and a viewport), you've got almost all you need to render
    a simple scene. The next thing to do is to create and configure a material
    and set some initial lighting states. These can all be changed later if
    needed. For an introduction to these concepts, see Lighting and Materials.

    The Triangle sample sets material parameters, as shown here:
    */

    D3DMATERIAL7 mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.ambient.r = 1.0f;
    mtrl.ambient.g = 1.0f;
    mtrl.ambient.b = 0.0f;
    pd3dDevice->SetMaterial( &mtrl );

    /*
    The preceding code prepares material properties, represented by a D3DMATERIAL7
    structure. The code prepares the D3DMATERIAL7 structure to describe a material
    that will reflect the red and green components of ambient light, making it
    appear yellow in the scene. (This tutorial only uses ambient light, so it
    only sets an ambient reflectance property. A real-world application would use
    direct light as well as ambient light, and should set therefore set diffuse
    and specular reflectance properties as well.) After preparing the material
    properties, the code applies them in the device by calling the
    IDirect3DDevice7::SetMaterial method.

    Note  When using textures, the object material is usually omitted or colored white.

    After the current material is selected, all polygons will be rendered using
    this material. However, before anything in the scene will be visible you need
    to provide some light. The code in the Triangle application sets an ambient
    light level by calling the IDirect3DDevice7::SetRenderState method with the
    D3DRENDERSTATE_AMBIENT render state for white ambient light:
    */

    // The ambient lighting value is another state to set. Here, we are turning
    // ambient lighting on to full white.
    pd3dDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xffffffff );

    /*
    Now that the geometry, material, and initial lighting parameters are set, the
    sample moves on to setting up the transformation matrices. This is covered in
    Step 3.3: Prepare and Set Transformation Matrices.
    */


    /*
    Step 3.3: Prepare and Set Transformation Matrices

    Another step in setting up a simple scene involved setting the world, view,
    and projection matrices. The system applies these matrices to geometry to
    place it in the scene, adjust for the camera's location and orientation, and
    scale vertex data to make distant objects appear smaller than near objects.
    (For a conceptual overview, see the Geometry Pipeline.)

    The Triangle sample starts by creating an identity matrix in a D3DMATRIX
    structure, then it manipulates the matrix to produce the desired
    transformations. Once a matrix is ready, the code assigns it to the device
    by calling the IDirect3DDevice7::SetTransform method with the
    D3DTRANSFORMSTATE_WORLD, D3DTRANSFORMSTATE_VIEW, or D3DTRANSFORMSTATE_PROJECTION
    values:
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
    matProj._11 =  2.0f;
    matProj._22 =  2.0f;
    matProj._34 =  1.0f;
    matProj._43 = -1.0f;
    matProj._44 =  0.0f;
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProj );

    /*
    After setting the transformations, Triangle is done setting up the scene.
    The App_InitDeviceObjects application-defined function returns S_OK to the
    caller, the Initialize3DEnvironment application-defined function. The
    Initialize3DEnvironment function then returns that value to WinMain, which
    moves on to process system messages, as discussed in Step 4: Monitor System
    Messages.
    */

    return S_OK;
}
//---------------------------------------------------------------------------

/*
Step 5.1: Update the Scene

Immediately after it is called, the Render3DEnvironment application-defined
function in the Triangle sample calls App_FrameMove (another application-defined
function). The App_FrameMove function simply updates the world matrix that
Direct3D applies to the geometry to reflect a rotation around the y-axis based
on an internal count value, passed to the function in the fTimeKey parameter.
Because the rotation is applied once per frame, the end result looks like the
model is rotating in place.
*/

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
 
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &matSpin );

    return S_OK;
}
/*
In the real world, of course, your applications will do much more than apply a
single rotation on a single model. (For more information rotation matrices, see
Rotation in the 3-D Transformations section.)

After you update the geometry in the scene, you can render it to the render target
surface, as the Triangle sample does in Step 5.2: Render the Scene.
*/

//---------------------------------------------------------------------------

/*
Step 5.2: Render the Scene
Once the geometry has been updated to reflect the desired animation, you can
render the scene. The Triangle sample takes a typical approach: the App_Render
application-defined function called from the sample's Render3DEnvironment
function starts by clearing the viewport:
*/

HRESULT TD3DTestForm::App_Render( LPDIRECT3DDEVICE7 pd3dDevice, D3DRECT* prcViewRect )
{
    // Clear the viewport to a blue color.
    pd3dDevice->Clear( 1UL, prcViewRect, D3DCLEAR_TARGET, 0x000000ff, 0L, 0L );

    /*
    The preceding code calls the IDirect3DDevice7::Clear method to clear the viewport.
    The first two methods that the Clear method accepts are the address of an array
    of rectangles that describe the areas on the render target surface to be cleared,
    and a value that informs the method how many rectangles from the array should
    be cleared. In most cases, you'll use a single rectangle that covers the entire
    render target. The third parameter determines the method's behavior. It can clear
    a render-target surface, an associated depth buffer, the stencil buffer, or any
    combination of the three. Because this tutorial doesn't use a depth buffer,
    D3DCLEAR_TARGET is the only flag used. The last three parameters are set to
    reflect clearing values for the render target, depth buffer, and stencil buffer.
    The Triangle sample sets the clear color for the render target surface to blue.
    Because the remaining parameters aren't used in this tutorial, the code just
    sets them to zero. The Clear method will ignores them when the corresponding
    flag isn't present.

    After clearing the viewport, the Triangle sample informs Direct3D that
    rendering will begin, renders the scene, then signals that rendering is
    complete, as shown here:
    */

    // Begin the scene
    if( FAILED( pd3dDevice->BeginScene() ) )
        return E_FAIL;
 
    // Draw the triangle using a DrawPrimitive() call. Subsequent
    // tutorials will go into more detail on the various calls for
    // drawing polygons.
    pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, D3DFVF_VERTEX,
                               g_pvTriangleVertices, 6, NULL );

    DrawAnythingPlease(pd3dDevice);

//    ShapeCreateWall(10,20);

    // End the scene.
    pd3dDevice->EndScene();

    return S_OK;
}
/*
The IDirect3DDevice7::BeginScene and IDirect3DDevice7::EndScene methods signal to
the system when rendering is beginning or is complete. You can only call rendering
methods between calls to these methods. Even if rendering methods fail, you should
call EndScene before calling BeginScene again.

After rendering the scene to the off-screen render target, you can update the
user's display. The tutorial sample performs this in Step 5.3: Update the Display.
*/

//---------------------------------------------------------------------------

/*
Step 5.3: Update the Display

Once a scene has been rendered to the render-target surface, you can show the
results on screen. A windowed application usually does this by blitting the
content of the render-target surface to the primary surface, and a full-screen
application that employs page-flipping would simply flip the surfaces in the
flipping chain. The Triangle sample uses the former method because it runs in a
window, using the following code:
*/

HRESULT TD3DTestForm::ShowFrame()
{
    if( NULL == g_pddsPrimary )
        return E_FAIL;

    // We are in windowed mode, so perform a blit from the backbuffer to the
    // correct position on the primary surface
    return g_pddsPrimary->Blt( &g_rcScreenRect, g_pddsBackBuffer,
                               &g_rcViewportRect, DDBLT_WAIT, NULL );
}

/*
Note that the preceding application-defined function simply blits the entire
contents of the render target surface to the window on the desktop. The tutorial
tracks the destination rectangle for the blit in the g_rcScreenRect global variable.
This rectangle is updated whenever the user moves the window, as covered in the
Handle Window Movement section.
*/

//---------------------------------------------------------------------------

/*
Step 6: Shut Down

At some point during execution, your application must shut down. Shutting down a
DirectX application not only means that you should destroy the application window,
but you also deallocate any DirectX objects your application uses and invalidate
the pointers to them. The Triangle calls an application-defined function to handle
this cleanup, called Cleanup3DEnvironment, when it receives a WM_DESTROY message:
*/

HRESULT TD3DTestForm::Cleanup3DEnvironment()
{
    // Cleanup any objects created for the scene
    App_DeleteDeviceObjects( g_pd3dDevice );
 
    // Release the DDraw and D3D objects used by the app
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
 
    g_pd3dDevice     = NULL;
    g_pD3D           = NULL;
    g_pddsBackBuffer = NULL;
    g_pddsPrimary    = NULL;
    g_pDD            = NULL;
 
    return S_OK;
}
/*
The preceding function deallocates the DirectX objects it uses by calling the
IUnknown::Release methods for each object. Because the tutorial follows COM rules,
the reference counts for most objects should become zero and are automatically
removed from memory.

In addition to shut down, there are times during normal execution—such as when
the user changes the desktop resolution or color depth—when you might need to
destroy and re-create the DirectX objects in use. As a result, it's handy to keep
your application's cleanup code in one place, which can be called when the need
arises.
*/

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

/*Handle Window Resizing  [Language: C++]
Any DirectX application that runs in a window must respond to any WM_SIZE messages
that the system sends. The render target surface is usually kept as small as possible
to conserve memory, and the smallest size is usually the size of the window client
area. When window size increases, you must destroy the render target surface and
the associated objects and re-create it at an appropriate size. Technically, an
application could do this only when the window gets larger, and respond to situations
when window size decreases by adjusting the viewport and decreasing the size of the
blit accordingly. For simplicity, this tutorial destroys and re-creates the objects
it uses whenever it receives a WM_SIZE message:
*/

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
        if( FAILED( Initialize3DEnvironment( Handle ) ) )
            DestroyWindow( Handle );
        App_InitDeviceObjects(g_pd3dDevice);
//        g_bReady = TRUE;
    }

/*
Note that the preceding code sets a global variable to communicate to other portions
of the code that the DirectX objects in use are being invalidated. In addition,
this code calls the application-defined Cleanup3DEnvironment function to destroy
the objects, which is also called during application shut-down. Ending the application
is discussed in Step 6: Shut Down.
*/
}
//---------------------------------------------------------------------------

