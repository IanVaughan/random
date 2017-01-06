//-----------------------------------------------------------------------------
// File: D3DApp.h
//
// Desc: Application class for the Direct3D samples framework library.
//
// Copyright (c) 1998-1999 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef  D3DAPP_H
#define  D3DAPP_H
#define  D3D_OVERLOADS
#include <d3d.h>
#include "D3DFrame.h"
#include "D3DEnum.h"
#include "D3DUtil.h"
#include "D3DRes.h"


// A parameter of this type is passed to SetViewMatrix to set up the
// D3D view transformation matrix for a normal view, right-eye
// view, or left-eye view (the latter two are for stereo modes)
enum D3DFWVIEW
{
    D3DFWVIEW_CENTER,
    D3DFWVIEW_RIGHT,
    D3DFWVIEW_LEFT,
};


//-----------------------------------------------------------------------------
// Name: class CD3DApplication
// Desc:
//-----------------------------------------------------------------------------
class CD3DApplication
{
    // Internal varaibles and member functions
    CD3DFramework7* m_pFramework;

    BOOL            m_bActive;
    BOOL            m_bReady;
    BOOL            m_bWindowed;
    BOOL            m_bToggleFullscreen;

    BOOL            m_bFrameMoving;
    BOOL            m_bSingleStep;
    DWORD           m_dwBaseTime;
    DWORD           m_dwStopTime;

    D3DVECTOR       m_vEyePt;
    D3DVECTOR       m_vLookatPt;
    D3DVECTOR       m_vUpVec;
    FLOAT           m_fEyeDistance; // Offset of each eye from m_vEyePt
    BOOL            m_bUseViewPoints;

    HRESULT Initialize3DEnvironment();
    HRESULT Change3DEnvironment();
    HRESULT Render3DEnvironment();
    VOID    Cleanup3DEnvironment();
    VOID    DisplayFrameworkError( HRESULT, DWORD );

protected:
    D3DEnum_DeviceInfo*  m_pDeviceInfo;
    HWND                 m_hWnd;
    LPDIRECTDRAW7        m_pDD;
    LPDIRECT3D7          m_pD3D;
    LPDIRECT3DDEVICE7    m_pd3dDevice;
    LPDIRECTDRAWSURFACE7 m_pddsRenderTarget;
    LPDIRECTDRAWSURFACE7 m_pddsRenderTargetLeft; // For stereo modes

    // Overridable variables for the app
    TCHAR*               m_strWindowTitle;
    BOOL                 m_bAppUseZBuffer;
    BOOL                 m_bShowStats;
    HRESULT              (*m_fnConfirmDevice)(DDCAPS*, D3DDEVICEDESC7*);

    // Overridable functions for the 3D scene created by the app
    virtual HRESULT OneTimeSceneInit()     { return S_OK; }
    virtual HRESULT InitDeviceObjects()    { return S_OK; }
    virtual HRESULT DeleteDeviceObjects()  { return S_OK; }
    virtual HRESULT Render()               { return S_OK; }
    virtual HRESULT FrameMove( FLOAT )     { return S_OK; }
    virtual HRESULT RestoreSurfaces()      { return S_OK; }
    virtual HRESULT FinalCleanup()         { return S_OK; }

    // View control functions
    virtual VOID    SetViewParams( D3DVECTOR *vEyePt,
                                   D3DVECTOR *vLookatPt,
                                   D3DVECTOR *vUpVec,
                                   FLOAT      fEyeDistance );
    virtual HRESULT SetViewMatrix( D3DFWVIEW view );

    // Miscellaneous functions
    VOID    ShowStats();
    VOID    OutputText( DWORD x, DWORD y, CHAR* str );

public:
    // Functions to create, run, pause, and clean up the application
    virtual HRESULT Create( HINSTANCE, LPSTR );
    virtual INT     Run();
    virtual LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    virtual VOID    Pause( BOOL bPause );

    // Class constructor
    CD3DApplication();
};




#endif // D3DAPP_H


