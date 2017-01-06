//---------------------------------------------------------------------------
#ifndef D3DSrcH
#define D3DSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TD3D : public TForm
{
__published:
void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);

private:
    HRESULT Setup();
    HRESULT InitDD();
    HRESULT Init3D();
    HRESULT InitOverlay();

    void Create_objects();
    void render_frame(float elapsed);
    void __fastcall Loop(TObject *Sender);
    void __fastcall z(TObject *Sender);

    void CleanUp();

    void Error(HRESULT res);

    BOOL ShapeCreateWall(void* pShape, double x, double y);

public:
    __fastcall TD3D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TD3D *D3D;
//---------------------------------------------------------------------------
#endif
