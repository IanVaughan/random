//---------------------------------------------------------------------------
#ifndef DataPrepSrcFakeH
#define DataPrepSrcFakeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
// -----------------------------------------------------------------------------
#include "MapEditorFake.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);

private:
    bool ToBeCalled(DPFormShowData *dataIn);

public:
    __fastcall TMainForm(TComponent* Owner);

    DPFormShowData *MapData;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
