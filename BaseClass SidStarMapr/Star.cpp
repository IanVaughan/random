//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Star.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall Star::Star(TComponent* Owner) : TBaseSidStarMapr(Owner)
{
}

bool Star::Execute()
{
    Caption = "Star" ;

    //star pattern = fix trans - fix route - common route -  runway route - runway trans.

    //fix gets hidden by mapr, so show it and re-position it to top
    fixTransitionGB->Show();
    fixTransitionGB->Align = alTop ;
    fixTransitionGB->Top = 0 ;

    //end route gets hidden by mapr, so show, and set to bottom
    endRouteP->Show() ;
    endRouteP->Align = alBottom ;

    //runways always shown, just re-position it to bottom
    runwayTransitionGB->Align =  alBottom;
    runwayTransitionGB->Top = mainCenter->Height ;

    //set splitter, it gets forced to the bottom if the last show was a mapr
    Splitter2->Top = 257 ;
    Splitter2->Enabled = true ;
    Splitter2->Visible - true ;

    //setup the start and end routes
    fixRouteP->Parent = startRouteP;
    runwayRouteP->Parent = endRouteP;

    //now the form is set up, show it
    return TBaseSidStarMapr::Execute();
}


