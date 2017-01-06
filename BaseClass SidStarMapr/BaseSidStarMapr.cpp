//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BaseSidStarMapr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WrapGrid"
#pragma resource "*.dfm"
TBaseSidStarMapr *BaseSidStarMapr;
//---------------------------------------------------------------------------

__fastcall TBaseSidStarMapr::TBaseSidStarMapr(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TBaseSidStarMapr::FormShow(TObject *Sender)
{
    Width = 443 ;
    Height = 500 ;

    runwayWG->WrapCell[0][0]->Text = "RUNWAY wrap grid - This is a test string, and is going to be very long indeed, so long in fact, that is should wrap around the cell, this is because this is a wrap grid" ;
    runwayWG->RowCount ++ ;
    runwayWG->WrapCell[0][1]->Text = "This is a short one." ;
    runwayWG->RowCount ++ ;
    runwayWG->WrapCell[0][2]->Text = "And this is another long one, just to make sure it wraps ok, so does it work? you tell me! your the one looking at it. so, give me you verdict?" ;
    runwayWG->RowCount ++ ;
    runwayWG->WrapCell[0][runwayWG->RowCount-1]->Text = "better just make sure it scrolls as well, so here are some short ones";
    runwayWG->RowCount ++ ;
    runwayWG->WrapCell[0][runwayWG->RowCount-1]->Text = "a blank" ;

    commonWG->WrapCell[0][0]->Text = "commonWG" ;

    fixWG->WrapCell[0][0]->Text = "fixWG";

}
//---------------------------------------------------------------------------

void __fastcall TBaseSidStarMapr::saveBTNClick(TObject *Sender)
{
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TBaseSidStarMapr::cancelBTNClick(TObject *Sender)
{
    ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TBaseSidStarMapr::WMGetMinMaxInfo(TWMGetMinMaxInfo &Msg)
{
    Msg.MinMaxInfo->ptMinTrackSize.x=443; //ptMinTrackSize = min size allowed
    Msg.MinMaxInfo->ptMinTrackSize.y=500; //by dragging with the mouse.

    Msg.MinMaxInfo->ptMaxTrackSize.x=933; //ptMaxTrackSize = max size allowed
    Msg.MinMaxInfo->ptMaxTrackSize.y=752; //by dragging with the mouse
}
//------------------------------------------------------------------------------

void __fastcall TBaseSidStarMapr::Splitter1Moved(TObject *Sender)
{
    runwayWG->Refresh();
    commonWG->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TBaseSidStarMapr::Splitter2Moved(TObject *Sender)
{
    commonWG->Refresh();
    fixWG->Refresh() ;
}
//---------------------------------------------------------------------------

bool TBaseSidStarMapr::Execute()
{
    if(ShowModal() == mrOk)
        return true;
    else
        return false ;
}

void __fastcall TBaseSidStarMapr::Splitter2CanResize(TObject *Sender, int &NewSize, bool &Accept)
{
Edit2->Text = NewSize ;
Edit3->Text = Splitter2->Top ;
Edit1->Text = commonP->Height ;

    if((endRouteP->Top) < (nameInfoP->Height + runwayTransitionGB->Height + startRouteP->Height + Splitter2->MinSize))// + commonRouteP->Height + ))
    {
        startRouteP->Height -- ; //= startRouteP->Height - 1 ;
    }
}
//---------------------------------------------------------------------------



void __fastcall TBaseSidStarMapr::SpeedButton1Click(TObject *Sender)
{
    runwayWG->ClearText();
    runwayWG->RowCount = 1 ;
    runwayWG->Refresh();    
}
//---------------------------------------------------------------------------

