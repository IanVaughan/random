//---------------------------------------------------------------------------
#ifndef MapEditorSrcFakeH
#define MapEditorSrcFakeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TMapEditorFormFake : public TForm
{
__published:
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);

private:

public:
    __fastcall TMapEditorFormFake(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TMapEditorFormFake *MapEditorFormFake;
//---------------------------------------------------------------------------
#endif
