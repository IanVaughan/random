//---------------------------------------------------------------------------
#ifndef MusicListSrcH
#define MusicListSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TMusicList : public TForm
{
__published:	// IDE-managed Components
    TTreeView *TreeView1;
    TPanel *Panel1;
    TBitBtn *PrintBTN;
    TBitBtn *SaveBTN;
    TBitBtn *CloseBTN;
    TOpenDialog *OpenDialog1;
    TDirectoryListBox *dlb;
    TFileListBox *flb;
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TMusicList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMusicList *MusicList;
//---------------------------------------------------------------------------
#endif
