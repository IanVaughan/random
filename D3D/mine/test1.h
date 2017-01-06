//---------------------------------------------------------------------------
#ifndef test1H
#define test1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "..\\D3DError.h"
//---------------------------------------------------------------------------
#define SafeRelease(x) { if(x) {x->Release(); x = NULL;} }

//---------------------------------------------------------------------------
class TX : public TForm
{
__published:

private:
    HRESULT CreateDD();
    HRESULT CreateSurfaces();
    HRESULT Create3D();

    TD3DError* err;

public:
    __fastcall TX(TComponent* Owner);
    __fastcall ~TX();
};
//---------------------------------------------------------------------------
extern PACKAGE TX *X;
//---------------------------------------------------------------------------
#endif
