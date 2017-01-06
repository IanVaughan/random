//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Sid.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall Sid::Sid(TComponent* Owner) : TBaseSidStarMapr(Owner)
{
}

bool Sid::Execute()
{
    //star pattern =  runway trans - runway route - common route - fix route - fix trans .
    Caption = "Sid" ;

    runwayTransitionGB->Align = alTop ;

    endRouteP->Show() ;
    endRouteP->Align = alBottom ;

    fixTransitionGB->Show();
    fixTransitionGB->Align = alBottom ;

    Splitter2->Top = 257 ; //mapc hides splitter, so put it back
    Splitter2->Enabled = true ;
    Splitter2->Visible = true ;

    //setup the start and end routes
    fixRouteP->Parent = endRouteP ;
    runwayRouteP->Parent = startRouteP;

    //now the form is set up, show it
    return TBaseSidStarMapr::Execute();
}








