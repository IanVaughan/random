//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SIDsrc.h"
#include "DMsrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSIDform *SIDform;
//---------------------------------------------------------------------------
__fastcall TSIDform::TSIDform(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*
//method copied from SIDEditorSrc.cpp
void FillMemo(TQuery* route_leg_query, TListBox* memo)
{
    //see what the Route_Leg_Type is.
    if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 0) {
        //then fix to fix
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = route_leg_query->FieldByName("Fix_One_ID")->AsInteger;
        FixNameQuery->Open();

        FixNameTwoQuery->Close();
        FixNameTwoQuery->ParamByName("CurrentTwoFix")->AsInteger = route_leg_query->FieldByName("Fix_Two_ID")->AsInteger;
        FixNameTwoQuery->Open();

        RouteElementString = FixNameQuery->FieldByName("Fix_Name")->AsString + " To " + FixNameTwoQuery->FieldByName("Fix_Name")->AsString;
        
        RouteElementString = routeLegTypeT->FieldByName("Fix_Name")->AsString + " To " + FixNameTwoQuery->FieldByName("Fix_Name")->AsString;
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 1)
    {
        //then direct to fix
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = route_leg_query->FieldByName("Fix_One_ID")->AsInteger;
        FixNameQuery->Open();

        RouteElementString = "Direct to " + FixNameQuery->FieldByName("Fix_Name")->AsString;
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 2)
    {
        //then Track/radial to Fix
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = route_leg_query->FieldByName("Fix_One_ID")->AsInteger;
        FixNameQuery->Open();

        if (route_leg_query->FieldByName("Track")->AsString != "")
            RouteElementString = "Fly Track " + route_leg_query->FieldByName("Track")->AsString + " to " + FixNameQuery->FieldByName("Fix_Name")->AsString;
        else
            RouteElementString = "Fly Radial " + route_leg_query->FieldByName("Radial")->AsString + " to " + FixNameQuery->FieldByName("Fix_Name")->AsString;
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 3)
    {
        //then Track/Radial/Heading From Fix
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = route_leg_query->FieldByName("Fix_One_ID")->AsInteger;
        FixNameQuery->Open();

        if (route_leg_query->FieldByName("Heading")->AsString != "")
            RouteElementString = "Fly Heading " + route_leg_query->FieldByName("Heading")->AsString + " from " + FixNameQuery->FieldByName("Fix_Name")->AsString;
        else if (route_leg_query->FieldByName("Track")->AsString != "")
            RouteElementString = "Fly Track " + route_leg_query->FieldByName("Track")->AsString + " from " + FixNameQuery->FieldByName("Fix_Name")->AsString;
        else
            RouteElementString = "Fly Radial " + route_leg_query->FieldByName("Radial")->AsString + " from " + FixNameQuery->FieldByName("Fix_Name")->AsString;
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 4)
    {
        //then Fly Track/Heading
        if (route_leg_query->FieldByName("Heading")->AsString != "")
            RouteElementString = "Fly Heading " + route_leg_query->FieldByName("Heading")->AsString;
        else if (route_leg_query->FieldByName("Track")->AsString != "")
            RouteElementString = "Fly Track " + route_leg_query->FieldByName("Track")->AsString;
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 5)
    {
        //then Course to Intercept
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = route_leg_query->FieldByName("Fix_One_ID")->AsInteger;
        FixNameQuery->Open();

        if (route_leg_query->FieldByName("Heading")->AsString != "")
            RouteElementString = "Fly Heading " + route_leg_query->FieldByName("Heading")->AsString;
        else if (route_leg_query->FieldByName("Track")->AsString != "")
            RouteElementString = "Fly Track " + route_leg_query->FieldByName("Track")->AsString;

        String fix_qualifier;

        if (route_leg_query->FieldByName("Fix_Qualifier")->AsString == "T")
            fix_qualifier = " To ";
        else
            fix_qualifier = " From ";

        RouteElementString += " to intercept radial " + route_leg_query->FieldByName("Radial")->AsString + fix_qualifier + FixNameQuery->FieldByName("Fix_Name")->AsString;
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 6)
    {
        //then Hold at
        HoldNameQuery->Close();
        HoldNameQuery->ParamByName("CurrentHold")->AsInteger = route_leg_query->FieldByName("Hold_ID")->AsInteger;
        HoldNameQuery->Open();

        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = HoldNameQuery->FieldByName("Fix_ID")->AsInteger;
        FixNameQuery->Open();

        RouteElementString = "Hold at " + FixNameQuery->FieldByName("Fix_Name")->AsString;
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 7)
    {
        //then Hold at Fix for n orbits.
        HoldNameQuery->Close();
        HoldNameQuery->ParamByName("CurrentHold")->AsInteger = route_leg_query->FieldByName("Hold_ID")->AsInteger;
        HoldNameQuery->Open();

        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = HoldNameQuery->FieldByName("Fix_ID")->AsInteger;
        FixNameQuery->Open();

        RouteElementString = "Hold at " + FixNameQuery->FieldByName("Fix_Name")->AsString + " for " + route_leg_query->FieldByName("Orbit_Count")->AsString + " orbits";
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 8)
    {
        //then Fly DME Fix
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = route_leg_query->FieldByName("Fix_One_ID")->AsInteger;
        FixNameQuery->Open();

        if (route_leg_query->FieldByName("Direction")->AsString == "0")
            Direction = "Clockwise";
        else
            Direction = "Anti-Clockwise";

        String fix_qualifier;

        if (route_leg_query->FieldByName("Fix_Qualifier")->AsString == "T")
            fix_qualifier = " To ";
        else
            fix_qualifier = " From ";

        RouteElementString = "Fly Arc on " + FixNameQuery->FieldByName("Fix_Name")->AsString + " at a range of " + route_leg_query->FieldByName("Radius_Distance")->AsString + " NM, in the Direction " + Direction + " " + fix_qualifier + " the Boundary Radial " + route_leg_query->FieldByName("Radial")->AsString + " and Terminating Radial "+route_leg_query->FieldByName("Boundary_Radial")->AsString;
    }
    else if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 9)
    {
        //then Fly Track or Heading from Runway.
        if (route_leg_query->FieldByName("Heading")->AsString != "")
            RouteElementString = "Fly Heading " + route_leg_query->FieldByName("Heading")->AsString + " from " + StartComboBox->Items->Strings[StartComboBox->ItemIndex];
        else if (route_leg_query->FieldByName("Track")->AsString != "")
            RouteElementString = "Fly Track " + route_leg_query->FieldByName("Track")->AsString + " from " + StartComboBox->Items->Strings[StartComboBox->ItemIndex];
    }

    //if the cleared level field for this route Element is not null then add the data.
    if (route_leg_query->FieldByName("Cleared_Level")->AsString != "")
        RouteElementString += " with a cleared level of " + route_leg_query->FieldByName("Cleared_Level")->AsString;

    RouteElementString += ".";

    //Add any Route Terminators or Conditions to this line.
    RouteTerminatorQuery->Close();
    RouteTerminatorQuery->ParamByName("CurrentRouteLeg")->AsInteger = route_leg_query->FieldByName("Route_Leg_Type_ID")->AsInteger;
    RouteTerminatorQuery->Open();

    if (RouteTerminatorQuery->RecordCount != 0) {
        //then add the terminator to the line.
        RouteTerminatorQuery->First();
        String terminator = AddTerminator();

        RouteElementString += " Until " + terminator;

        if (RouteTerminatorQuery->RecordCount > 1)
        {
            RouteTerminatorQuery->Next();
            while (!RouteTerminatorQuery->Eof) {
                terminator = AddTerminator();
                RouteElementString += " or " + terminator;
                RouteTerminatorQuery->Next();
            }
        }
    RouteElementString += ".";
    }

    RouteConditionQuery->Close();
    RouteConditionQuery->ParamByName("CurrentRouteLeg")->AsInteger = route_leg_query->FieldByName("Route_Leg_Type_ID")->AsInteger;
    RouteConditionQuery->Open();

    if (RouteConditionQuery->RecordCount != 0)
    {
        //then add the conditions to the line.
        RouteConditionQuery->First();
        String condition = AddCondition();

        RouteElementString += " Fly " + condition;

        if (RouteConditionQuery->RecordCount > 1)
        {
            RouteConditionQuery->Next();
            while (!RouteConditionQuery->Eof) {
                condition = AddCondition();
                RouteElementString += " and " + condition;
                RouteConditionQuery->Next();
            }
        }
    RouteElementString += ".";
    }

    memo->Items->Add(RouteElementString);

    //see if this item is longer than the list box width or the longest so far.
    int Width = memo->Canvas->TextWidth(RouteElementString);

    Width += 15;

    if (Width > 400){
        //then wider than the list box, see if it is longer than the longest.
        if (Width > LongestWidth){
            LongestWidth = Width;
            memo->Width = Width;
        }
    }

    int Height = memo->ItemHeight * memo->Items->Count;

    Height +=5;
    if (Height > 109) {
        memo->Height = Height+5;
    }
}

*/
void __fastcall TSIDform::FormShow(TObject *Sender)
{
//    FillStartTrans();
//    FillEndTrans();
}
//---------------------------------------------------------------------------

void __fastcall TSIDform::cancelBTNClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

void __fastcall TSIDform::saveBTNClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

