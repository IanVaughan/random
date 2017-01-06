//---------------------------------------------------------------------------
#ifndef dxTestH
#define dxTestH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <dxmgr.h>

// Release interface only if non-NULL, then set to NULL
#define RELEASE( p ) ( (p) ? ((p)->Release(), p = NULL) : NULL )

//---------------------------------------------------------------------------
class TdxTestForm : public TForm
{
__published:

private:
    HRESULT Initialize( HWND _hwnd );
    HRESULT PrepareToDraw( );
    HRESULT StopDrawing( );


    // Objects created by Initialize and retained
    HWND hwnd;
    IDXMgr *pDXMgr;

    // Transient objects that get affected by PrepareToDraw
    LPDIRECT3DDEVICE3 pD3DDevice;
    float fAngle;

    RECT rClient;
    bool bPaused;
    bool bActive;


public:
    __fastcall TdxTestForm(TComponent* Owner);
    __fastcall ~TdxTestForm();

};
//---------------------------------------------------------------------------
extern PACKAGE TdxTestForm *dxTestForm;
//---------------------------------------------------------------------------
#endif
