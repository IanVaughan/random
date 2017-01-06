//---------------------------------------------------------------------------
#ifndef DMsrcH
#define DMsrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TDMform : public TDataModule
{
__published:	// IDE-managed Components
    TQuery *get_mAppr_ID;
    TDataSource *routeTypeDS;
    TTable *mApprT;
    TTable *SidT;
    TTable *StarT;
    TTable *routeElementT;
    TDataSource *routeElementDS;
    TQuery *get_RE_ID;
    TQuery *get_RF_ID;
    TTable *routeCommonLegT;
    TDataSource *routesDS;
    TTable *routeFixLegT;
    TTable *routeRunwayLegT;
    TQuery *get_RLT_ID;
    TDataSource *routeLegTypeDS;
    TTable *routeLegTypeT;
    TTable *rConditionT;
    TDataSource *profileDS;
    TDatabase *BEST;
    TQuery *get_Sid_ID;
    TQuery *get_Star_ID;
    TTable *rTerminatorT;
    TTable *runwayT;
    TTable *fixT;
private:	// User declarations
public:		// User declarations
    __fastcall TDMform(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDMform *DMform;
//---------------------------------------------------------------------------
#endif
