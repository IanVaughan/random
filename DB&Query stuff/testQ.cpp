//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "testQ.h"
#include "DMsrc.h"
#include "SIDsrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
void setColWidth(TDBGrid *DataGrid);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
    setColWidth(route_type);
    setColWidth(route_element);
    setColWidth(route_leg);
    setColWidth(routeLegTypeGrid);
    setColWidth(profileGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mApprRBClick(TObject *Sender)
{
    DMform->routeElementT->Active = false;
    DMform->routeElementT->MasterFields = "" ;

    DMform->routeTypeDS->DataSet = DMform->mApprT ;
    DMform->routeElementT->MasterFields = "MApproach_ID" ;
    DMform->routeElementT->IndexFieldNames = "MApproach_ID" ;
    DMform->routeElementT->Active = true;

    setColWidth(route_type);
    setColWidth(route_element);
    setColWidth(routeLegTypeGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SidRBClick(TObject *Sender)
{
    DMform->routeElementT->Active = false;

    //set fields to NULL so that when changing the DS is donest try finding the fields
    DMform->routeElementT->MasterFields = "" ;

    DMform->routeTypeDS->DataSet = DMform->SidT ;
    DMform->routeElementT->MasterFields = "SID_ID" ;
    DMform->routeElementT->IndexFieldNames = "SID_ID" ;
    DMform->routeElementT->Active = true;

    setColWidth(route_type);
    setColWidth(route_element);
    setColWidth(routeLegTypeGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StarRBClick(TObject *Sender)
{
    DMform->routeElementT->Active = false;
    DMform->routeElementT->MasterFields = "" ;

    DMform->routeTypeDS->DataSet = DMform->StarT ;
    DMform->routeElementT->MasterFields = "STAR_ID" ;
    DMform->routeElementT->IndexFieldNames = "STAR_ID" ;
    DMform->routeElementT->Active = true;

    setColWidth(route_type);
    setColWidth(route_element);
    setColWidth(routeLegTypeGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::commonRBClick(TObject *Sender)
{
    DMform->routeLegTypeT->Close();
    DMform->routeLegTypeT->MasterFields = "" ;
    DMform->routesDS->DataSet = DMform->routeCommonLegT ;

    DMform->routeLegTypeT->MasterFields = "Route_Common_Leg_ID" ;
    DMform->routeLegTypeT->IndexFieldNames = "Common_Leg_ID";
    DMform->routeLegTypeT->Open();

    setColWidth(route_leg);
    setColWidth(routeLegTypeGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::fixRBClick(TObject *Sender)
{
    DMform->routeLegTypeT->Close();
    DMform->routeLegTypeT->MasterFields = "" ;
    DMform->routesDS->DataSet = DMform->routeFixLegT ;

    DMform->routeLegTypeT->MasterFields = "Route_Fix_Leg_ID" ;
    DMform->routeLegTypeT->IndexFieldNames = "Fix_Leg_ID";
    DMform->routeLegTypeT->Open();

    setColWidth(route_leg);
    setColWidth(routeLegTypeGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::runwayRBClick(TObject *Sender)
{
    DMform->routeLegTypeT->Close();
    DMform->routeLegTypeT->MasterFields = "" ;

    DMform->routesDS->DataSet = DMform->routeRunwayLegT ;

    DMform->routeLegTypeT->MasterFields = "Route_Runway_Leg_ID" ;
    DMform->routeLegTypeT->IndexFieldNames = "Runway_Leg_ID";
    DMform->routeLegTypeT->Open();

    setColWidth(route_leg);
    setColWidth(routeLegTypeGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::terminatorRBClick(TObject *Sender)
{
    DMform->profileDS->DataSet = DMform->rTerminatorT ;

    setColWidth(profileGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::conditionRBClick(TObject *Sender)
{
    DMform->profileDS->DataSet = DMform->rConditionT ;

    setColWidth(profileGrid);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::updateAllClick(TObject *Sender)
{
    DMform->BEST->StartTransaction();

    // try to write the updates to the database
    try
    {
        int ID;

        if(DMform->mApprT->UpdatesPending)
        if(mApprRB->Checked) {
            DMform->mApprT->ApplyUpdates();

            DMform->get_mAppr_ID->ParamByName("MApproach_Name")->AsString =
                DMform->mApprT->FieldByName("MApproach_Name")->AsString ;
            DMform->get_mAppr_ID->Open();
            ID = DMform->get_mAppr_ID->FieldByName("MApproach_ID")->AsInteger ;
            DMform->get_mAppr_ID->Close();

            //reset the sql 'cos the where by clause is differnt for sid/star/mappr
            DMform->get_RE_ID->SQL->Clear();
            DMform->get_RE_ID->SQL->Add("select *");
            DMform->get_RE_ID->SQL->Add("from Route_Element");
            DMform->get_RE_ID->SQL->Add("where MApproach_ID = :MApproach_ID");

            //pre-setup the next sql, 'cos its dependant on where we are now, ie sid/star/mappr
            DMform->get_RE_ID->ParamByName("MApproach_ID")->AsInteger = ID ;
        }

        if(DMform->SidT->UpdatesPending)
        if(SidRB->Checked)  {
            DMform->SidT->ApplyUpdates();

            DMform->get_Sid_ID->ParamByName("SID_Name")->AsString =
                DMform->mApprT->FieldByName("SID_Name")->AsString ;
            DMform->get_Sid_ID->Open();
            ID = DMform->get_Sid_ID->FieldByName("SID_ID")->AsInteger ;
            DMform->get_Sid_ID->Close();

            DMform->get_RE_ID->SQL->Clear();
            DMform->get_RE_ID->SQL->Add("select *");
            DMform->get_RE_ID->SQL->Add("from Route_Element");
            DMform->get_RE_ID->SQL->Add("where SID_ID = :SID_ID");
            DMform->get_RE_ID->ParamByName("SID_ID")->AsInteger = ID ;
        }

        if(DMform->StarT->UpdatesPending)
        if(StarRB->Checked) {
            DMform->StarT->ApplyUpdates();

            DMform->get_Star_ID->ParamByName("STAR_Name")->AsString =
                DMform->mApprT->FieldByName("STAR_Name")->AsString ;
            DMform->get_Star_ID->Open();
            ID = DMform->get_Star_ID->FieldByName("STAR_ID")->AsInteger ;
            DMform->get_Star_ID->Close();

            DMform->get_RE_ID->SQL->Clear();
            DMform->get_RE_ID->SQL->Add("select *");
            DMform->get_RE_ID->SQL->Add("from Route_Element");
            DMform->get_RE_ID->SQL->Add("where STAR_ID = :STAR_ID");
            DMform->get_RE_ID->ParamByName("SID_ID")->AsInteger = ID ;
        }

        bool route_leg_type_inserted = false ;
        //only apply updates to two joins & Route_Leg_Type if the Route_Leg_Type table needs updating. eg. new/edit/delete
        if(DMform->routeLegTypeT->UpdatesPending) {
            if(DMform->routeLegTypeT->UpdateStatus() == usInserted) {
                //this will have to be moved, the applyUpdates can only happen if
                // no new sid/star/mappr have been made, if they have then there is no
                // id required field. need to have if (bool inserted_sid/star/mapr) to do
                // like in routes
                DMform->routeLegTypeT->ApplyUpdates();
                route_leg_type_inserted = true ;

                DMform->get_RLT_ID->Open();
                DMform->get_RLT_ID->Last();
                ID = DMform->get_RLT_ID->FieldByName("Route_Leg_Type_ID")->AsInteger ;
                DMform->get_RLT_ID->Close();
            }
        }
        //only update profiles if changed
        if(DMform->rTerminatorT->UpdatesPending) {
            //if a new record AND a new Route_Leg_Type record was make, then set this ID
            if(DMform->rTerminatorT->UpdateStatus() == usInserted && route_leg_type_inserted) {
                int temp = DMform->rTerminatorT->FieldByName("Route_Leg_Type_ID")->AsInteger ;
                temp = DMform->rTerminatorT->FieldByName("Route_Terminator_ID")->AsInteger ;
                temp = DMform->rTerminatorT->FieldByName("Range")->AsInteger ;

                DMform->rTerminatorT->Edit();
                DMform->rTerminatorT->FieldByName("Route_Leg_Type_ID")->AsInteger = ID ;
                DMform->rTerminatorT->Post();

                DMform->rTerminatorT->ApplyUpdates();
            }
            else
                DMform->rTerminatorT->ApplyUpdates();
        }

        DMform->BEST->Commit(); // on success, commit the changes;
    }
    catch (...)
    {
        DMform->BEST->Rollback(); // on failure, undo the changes
        throw; // throw the exception to prevent a call to CommitUpdates!
    }

    // on success, clear the cache
    DMform->mApprT->CommitUpdates();
    DMform->SidT->CommitUpdates();
    DMform->StarT->CommitUpdates();

    DMform->routeElementT->CommitUpdates();

    DMform->routeCommonLegT->CommitUpdates();
    DMform->routeFixLegT->CommitUpdates();
    DMform->routeRunwayLegT->CommitUpdates();

    DMform->routeLegTypeT->CommitUpdates();

    DMform->rTerminatorT->CommitUpdates();

//    ApplyUpdates(TDBDataSet* const * DataSets, const int DataSets_Size);
//    BEST->ApplyUpdates(routesT, 1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::revertAllClick(TObject *Sender)
{
    DMform->mApprT->CancelUpdates();
    DMform->SidT->CancelUpdates();
    DMform->StarT->CancelUpdates();

    DMform->routeElementT->CancelUpdates();

    DMform->routeCommonLegT->CancelUpdates();
    DMform->routeFixLegT->CancelUpdates();
    DMform->routeRunwayLegT->CancelUpdates();

    DMform->routeLegTypeT->CancelUpdates();

    DMform->rTerminatorT->CancelUpdates();
}
//---------------------------------------------------------------------------

void setColWidth(TDBGrid *DataGrid)
{
    int DataWidth ;
    for(int x = 0; x < DataGrid->FieldCount; x++)
    {
         String ColTitle = DataGrid->Columns->Items[x]->Title->Caption;
         DataWidth = DataGrid->Canvas->TextWidth(ColTitle)+5;

         DataGrid->Columns->Items[x]->Width = DataWidth;
    }
}

// -----------------------------------------------------------------------------

void __fastcall TForm1::route_typeEnter(TObject *Sender)
{
    nav->DataSource = DMform->routeTypeDS ;
    setColWidth((TDBGrid*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::route_elementEnter(TObject *Sender)
{
    nav->DataSource = DMform->routeElementDS ;
    setColWidth((TDBGrid*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::routeLegTypeGridEnter(TObject *Sender)
{
    nav->DataSource = DMform->routeLegTypeDS ;
    setColWidth((TDBGrid*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::profileGridEnter(TObject *Sender)
{
    nav->DataSource = DMform->profileDS ;
    setColWidth((TDBGrid*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::route_legEnter(TObject *Sender)
{
    nav->DataSource = DMform->routesDS;
    setColWidth((TDBGrid*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::route_legCellClick(TColumn *Column)
{
    setColWidth(routeLegTypeGrid);
}
// -----------------------------------------------------------------------------

void __fastcall TForm1::TimerTimer(TObject *Sender)
{
    if(DMform->mApprT->UpdatesPending || DMform->SidT->UpdatesPending || DMform->StarT->UpdatesPending ||
        DMform->routeElementT->UpdatesPending ||
        DMform->routeLegTypeT->UpdatesPending ||
        DMform->rTerminatorT->UpdatesPending ||
        DMform->routeCommonLegT->UpdatesPending || DMform->routeFixLegT->UpdatesPending || DMform->routeRunwayLegT->UpdatesPending) {

        updateAll->Enabled = true ;
        revertAll->Enabled = true ;
    }
    else {
        updateAll->Enabled = false ;
        revertAll->Enabled = false ;
    }

    if(DMform->mApprT->UpdatesPending || DMform->SidT->UpdatesPending || DMform->StarT->UpdatesPending) cb1->State = cbGrayed ;
        else cb1->State = cbUnchecked ;
    if(DMform->mApprT->UpdatesPending && DMform->SidT->UpdatesPending && DMform->StarT->UpdatesPending) cb1->State = cbChecked ;

    if(DMform->routeElementT->UpdatesPending) cb2->State = cbChecked ;
        else cb2->State = cbUnchecked ;

    if(DMform->routeCommonLegT->UpdatesPending || DMform->routeFixLegT->UpdatesPending || DMform->routeRunwayLegT->UpdatesPending)
        cb3->State = cbGrayed ;
    else cb3->State = cbUnchecked ;
    if(DMform->routeCommonLegT->UpdatesPending && DMform->routeFixLegT->UpdatesPending && DMform->routeRunwayLegT->UpdatesPending)
        cb3->State = cbChecked ;

    if(DMform->routeLegTypeT->UpdatesPending) cb4->State = cbChecked ;
        else cb4->State = cbUnchecked ;

    if(DMform->rTerminatorT->UpdatesPending) cb5->State = cbChecked ;
    else cb5->State = cbUnchecked ;

    if(DMform->mApprT->IsSequenced()) IsSequencedCB->Checked = true ;else IsSequencedCB->Checked = false ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    DMform->mApprT->UpdateRecordTypes.Clear();
    DMform->mApprT->UpdateRecordTypes << rtInserted;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mApprTUpdateRecord(TDataSet *DataSet,
      TUpdateKind UpdateKind, TUpdateAction &UpdateAction)
{
//TUpdateAction { uaFail, uaAbort, uaSkip, uaRetry, uaApplied };

//    if(UpdateKind == ukModify)
//    if(UpdateKind == ukInsert)
//    if(UpdateKind == ukDelete)

/*    int routeID = mApprT->FieldByName("MApproach_ID")->AsInteger;
    int an = DataSet->FieldByName("MApproach_ID")->AsInteger;

    bool well = mApprT->UpdatesPending;

    UpdateAction = uaApplied ;
*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::routeTypeDSUpdateData(TObject *Sender)
{
//    Application->MessageBox("Routes will need saving.","Update",MB_OK|MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
    SIDform->ShowModal();    
}
//---------------------------------------------------------------------------

