//---------------------------------------------------------------------------
#ifndef testQH
#define testQH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <DBCGrids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TRadioButton *mApprRB;
    TRadioButton *SidRB;
    TRadioButton *StarRB;
    TRadioButton *commonRB;
    TRadioButton *fixRB;
    TRadioButton *runwayRB;
    TDBGrid *route_type;
    TDBGrid *route_element;
    TDBGrid *route_leg;
    TDBGrid *routeLegTypeGrid;
    TDBGrid *profileGrid;
    TGroupBox *Profile;
    TRadioButton *terminatorRB;
    TRadioButton *conditionRB;
    TDBNavigator *nav;
    TButton *updateAll;
    TButton *Button1;
    TButton *revertAll;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TTimer *Timer;
    TCheckBox *cb1;
    TCheckBox *cb2;
    TCheckBox *cb3;
    TCheckBox *cb4;
    TCheckBox *cb5;
    TButton *Button2;
    TCheckBox *IsSequencedCB;
    TButton *Button3;
    void __fastcall FormShow(TObject *Sender);
    
    void __fastcall mApprRBClick(TObject *Sender);
    void __fastcall SidRBClick(TObject *Sender);
    void __fastcall StarRBClick(TObject *Sender);
    void __fastcall commonRBClick(TObject *Sender);
    void __fastcall fixRBClick(TObject *Sender);
    void __fastcall runwayRBClick(TObject *Sender);
    void __fastcall terminatorRBClick(TObject *Sender);
    void __fastcall conditionRBClick(TObject *Sender);
    void __fastcall updateAllClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall revertAllClick(TObject *Sender);
    void __fastcall route_typeEnter(TObject *Sender);
    void __fastcall route_elementEnter(TObject *Sender);
    void __fastcall routeLegTypeGridEnter(TObject *Sender);
    void __fastcall profileGridEnter(TObject *Sender);
    void __fastcall route_legEnter(TObject *Sender);
    
    
    void __fastcall route_legCellClick(TColumn *Column);
    void __fastcall TimerTimer(TObject *Sender);
    
    
    void __fastcall Button2Click(TObject *Sender);
    
    void __fastcall mApprTUpdateRecord(TDataSet *DataSet,
          TUpdateKind UpdateKind, TUpdateAction &UpdateAction);
    void __fastcall routeTypeDSUpdateData(TObject *Sender);
    
    void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
  