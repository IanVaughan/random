//---------------------------------------------------------------------------
#ifndef CodeViewCreatorSrcH
#define CodeViewCreatorSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------

class TCodeViewCreator : public TForm
{
__published:
    TDirectoryListBox *DirectoryListBox;
    TLabel *Label1;
    TBitBtn *GoBTN;
    TBitBtn *CancelBTN;
    void __fastcall GoBTNClick(TObject *Sender);
    void __fastcall CancelBTNClick(TObject *Sender);

private:

public:
    __fastcall TCodeViewCreator(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TCodeViewCreator *CodeViewCreator;
//---------------------------------------------------------------------------
#endif
