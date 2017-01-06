//---------------------------------------------------------------------------
#ifndef D3DTestSrcH
#define D3DTestSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#define D3D_OVERLOADS
#define INITGUID
#include "ddraw.h"
#include "d3d.h"
#include "d3drm.h"

//---------------------------------------------------------------------------
class TD3DTestForm : public TForm
{
__published:

    void __fastcall FormResize(TObject *Sender);
private:
    HRESULT CreateEverything();
    HRESULT Initialize3DEnvironment( HWND hWnd, GUID* pDriverGUID, const GUID* pDeviceGUID );
    VOID GetDXVersion( DWORD* pdwDXVersion, DWORD* pdwDXPlatform );
    HRESULT App_InitDeviceObjects( LPDIRECT3DDEVICE7 pd3dDevice );
    HRESULT App_FrameMove( LPDIRECT3DDEVICE7 pd3dDevice, FLOAT fTimeKey );
    HRESULT App_Render( LPDIRECT3DDEVICE7 pd3dDevice, D3DRECT* prcViewRect );
    HRESULT ShowFrame();
    HRESULT Cleanup3DEnvironment();

    HRESULT Render3DEnvironment();
    HRESULT RestoreSurfaces();
    VOID App_DeleteDeviceObjects( LPDIRECT3DDEVICE7 pd3dDevice );

    void __fastcall timerRunning(TObject *Sender);

    BOOL MyCreate(D3DVECTOR* pVectors, int nVectors, D3DVECTOR* pNormals,
        int nNormals, int* pFaceData, BOOL bAutoGen = false);
    BOOL ShapeCreateWall(double x, double y);
    BOOL DrawAnythingPlease(LPDIRECT3DDEVICE7 d3dd);


public:

    __fastcall TD3DTestForm(TComponent* Owner);
    __fastcall ~TD3DTestForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TD3DTestForm *D3DTestForm;
//---------------------------------------------------------------------------
#endif
