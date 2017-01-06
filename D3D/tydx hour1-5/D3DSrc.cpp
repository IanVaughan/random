//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#if defined( __BORLANDC__ ) && defined( __WIN32__ )
#define _WIN32
#endif

#include "D3DSrc.h"

#define D3D_OVERLOADS
#define INITGUID
#include "ddraw.h"
#include "d3dutil.h"

#include "mmsystem.h" //timeGetTime

#include "Cube.h"

#include "D3DError.h"
#define Err(x); {MessageBox(NULL, x, "Error", MB_OK|MB_ICONERROR);}

    float rotAngle=3.14;		// current angle
    float rotVel=0.0f;			// current velociy of spin

    float elevation=350.0f;		// current elevation
    float liftVel=0.0f;			// rate of rise / decent

#define ORBIT			800.0f

#define NUM_ROWS		1
#define NUM_COLUMNS		2

CCube *cubes[NUM_ROWS][NUM_COLUMNS];

TTimer *tim;
TTimer *tom;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TD3D *D3D;
TD3DError* DXError;

LPDIRECT3D7 lpD3D                   = NULL;
LPDIRECTDRAW7 lpDD7                 = NULL;
LPDIRECT3DDEVICE7 lpDevice          = NULL;
LPDIRECTDRAWCLIPPER lpClip          = NULL;
LPDIRECTDRAWSURFACE7 lpDDSPrimary   = NULL;
LPDIRECTDRAWSURFACE7 lpDDSBack      = NULL;
LPDIRECTDRAWSURFACE7 lpDDSOver      = NULL;

bool ProgActive = true;

//---------------------------------------------------------------------------

__fastcall TD3D::TD3D(TComponent* Owner) : TForm(Owner)
{
    DXError = new TD3DError();

    HRESULT hres = Setup();
    if(hres != DD_OK)
    {
        CleanUp();
        DXError->Display(hres);
        exit(0);
    }

    tim = new TTimer(this);
    tim->Interval = 1000; //is faster with this delay
    tim->OnTimer = Loop;

    tom = new TTimer(this);
    tom->Interval = 100;
    tom->OnTimer = z;
}
//---------------------------------------------------------------------------

HRESULT TD3D::Setup()
{
    HRESULT hres;

    hres = InitDD();
    if(hres != DD_OK)
        return hres;

/*    hres = InitOverlay();
    if(hres != D3D_OK)
        return hres;
*/
    hres = Init3D();
    if(hres != DD_OK)
        return hres;

    Create_objects();

    return DD_OK;
}
//---------------------------------------------------------------------------

#define SafeRelease(x) if (x) {x->Release(); x=NULL; }
#define SafeDelete(x) if (x) {delete x;x=NULL;}

void TD3D::CleanUp()
{
	for (int i=0;i<NUM_ROWS;i++)
		for (int j=0;j<NUM_COLUMNS;j++)
			SafeDelete(cubes[i][j]);

	// release 3D interfaces
	SafeRelease(lpDevice);
	SafeRelease(lpD3D);

    //release the interfaces
    SafeRelease(lpDDSBack);
    SafeRelease(lpDDSPrimary);
    SafeRelease(lpClip);
    SafeRelease(lpDD7);
}
//---------------------------------------------------------------------------

HRESULT TD3D::InitDD()
{
    HRESULT ddVal;

    //createa main DD object
    ddVal = DirectDrawCreateEx(NULL, (LPVOID*) &lpDD7, IID_IDirectDraw7, NULL);
    if(ddVal != DD_OK)
    {
        Err("Could not create direct draw object.");
        return ddVal;
    }

    //setup coop level
    ddVal = lpDD7->SetCooperativeLevel(Handle, DDSCL_ALLOWREBOOT |
                                               DDSCL_EXCLUSIVE |
                                               DDSCL_FULLSCREEN
                                               //DDSCL_NORMAL
                                              );
    if(ddVal != DD_OK)
    {
        Err("Could not set cooperative level.");
        return ddVal;
    }

    ddVal = lpDD7->SetDisplayMode(640,480,16,0,0);
    if(ddVal != DD_OK)
    {
        Err("Could not set the display mode.");
        return ddVal;
    }

    //create clipper
    ddVal = lpDD7->CreateClipper(NULL, &lpClip, NULL);
    if(ddVal != DD_OK)
    {
        Err("Could not create clipper device.");
        return ddVal;
    }
    lpClip->SetHWnd(0, Handle);


    DDSURFACEDESC2 ddsd;
    DDSCAPS2 ddscaps;

    //create primary surface
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps =   DDSCAPS_PRIMARYSURFACE |
                            DDSCAPS_FLIP | DDSCAPS_3DDEVICE |
                            DDSCAPS_COMPLEX ; //DDSCAPS_ZBUFFER || DDSCAPS_OVERLAY  ||
    ddsd.dwBackBufferCount = 1;

    ddVal = lpDD7->CreateSurface(&ddsd, &lpDDSPrimary, NULL);
    if(ddVal != DD_OK) {
        Err("Could not create primary surface.");
        return ddVal;
    }

    //set the clipper for the primary surface
    lpDDSPrimary->SetClipper(lpClip);

    ZeroMemory(&ddscaps, sizeof(ddscaps));
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER ;
    ddVal = lpDDSPrimary->GetAttachedSurface(&ddscaps, &lpDDSBack);
    if(ddVal != DD_OK) {
        Err("Could not GetAttachedSurface.");
        return ddVal;
    }

    return ddVal;
}
//---------------------------------------------------------------------------

HRESULT TD3D::InitOverlay()
{
//    lpDDSOver
    HRESULT ddVal;
    DDSURFACEDESC2 ddsd;
    DDSCAPS2 ddscaps;

    //create primary surface
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS; //| 
    ddsd.ddsCaps.dwCaps = DDSCAPS_OVERLAY | DDSCAPS_VIDEOMEMORY  //have 2 b in vid mem
                           // | DDSCAPS_PRIMARYSURFACE
                            | DDSCAPS_VISIBLE
                            ;
//                            DDSCAPS_FLIP | DDSCAPS_3DDEVICE ;;
                            //DDSCAPS_COMPLEX ; //DDSCAPS_ZBUFFER || DDSCAPS_OVERLAY  ||

    ddVal = lpDD7->CreateSurface(&ddsd, &lpDDSOver, NULL);
    if(ddVal != DD_OK) {
        Err("Could not create overlay surface.");
        return ddVal;
    }

    return ddVal;
}
//---------------------------------------------------------------------------

HRESULT TD3D::Init3D()
{
    HRESULT hres;

	// get master 3D interface
    hres = lpDD7->QueryInterface(IID_IDirect3D7, (LPVOID *)&lpD3D);
	if(hres != D3D_OK) {
		Err("Could not get Interface to D3D7.");
		return hres;
	}

    // set up the best device interface
    hres = lpD3D->CreateDevice(IID_IDirect3DTnLHalDevice,lpDDSBack,&lpDevice);
    if(hres != D3D_OK)
    {
        hres = lpD3D->CreateDevice(IID_IDirect3DHALDevice,lpDDSBack,&lpDevice);
        if(hres != D3D_OK)
        {
            hres = lpD3D->CreateDevice(IID_IDirect3DMMXDevice,lpDDSBack,&lpDevice);
            if(hres != D3D_OK)
            {
				hres = lpD3D->CreateDevice(IID_IDirect3DRGBDevice,lpDDSBack,&lpDevice);
                if(hres !=D3D_OK)
                {
					Err("Could not CreateDevice.");
					return hres;
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
	hres = lpDevice->SetViewport(&view) ;
    if(hres != D3D_OK) {
		Err("Could not SetViewport.");
		return hres;
	}
	
	D3DMATRIX proj_m;
	D3DUtil_SetProjectionMatrix(proj_m, 0.785f, 1.333f, 10.0f, 2000.0f );
	lpDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION,&proj_m);

	// disable Direct3D lighting, since we will provide our own
	lpDevice->SetRenderState(D3DRENDERSTATE_LIGHTING,FALSE);

//    lpDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);


	return hres;
}
//---------------------------------------------------------------------------

void TD3D::Create_objects()
{
	// create cubes on a grid

/*	for (int i=0;i<NUM_ROWS;i++)
		for (int j=0;j<NUM_COLUMNS;j++)
			cubes[i][j]=new CCube(
            */
            cubes[0][0]=new CCube(D3DVECTOR(0.0f,0.0f,0.0f),
								    D3DVECTOR(50.0f,250.0f,0.0f),
                                    0.95f,0.0f,0.8f);

            cubes[0][1]=new CCube(D3DVECTOR(10.0f,0.0f,50.0f),
								    D3DVECTOR(50.0f,250.0f,0.0f),
                                    0.95f,0.9f,0.8f);
}
//---------------------------------------------------------------------------

void TD3D::render_frame(float elapsed)
{
	// recover any lost surfaces
	if (lpDDSPrimary->IsLost()==DDERR_SURFACELOST)
		lpDDSPrimary->Restore();
	if (lpDDSBack->IsLost()==DDERR_SURFACELOST)
		lpDDSBack->Restore();

	// increment viewer position
	elevation+=liftVel*elapsed;
	rotAngle+=rotVel*elapsed;

	// calculate current viewer position
	D3DVECTOR view_loc;
	view_loc.y=elevation;				// set elevation
	view_loc.x=sin(rotAngle)*ORBIT;		// calculate position on x,z plane
	view_loc.z=cos(rotAngle)*ORBIT;

	// create and set the view matrix
	D3DMATRIX view_matrix;
	D3DUtil_SetViewMatrix(view_matrix,
						  view_loc,
						  D3DVECTOR(0.0f,0.0f,0.0f),
						  D3DVECTOR(0.0f,1.0f,0.0f));
	lpDevice->SetTransform(D3DTRANSFORMSTATE_VIEW,&view_matrix);

 	// clear the viewport
    lpDevice->Clear(0,NULL,D3DCLEAR_TARGET,0,1.0f,0);

    // start the scene render
	if( SUCCEEDED( lpDevice->BeginScene() ) )
    {
		// loop through the cubes and draw
		for (int i=0;i<NUM_ROWS;i++)
			for (int j=0;j<NUM_COLUMNS;j++)
				if (cubes[i][j])
					cubes[i][j]->draw(lpDevice);

		// end the scene
		lpDevice->EndScene();
	}

	// flip to the primary surface
	lpDDSPrimary->Flip(0, DDFLIP_WAIT);
}
//---------------------------------------------------------------------------

void __fastcall TD3D::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        ProgActive = false;
        CleanUp();
        Close();
    }
    else if(Key == VK_UP)
    {
        // move up
        liftVel=200.0f;
    }
    else if(Key == VK_DOWN)
    {
        // move down
        liftVel=-200.0f;
    }
    else if(Key == VK_RIGHT)
    {
        // rotate to the right
        rotVel=4.5f;
    }
    else if(Key == VK_LEFT)
    {
        // rotate to the left
        rotVel=-4.5f;
    }
}
//---------------------------------------------------------------------------

void __fastcall TD3D::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_UP || Key == VK_DOWN)
    {
        liftVel=0.0f;
    }
    else if(Key == VK_RIGHT || Key == VK_LEFT)
    {
        rotVel=0.0f;
    }
}
//---------------------------------------------------------------------------

void __fastcall TD3D::Loop(TObject *Sender)
{
	LONGLONG cur_time;       // current time
	LONGLONG perf_cnt;       // performance timer frequency
	BOOL perf_flag=FALSE;    // flag determining which timer to use
	LONGLONG last_time=0;	 // time of previous frame
	float time_elapsed;	 // time since previous frame
	float time_scale;		 // scaling factor for time

	// is there a performance counter available?
	if (QueryPerformanceFrequency((LARGE_INTEGER *) &perf_cnt))
    {
		// yes, set timer info and get starting time
		perf_flag=TRUE;
		QueryPerformanceCounter((LARGE_INTEGER *) &last_time);
		time_scale=1.0f/perf_cnt;
	}
    else
    {
		// no performance counter, read in using timeGetTime
		last_time=::timeGetTime();
		time_scale=0.001f;
	}

    BOOL bGotMsg;
    MSG  msg;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
    
    while( /*msg.message != WM_QUIT &&*/ ProgActive)
    {
        bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
        if( bGotMsg )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
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
}
//---------------------------------------------------------------------------

int nZ = 0;
void __fastcall TD3D::z(TObject *Sender)
{
    lpDevice->SetRenderState(D3DRENDERSTATE_ZBIAS, nZ);
    nZ++;
    if(nZ >15) nZ=0;
}
//---------------------------------------------------------------------------

/*
BOOL TD3D::ShapeCreateWall(void* pShape, double x, double y)
{
	D3DVALUE x1 = D3DVAL(x / 2);
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

	BOOL rval = pShape->Create(vert, 4, nlist, 1, flist);

	return rval;
}
//---------------------------------------------------------------------------

*/
