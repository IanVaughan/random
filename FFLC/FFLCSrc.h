//---------------------------------------------------------------------------
#ifndef FFLCSrcH
#define FFLCSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFFLC : public TForm
{
__published:	// IDE-managed Components
    TPageControl *Picker;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TPanel *Panel1;
    TSpeedButton *A;
    TSpeedButton *B;
    TSpeedButton *C;
    TSpeedButton *D;
    TSpeedButton *E;
    TSpeedButton *F;
    TSpeedButton *G;
    TSpeedButton *H;
    TSpeedButton *I;
    TSpeedButton *J;
    TSpeedButton *K;
    TSpeedButton *L;
    TSpeedButton *M;
    TSpeedButton *Z;
    TSpeedButton *N;
    TSpeedButton *O;
    TSpeedButton *P;
    TSpeedButton *Q;
    TSpeedButton *R;
    TSpeedButton *S;
    TSpeedButton *T;
    TSpeedButton *U;
    TSpeedButton *V;
    TSpeedButton *W;
    TSpeedButton *X;
    TSpeedButton *Y;
    TLabel *Label1;
    TBitBtn *add;
    TButton *Save;
    TListBox *ListBox1;
    TButton *Remove;
    TBevel *Bevel1;
    TBitBtn *MoveUp;
    TBitBtn *MoveDown;
    TCheckBox *Sorted;
    TSpeedButton *_1;
    TSpeedButton *_2;
    TSpeedButton *_3;
    TSpeedButton *_4;
    TSpeedButton *_5;
    TSpeedButton *_6;
    TSpeedButton *_7;
    TSpeedButton *_8;
    TSpeedButton *_9;
    TSpeedButton *_0;
    TSaveDialog *SaveDialog1;
    TOpenDialog *OpenDialog1;
    TButton *Load;
    TEdit *Edit1;
    TLabel *Label2;
    void __fastcall AClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall addClick(TObject *Sender);
    void __fastcall PickerChange(TObject *Sender);
    void __fastcall SortedClick(TObject *Sender);
    void __fastcall MoveUpClick(TObject *Sender);
    void __fastcall MoveDownClick(TObject *Sender);
    void __fastcall SaveClick(TObject *Sender);
    void __fastcall LoadClick(TObject *Sender);
    void __fastcall RemoveClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ListBox1DblClick(TObject *Sender);

private:
    void ShowLettersLeft(TSpeedButton *firstLetter);
    //this is used after adding a pair so that all the buttons are avaible again
    void EnableAllButtons();
    //used when two buttons have been pressed so no more can be added
    void DisableAllButtons();
    //this allows the load method to match up the text chars to actual buttons
    TSpeedButton *GetButton(String chr, int);

    int ReplacePos;

public:
    __fastcall TFFLC(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFFLC *FFLC;
//---------------------------------------------------------------------------
#endif
