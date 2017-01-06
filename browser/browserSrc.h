//---------------------------------------------------------------------------
#ifndef browserSrcH
#define browserSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <NMHTML.hpp>
#include <NMURL.hpp>
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    THTML *HTML1;
    TStatusBar *StatusBar1;
    TNMURL *NMURL1;
    TPanel *Panel1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TComboBox *ComboBox1;void __fastcall ComboBox1Click(TObject *Sender);
    void __fastcall ComboBox1KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
