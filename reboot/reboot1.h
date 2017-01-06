//---------------------------------------------------------------------------
#ifndef reboot1H
#define reboot1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TPopupMenu *PopupMenu1;
    TMenuItem *Logoff1;
    TMenuItem *Shutdown1;
    TMenuItem *Reboot1;
    TButton *Button1;
    void __fastcall Logoff1Click(TObject *Sender);
    void __fastcall Reboot1Click(TObject *Sender);
    void __fastcall Shutdown1Click(TObject *Sender);

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    
    void __fastcall Button1Click(TObject *Sender);
    
private:	// User declarations
    unsigned int iconmessage;
    void AddTrayIcon();
    void RemoveTrayIcon();

protected:
    virtual void __fastcall WndProc(Messages::TMessage &Message);

public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
