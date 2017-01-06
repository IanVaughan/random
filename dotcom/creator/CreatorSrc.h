//---------------------------------------------------------------------------
#ifndef CreatorSrcH
#define CreatorSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

class TCreator : public TForm
{
__published:
    TProgressBar *ProgressBar1;

private:
    bool FindHeaders(String dir);

public:
    __fastcall TCreator(TComponent* Owner);

    bool Create(String);

};
//---------------------------------------------------------------------------
extern PACKAGE TCreator *Creator;
//---------------------------------------------------------------------------
#endif
