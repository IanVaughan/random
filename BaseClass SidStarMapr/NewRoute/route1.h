//---------------------------------------------------------------------------
#ifndef route1H
#define route1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "WrapGrid.h"
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TButton *addBTN;
    TButton *cancelBTN;
    TRichEdit *RichEdit1;
    TWrapGrid *WrapGrid1;
    TWrapGrid *WrapGrid2;
    TLabel *Label4;
    TLabel *Label5;
    TRadioButton *fixtoFixRB;
    TRadioButton *directToFixRB;
    TRadioButton *courseToFixRB;
    TRadioButton *courseFromFixRB;
    TRadioButton *courseToFlyRB;
    TRadioButton *courseToInterceptRadialRB;
    TRadioButton *holdAtFixRB;
    TRadioButton *holdAtFixForNOrbitsRB;
    TRadioButton *flyDMEArcRB;
    TRadioButton *courseFromRunwayRB;
    TNotebook *dataNB;
    TLabel *Label1;
    TLabel *Label2;
    TComboBox *ComboBox3;
    TComboBox *ComboBox4;
    TLabel *Label3;
    TComboBox *ComboBox5;
    TLabel *fromLabel;
    TLabel *toLabel;
    TComboBox *ComboBox1;
    TBevel *Bevel1;
    TBevel *Bevel2;
    TBevel *Bevel3;
    TBevel *Bevel4;
    TPopupMenu *PopupMenu1;
    TMenuItem *Add1;
    TMenuItem *Edit1;
    TMenuItem *Delete1;
    TMenuItem *Level1;
    TMenuItem *Speed1;
    TMenuItem *AddConidition1;
    TMenuItem *Distance1;
    TMenuItem *Level2;
    TMenuItem *Radial1;
    TLabel *Label8;
    TEdit *Edit2;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TRadioButton *RadioButton3;
    TEdit *Edit3;
    TLabel *Label9;
    TComboBox *ComboBox6;
    TRadioButton *RadioButton4;
    TRadioButton *RadioButton5;
    TRadioButton *RadioButton6;
    TEdit *Edit4;
    TLabel *Label10;
    TComboBox *ComboBox7;
    TRadioButton *RadioButton7;
    TRadioButton *RadioButton9;
    TEdit *Edit5;
    TRadioButton *RadioButton8;
    TRadioButton *RadioButton11;
    TEdit *Edit6;
    TComboBox *ComboBox8;
    TLabel *Label12;
    TEdit *Edit7;
    TLabel *Label13;
    TComboBox *ComboBox9;
    TComboBox *ComboBox10;
    TLabel *Label14;
    TLabel *Label15;
    TEdit *Edit8;
    TEdit *Edit9;
    TRadioButton *RadioButton13;
    TRadioButton *RadioButton14;
    TEdit *Edit11;
    TLabel *Label17;
    TRadioButton *RadioButton17;
    TRadioButton *RadioButton18;
    TEdit *Edit12;
    TLabel *Label18;
    TLabel *Label19;
    TMemo *Memo1;
    TPanel *toFromComboP2;
    TRadioButton *RadioButton16;
    TRadioButton *RadioButton15;
    TPanel *toFromComboBoxP;
    TRadioButton *RadioButton10;
    TRadioButton *RadioButton12;
    TBevel *Bevel5;
    TBevel *Bevel6;
    TBevel *Bevel7;
    TBevel *Bevel8;
    TBevel *Bevel9;
    TBevel *Bevel10;
    TBevel *Bevel11;
    TBevel *Bevel12;
    TBevel *Bevel13;
    TBevel *Bevel14;
    TBevel *Bevel15;
    TBevel *Bevel16;
    TBevel *Bevel17;
    TBevel *Bevel18;
    TBevel *Bevel19;
    TBevel *Bevel20;
    TBevel *Bevel21;
    TBevel *Bevel22;
    TBevel *Bevel23;
    TBevel *Bevel24;
    TBevel *Bevel25;
    TBevel *Bevel26;
    TBevel *Bevel27;
    TBevel *Bevel28;
    void __fastcall fixtoFixRBClick(TObject *Sender);
    void __fastcall directToFixRBClick(TObject *Sender);
    void __fastcall courseToFixRBClick(TObject *Sender);
    void __fastcall courseFromFixRBClick(TObject *Sender);
    void __fastcall courseToFlyRBClick(TObject *Sender);
    void __fastcall courseToInterceptRadialRBClick(TObject *Sender);
    void __fastcall holdAtFixRBClick(TObject *Sender);
    void __fastcall holdAtFixForNOrbitsRBClick(TObject *Sender);
    void __fastcall flyDMEArcRBClick(TObject *Sender);
    void __fastcall courseFromRunwayRBClick(TObject *Sender);
    void __fastcall addBTNClick(TObject *Sender);
    void __fastcall cancelBTNClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    
    
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
