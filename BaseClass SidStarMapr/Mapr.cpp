//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Mapr.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall Mapr::Mapr(TComponent* Owner) : TBaseSidStarMapr(Owner)
{
}

bool Mapr::Execute()
{
    Caption = "Missed Approach" ;
    //mapr pattern = runway trans - runway route - common route .

    runwayTransitionGB->Align = alTop ;
    runwayTransitionGB->Top = 0 ;

    fixTransitionGB->Hide();
    fixTransitionGB->Align = alNone ;

    //hide the end route
    endRouteP->Hide() ;
    endRouteP->Align = alNone ;

    Splitter2->Enabled = false ;
    Splitter2->Visible = false ;

    //setup the start and end routes
    runwayRouteP->Parent = startRouteP;

    //now the form is set up, show it
    return TBaseSidStarMapr::Execute();
}


