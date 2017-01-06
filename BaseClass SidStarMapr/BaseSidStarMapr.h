//---------------------------------------------------------------------------
#ifndef BaseSidStarMaprH
#define BaseSidStarMaprH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WrapGrid.h"
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TBaseSidStarMapr : public TForm
{
__published:	// IDE-managed Components
    TPanel *nameInfoP;
    TPanel *saveCancelP;
    TButton *saveBTN;
    TButton *cancelBTN;
    TPanel *mainCenter;
    TSplitter *Splitter1;
    TSplitter *Splitter2;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TLabel *nameL;
    TLabel *minAltL;
    TLabel *maxAltL;
    TComboBox *runwayTransitionCB;
    TGroupBox *runwayTransitionGB;
    TButton *assocRunwayNewBTN;
    TButton *assocRunwayDelBTN;
    TPanel *fixRouteP;
    TWrapGrid *fixWG;
    TPanel *fixUpDownP;
    TPanel *endRouteP;
    TLabel *endRouteMemoL;
    TSpeedButton *fixUpBTN;
    TPanel *fixDownBtnL;
    TSpeedButton *fixDownBTN;
    TPanel *startRouteP;
    TLabel *startRouteMemoL;
    TPanel *commonP;
    TLabel *commonRouteMemoL;
    TPanel *commonRouteP;
    TWrapGrid *commonWG;
    TPanel *commonUpDownP;
    TSpeedButton *commonUpBTN;
    TPanel *commonDownBtnP;
    TSpeedButton *commonDownBTN;
    TGroupBox *fixTransitionGB;
    TComboBox *fixCB;
    TButton *fixNewBTN;
    TButton *fixDelBTN;
    TButton *fixEditBTN;
    TPanel *runwayRouteP;
    TWrapGrid *runwayWG;
    TPanel *runwayUpDownP;
    TSpeedButton *runwayUpBTN;
    TPanel *runwayUpDownBtnP;
    TSpeedButton *runwayDownBTN;
    TSpeedButton *SpeedButton1;
    void __fastcall cancelBTNClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Splitter1Moved(TObject *Sender);
    void __fastcall Splitter2Moved(TObject *Sender);
    void __fastcall saveBTNClick(TObject *Sender);

    void __fastcall Splitter2CanResize(TObject *Sender, int &NewSize,
          bool &Accept);
    
    
    void __fastcall SpeedButton1Click(TObject *Sender);
protected:
//    void FillMemo(TQuery* route_leg_query, TListBox* memo);
    void FillStartTransitionList();
    void FillEndTransitionList();
    void FillFixMemoList();
    void FillCommonMemoList();
    void FillRunwayMemoList();
    virtual bool Execute(); 

private:	// User declarations
    void __fastcall WMGetMinMaxInfo(TWMGetMinMaxInfo &Msg);  // prototype for msg handler

public:		// User declarations
    __fastcall TBaseSidStarMapr(TComponent* Owner);
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_GETMINMAXINFO,TWMGetMinMaxInfo,WMGetMinMaxInfo)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TBaseSidStarMapr *BaseSidStarMapr;
//---------------------------------------------------------------------------
#endif



