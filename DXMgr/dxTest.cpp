//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "dxTest.h"

#define D3D_OVERLOADS
#include <d3d.h>
#include <dxmgr.h>
//#include <dxmgr_i.c>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdxTestForm *dxTestForm;
//---------------------------------------------------------------------------

__fastcall TdxTestForm::TdxTestForm(TComponent* Owner) : TForm(Owner)
{
    bPaused = false;
    pDXMgr = NULL;
    pD3DDevice = NULL;
    fAngle = 0.0f;
    memset( &rClient, 0, sizeof(rClient ) );

    Initialize(this);
    PrepareToDraw();

}

__fastcall TdxTestForm::~TdxTestForm()
{
    RELEASE(pD3DDevice);
    RELEASE(pDXMgr);

}
//---------------------------------------------------------------------------

HRESULT TdxTestForm::Initialize( HWND _hwnd )
{
    HRESULT hr;
    hwnd = _hwnd;

    hr = DXMgrCreate( IID_IDXMgr, (LPVOID *) &pDXMgr );
    if ( FAILED(hr) )
        goto e_Exit;
    hr = pDXMgr->Initialize( NULL, hwnd, 0 );
    if ( FAILED(hr) )
        goto e_Exit;
    return S_OK;
e_Exit:
    RELEASE(pDXMgr);
    return hr;
}
//---------------------------------------------------------------------------

HRESULT TdxTestForm::PrepareToDraw( )
{
    HRESULT hr;

//    GetClientRect( hwnd, &rClient );
    rClient = GetClientRect();

    DXMGRENABLE enable;
    memset( &enable, 0, sizeof(enable) );
    enable.uFlags = DXMGRENABLE_3D;
    enable.hwndDevice = hwnd;
    enable.fNear = 1.0f;
    enable.fFar = 10.0f;
    hr = pDXMgr->Enable( &enable );
    if (FAILED(hr))
        goto e_Exit;
    hr = pDXMgr->GetDirect3DDevice( &pD3DDevice );
    if (FAILED(hr))
        goto e_Exit;
    (void) pD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
    (void) pD3DDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, TRUE );
    return S_OK;
e_Exit:
    RELEASE( pD3DDevice );
    (void) pDXMgr->Disable( 0 );
    return hr;
}
//---------------------------------------------------------------------------

HRESULT TdxTestForm::StopDrawing( )
{
    HRESULT hr;

    RELEASE( pD3DDevice );
    hr = pDXMgr->Disable( 0 );
    return hr;
}



/*#include <windows.h>

#include <objbase.h>
#include <initguid.h>

#define D3D_OVERLOADS
#include <d3d.h>

#include <dxmgr.h>
#include <dxmgr_i.c>

#include "resource.h"


class TdxTestForm
{
public:
    TdxTestForm( );
    ~TdxTestForm( );

    // Create and initialize DXMgr object
    HRESULT Initialize( HWND hwnd );

    // Enable DXMgr object (creates back buffer, clipper, D3D device, etc.)
    HRESULT PrepareToDraw( );

    // Disable (releases back buffers, clipper, D3D device, etc.)
    HRESULT StopDrawing( );

    // Draw if active and not paused
    void Draw();

    // Don't hurt anything, just stop drawing
    void PauseDrawing( );
    void RestartDrawing( );

    static LRESULT WINAPI TrivialWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
    // Objects created by Initialize and retained
    HWND hwnd;
    IDXMgr *pDXMgr;

    // Transient objects that get affected by PrepareToDraw
    LPDIRECT3DDEVICE3 pD3DDevice;
    float fAngle;

    RECT rClient;
    bool bPaused;
    bool bActive;
};

// Release interface only if non-NULL, then set to NULL
#define RELEASE( p ) ( (p) ? ((p)->Release(), p = NULL) : NULL )

TdxTestForm::TdxTestForm( )
{
    bPaused = false;
    pDXMgr = NULL;
    pD3DDevice = NULL;
    fAngle = 0.0f;
    memset( &rClient, 0, sizeof(rClient ) );
}

TdxTestForm::~TdxTestForm( )
{
    RELEASE(pD3DDevice);
    RELEASE(pDXMgr);
}


D3DVECTOR v[3] = { D3DVECTOR(0.0f, 1.0f, 0.0f), D3DVECTOR(1.0f, 0.0f, 0.0f), D3DVECTOR(-1.0f, 0.0f, 0.0f) };
// position data in vTriangle is filled in by rotating the above points
D3DLVERTEX vTriangle[3] = { D3DLVERTEX(D3DVECTOR(0.0f, 0.0f, 0.0f), RGB_MAKE( 0xff, 0x00, 0x00 ), 0, 0.0f, 0.0f),
                            D3DLVERTEX(D3DVECTOR(0.0f, 0.0f, 0.0f), RGB_MAKE( 0x00, 0xff, 0x00 ), 0, 0.0f, 0.0f),
                            D3DLVERTEX(D3DVECTOR(0.0f, 0.0f, 0.0f), RGB_MAKE( 0x00, 0x00, 0xff ), 0, 0.0f, 0.0f) };

void
TdxTestForm::Draw()
{
    HRESULT hr = pD3DDevice->BeginScene();
    if ( FAILED(hr) )
    {
        if ( FAILED( pDXMgr->RestoreSurfaces() ) )
            return;
        hr = pD3DDevice->BeginScene();
    }
    if ( FAILED(hr) )
        return;

    (void) pDXMgr->Clear( 0, NULL, D3DCLEAR_TARGET, RGB_MAKE(0,0,0), 1.0f, 0 );

    // Rotate triangle about Y axis before drawing
    float fSin = (float) sin(fAngle);
    float fCos = (float) cos(fAngle);
    for (int i = 0; i < 3; i += 1)
    {
        vTriangle[i].x = v[i].x * fCos - v[i].z * fSin;
        vTriangle[i].y = v[i].y;
        vTriangle[i].z = v[i].x * fSin + v[i].z * fCos + 2.5f;
    }
    (void) pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, D3DFVF_LVERTEX, vTriangle, 3, D3DDP_WAIT );
    (void) pD3DDevice->EndScene( );
    (void) pDXMgr->Update( 0, NULL );

}

void
TdxTestForm::PauseDrawing( )
{
    bPaused = true;
}

void
TdxTestForm::RestartDrawing( )
{
    bPaused = false;
}

LRESULT WINAPI
TdxTestForm::TrivialWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    TdxTestForm *pData = (TdxTestForm *) GetWindowLong( hwnd, 0 );
    RECT r;
    switch (msg)
    {
        case WM_CREATE:
            pData = new TdxTestForm;
            if ( ! pData )
                return -1;

            if (FAILED(pData->Initialize( hwnd ) ) ||
                FAILED(pData->PrepareToDraw() ) )
            {
                delete pData;
                return -1;
            }
            SetTimer(hwnd, 1, 10, NULL);

            SetWindowLong( hwnd, 0, (LONG) pData );
            return 0;
        case WM_DESTROY:
            if ( pData )
                delete pData;
            KillTimer(hwnd, 1);
            return 0;
        case WM_ACTIVATEAPP:
            if (pData) pData->bActive = (wparam) ? true : false;
            break;
        case WM_TIMER:
            if ( pData && ! pData->bPaused )
            {
                if ( pData->bActive )
                    pData->fAngle += 2.0f*3.141592654f / 90.0f;
                InvalidateRect( hwnd, NULL, FALSE );
            }
            return 0;
        case WM_SIZE:
            GetClientRect( hwnd, &r );
            if ( SIZE_MINIMIZED == wparam || r.top == r.bottom )
            {
                pData->PauseDrawing();
                return 0;
            }
            pData->RestartDrawing();
            pData->StopDrawing();
            pData->PrepareToDraw( );
            return 0;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                BeginPaint( hwnd, &ps );
                if (pData) pData->Draw();
                EndPaint( hwnd, &ps );
            }
            break;
        case WM_COMMAND:
            if ( 0 == HIWORD(wparam) )
            {
                switch ( LOWORD(wparam) )
                {
                    case ID_FILE_EXIT:
                        PostQuitMessage(0);
                        return 0;
                }
            }
            break;
	/*
	 * Pause and unpause the app when entering/leaving the menu
	 */
/*        case WM_ENTERMENULOOP:
            if ( pData ) pData->PauseDrawing();
            break;
        case WM_EXITMENULOOP:
            if ( pData ) pData->RestartDrawing();
            break;
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

HWND hwndMain;
HINSTANCE hInstance;

static BOOL
InitApp(HINSTANCE hInstance)
{
    WNDCLASS wndclass;

    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC) TdxTestForm::TrivialWndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = sizeof(void *);
    wndclass.hInstance     = hInstance;
    wndclass.hIcon         = (HICON) NULL;
    wndclass.hCursor       = (HCURSOR) NULL;
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
    wndclass.lpszClassName = "TrivWindow";
    if (! RegisterClass(&wndclass) )
    {
        return FALSE;
    }

    return TRUE;
}

int APIENTRY
WinMain( HINSTANCE hinst, 
         HINSTANCE hPrevInstance,
         LPSTR lpCmdLine,
         int nCmdShow )
{
    HRESULT hr;

    // initialize COM
    if (FAILED(hr = CoInitialize(NULL)))
        return FALSE;


    /* Register the window class for the main window. */

/*    if (!hPrevInstance) {
        if (! InitApp(hinst) )
            return FALSE;
    }

    hInstance = hinst;

    /* Create the main window. */
/*    hwndMain = CreateWindow("TrivWindow", "TrivWin",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, (HWND) NULL,
        (HMENU) NULL, hInstance, (LPVOID) NULL);

    /*
     * If the main window cannot be created, terminate
     * the application.
     */

/*    if (!hwndMain)
        return FALSE;

        /* Show the window and paint its contents. */

/*    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

        /* Start the message loop. */

/*    MSG msg;
    while (GetMessage(&msg, (HWND) NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow( hwndMain );
    /* Return the exit code to Windows. */

    // uninitialize COM
/*    CoUninitialize();

    return msg.wParam;
}

*/
