//---------------------------------------------------------------------------
// Copyright (C) 1998 : Micro Nav Limited
//---------------------------------------------------------------------------
// Current Revision $Revision: 1.9 $
//
// Revision Date    $Date: Tue Aug 03 10:43:02 1999 $
//
// Revised By       $Author: IanVaughan $
//---------------------------------------------------------------------------
/*
$Log20: I:\Best\Source\SIDEditorSrc.dqq $
*  
*    
*  
*  Revision 1.9  by: ChrisKnight  Rev date: Tue Aug 03 10:43:02 1999
*    163/CR/112/001
*  
*  Revision 1.8  by: MikeMale  Rev date: Fri Jul 23 13:07:34 1999
*    System manager network fault, plus re-write of network licence
*    checking, code review 163/CR/75/001
*  
*  Revision 1.7  by: ChrisKnight  Rev date: Tue Jul 20 13:27:38 1999
*    163-CR-19-009 First Review
*  
*  Revision 1.6  by: ChrisKnight  Rev date: Tue Jul 20 13:25:12 1999
*    163-CR-009 First Review
*  
*  Revision 1.5  by: ChrisKnight  Rev date: Wed May 19 15:13:30 1999
*    
*  
*  Revision 1.4  by: ChrisKnight  Rev date: Wed May 19 09:02:08 1999
*    
*  
*  Revision 1.3  by: JonEvans  Rev date: Tue May 04 13:13:54 1999
*    Tidied up the forms a little bit
*  
*  Revision 1.2  by: ChrisKnight  Rev date: Fri Apr 30 15:53:50 1999
*    
*  
*  Revision 1.1  by: ChrisKnight  Rev date: Fri Apr 30 12:20:36 1999
*    
*  
*  Revision 1.0  by: ChrisKnight  Rev date: Fri Apr 30 08:50:46 1999
*    Initial revision.
*  
*  $Endlog$
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SIDEditorSrc.h"
#include "DataPrepSrc.h"
#include "MasterDataFormSrc.h"
#include "FixTransitonEditorSrc.h"
#include "RouteElementEditorSrc.h"
#include "RunwayTransitionEditorSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSIDEditSrc *SIDEditSrc;
//---------------------------------------------------------------------------
__fastcall TSIDEditSrc::TSIDEditSrc(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::FormShow(TObject *Sender)
{
    NewBtn->Enabled = true;
    DeleteBtn->Enabled = true;
    FormMainShow();
}
//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::StartPopupMenuPopup(TObject *Sender)
{
    if (SIDEditSrc->ActiveControl == StartMemoListBox || SIDEditSrc->ActiveControl == CommonMemoListBox || SIDEditSrc->ActiveControl == EndMemoListBox)
    {
        if (StartMemoListBox->ItemIndex != -1 || EndMemoListBox->ItemIndex != -1 || CommonMemoListBox->ItemIndex != -1)
        {
            Add->Enabled = true;
            Edit->Enabled = true;
            Delete->Enabled = true;
        }
        else
        {
            Add->Enabled = true;
            Edit->Enabled = false;
            Delete->Enabled = false;
        }
    }
    else
    {
        Add->Enabled = false;
        Edit->Enabled = false;
        Delete->Enabled = false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::FillMemo(TQuery* route_leg_query, TListBox* memo)
{
    //see what the Route_Leg_Type is.
    if (route_leg_query->FieldByName("Route_Leg_Type")->AsInteger == 0)
    {
        //then fix to fix
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = route_leg_query->FieldByName("Fix_One_ID")->AsInteger;
        FixNameQuery->Open();

        FixNameTwoQuery->Close();
        FixNameTwoQuery->ParamByName("CurrentTwoFix")->AsInteger = route_leg_query->FieldByName("Fix_Two_ID")->AsInteger;
        FixNameTwoQuery->Open();

        RouteElementString = FixNameQuery->FieldByName("Fix_Name")->AsString + " To " + FixNameTwoQuery->FieldByName("Fix_Name")->AsString;
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

    if (RouteTerminatorQuery->RecordCount != 0)
    {
        //then add the terminator to the line.
        RouteTerminatorQuery->First();
        String terminator = AddTerminator();

        RouteElementString += " Until " + terminator;

        if (RouteTerminatorQuery->RecordCount > 1)
        {
            RouteTerminatorQuery->Next();
            while (!RouteTerminatorQuery->Eof)
            {
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
            while (!RouteConditionQuery->Eof)
            {
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

    if (Width > 400)
    {
        //then wider than the list box, see if it is longer than the longest.
        if (Width > LongestWidth)
        {
            LongestWidth = Width;
            memo->Width = Width;
        }
    }

    int Height = memo->ItemHeight * memo->Items->Count;

    Height +=5;
    if (Height > 109)
    {
        memo->Height = Height+5;
    }
}

//---------------------------------------------------------------------------
String TSIDEditSrc::AddTerminator()
{
    String this_fix_name;

    String this_terminator = "";
    //Find out which of the four Terminators this one is (Level, Range, Radial or Time)
    int terminator_type = RouteTerminatorQuery->FieldByName("Route_Terminator_Type")->AsInteger;

    if (terminator_type == 0)//Range terminator
    {
        //Add the following format line. Terminate at "Range" "Qualifier" (From or To) "Fix".
        //get the Fix name.
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = RouteTerminatorQuery->FieldByName("Fix_ID")->AsInteger;
        FixNameQuery->Open();

        this_fix_name = FixNameQuery->FieldByName("Fix_Name")->AsString;

        String qualifier;

        if (RouteTerminatorQuery->FieldByName("Qualifier")->AsString.SubString(0,1) == "F")
        qualifier = " From ";
        else
        qualifier = " To ";

        this_terminator = "at " + RouteTerminatorQuery->FieldByName("Range")->AsString + "NM " + qualifier + this_fix_name;
    }

    else if (terminator_type == 1)//Level terminator
    {
        //Add the following format line. Terminate "Qualifier" (at, above, or below) Height or FL.
        this_terminator = "at " + RouteTerminatorQuery->FieldByName("Level_Term")->AsString;
    }

    else if (terminator_type == 2)//Radial terminator
    {
        //Add the following format line. Terminate radial "Radial" in reference to "Fix"
        //get the Fix name.
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = RouteTerminatorQuery->FieldByName("Fix_ID")->AsInteger;
        FixNameQuery->Open();

        this_fix_name = FixNameQuery->FieldByName("Fix_Name")->AsString;

        if (RouteTerminatorQuery->FieldByName("Qualifier")->AsString.SubString(0,1) == "F")
        this_terminator = "at radial " + RouteTerminatorQuery->FieldByName("Radial")->AsString + " From " + this_fix_name;
        else
        this_terminator = "at radial " + RouteTerminatorQuery->FieldByName("Radial")->AsString + " To " + this_fix_name;

    }

    else if (terminator_type == 3)//Time terminator
    this_terminator = "after " + RouteTerminatorQuery->FieldByName("Time")->AsString + " seconds";

    return this_terminator;
}
//---------------------------------------------------------------------------
String TSIDEditSrc::AddCondition()
{
    String this_profile = "";
    //Find out which of the two Profiles this one is (Level, Speed)
    int profile_type = RouteConditionQuery->FieldByName("Route_Condition_Type")->AsInteger;

    if (profile_type == 0)//Level Profile
    {
        String qualifier;

        if (RouteConditionQuery->FieldByName("Level_Condition_Qualifier")->AsString == "-")
        qualifier = "Below";
        else if (RouteConditionQuery->FieldByName("Level_Condition_Qualifier")->AsString == "+")
        qualifier = "Above";
        else
        qualifier = "At";

        if (RouteConditionQuery->FieldByName("Level_Condition")->AsString != "")
        //Add the following format line.
        this_profile = qualifier + " " + RouteConditionQuery->FieldByName("Level_Condition")->AsString;
    }

    else if (profile_type == 1)//Speed Profile
    {
        String qualifier;

        if (RouteConditionQuery->FieldByName("Speed_Qualifier")->AsString == "-")
        qualifier = "Below";
        else if (RouteConditionQuery->FieldByName("Speed_Qualifier")->AsString == "+")
        qualifier = "Above";
        else
        qualifier = "At";

        //Add the following format line. Fly Leg - "Qualifier" (At, above or below) "Type" "Speed"
        this_profile = qualifier + " " + RouteConditionQuery->FieldByName("Speed_Type")->AsString + " " + RouteConditionQuery->FieldByName("Speed_Condition")->AsString;
    }
    return this_profile;
}
//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::FillEndTransitionList()
{
    //Clear all of the list boxes.
    EndComboBox->Items->Clear();
    EndID->Items->Clear();
    FixIDListBox->Items->Clear();

    //Run the StarRouteQuery.
    EndRouteQuery->Close();
    EndRouteQuery->ParamByName("CurrentRouteID")->AsInteger = RouteElementIDEdit->Text.ToIntDef(0);
    EndRouteQuery->Open();

    //Fill the DropDownListBox and record the ID's in the String list.
    while (!EndRouteQuery->Eof)
    {
        FixNameQuery->Close();
        FixNameQuery->ParamByName("CurrentFix")->AsInteger = EndRouteQuery->FieldByName("Fix_ID")->AsInteger;
        FixNameQuery->Open();

        EndComboBox->Items->Add(FixNameQuery->FieldByName("Fix_Name")->AsString);
        EndID->Items->Add(EndRouteQuery->FieldByName("Route_Fix_Leg_ID")->AsString);
        FixIDListBox->Items->Add(EndRouteQuery->FieldByName("Fix_ID")->AsString);

        EndRouteQuery->Next();
    }
}

//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::FillStartTransitionList()
{
    //Clear all of the list boxes.
    StartComboBox->Items->Clear();
    StartID->Items->Clear();
    RunwayIDListBox->Items->Clear();

    //Run the StartRouteQuery.
    StartRouteQuery->Close();
    StartRouteQuery->ParamByName("CurrentRouteID")->AsInteger = RouteElementIDEdit->Text.ToIntDef(0);
    StartRouteQuery->Open();

    //Fill the DropDownListBox and record the ID's in the String list.
    while (!StartRouteQuery->Eof)
    {
        RunwayNameQuery->Close();
        RunwayNameQuery->ParamByName("CurrentRunway")->AsInteger = StartRouteQuery->FieldByName("Runway_ID")->AsInteger;
        RunwayNameQuery->Open();

        StartComboBox->Items->Add(RunwayNameQuery->FieldByName("Airfield_Name")->AsString + " " + RunwayNameQuery->FieldByName("Runway_Name")->AsString);
        StartID->Items->Add(StartRouteQuery->FieldByName("Route_Runway_Leg_ID")->AsString);
        RunwayIDListBox->Items->Add(StartRouteQuery->FieldByName("Runway_ID")->AsString);

        if (StartRouteQuery->FieldByName("Runway_ID")->AsString == AssociatedRunwayIDListBox->Items->Strings[RunwayComboBox->ItemIndex])
        {
            StartComboBox->ItemIndex = StartComboBox->Items->Count -1;
        }

        StartRouteQuery->Next();
    }
}

//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::FillFixMemoList()
{
    //empty the Memo and ID list boxes
    EndIDListBox->Items->Clear();
    EndMemoListBox->Items->Clear();

    FixLegQuery->Close();
    FixLegQuery->ParamByName("CurrentID")->AsInteger = (EndID->Items->Strings[EndComboBox->ItemIndex]).ToIntDef(0);
    FixLegQuery->Open();

    LongestWidth = 0;

    //Fill the Memo and record the ID's in the String list.
    while (!FixLegQuery->Eof)
    {
        if (FixLegQuery->FieldByName("Route_Leg_Type")->AsInteger != 10)
        {
            EndIDListBox->Items->Add(FixLegQuery->FieldByName("Route_Leg_Type_ID")->AsString);
            FillMemo(FixLegQuery, EndMemoListBox);
        }
        FixLegQuery->Next();
    }
}

//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::FillCommonMemoList()
{
    //empty the Memo and ID list boxes
    CommonIDListBox->Items->Clear();
    CommonMemoListBox->Items->Clear();

    CommonLegQuery->Close();
    CommonLegQuery->ParamByName("CurrentID")->AsInteger = CommonRouteQuery->FieldByName("Route_Common_Leg_ID")->AsInteger;
    CommonLegQuery->Open();

    LongestWidth = 0;

    //Fill the Memo and record the ID's in the String list.
    while (!CommonLegQuery->Eof)
    {
        CommonIDListBox->Items->Add(CommonLegQuery->FieldByName("Route_Leg_Type_ID")->AsString);

        FillMemo(CommonLegQuery, CommonMemoListBox);
        CommonLegQuery->Next();
    }
}

//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::FillRunwayMemoList()
{
    //empty the Memo and ID list boxes
    StartIDListBox->Items->Clear();
    StartMemoListBox->Items->Clear();

    RunwayLegQuery->Close();
    RunwayLegQuery->ParamByName("CurrentID")->AsInteger = (StartID->Items->Strings[StartComboBox->ItemIndex]).ToIntDef(0);
    RunwayLegQuery->Open();

    LongestWidth = 0;

    //Fill the Memo and record the ID's in the String list.
    while (!RunwayLegQuery->Eof)
    {
        StartIDListBox->Items->Add(RunwayLegQuery->FieldByName("Route_Leg_Type_ID")->AsString);

        FillMemo(RunwayLegQuery, StartMemoListBox);
        RunwayLegQuery->Next();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::NewEndBtnClick(TObject *Sender)
{
    FixTransitonEditSrc->IsSid = true;
    FixTransitonEditSrc->IsStar = false;

    // EndRouteQuery->Insert();

    // EndRouteQuery->Edit();
    // EndRouteQuery->FieldByName("Route_Element_ID")->AsInteger = RouteElementIDEdit->Text.ToIntDef(0);

    FixTransitonEditSrc->RouteElement_ID = RouteElementIDEdit->Text.ToIntDef(0);
    FixTransitonEditSrc->Fix_Leg_ID = 0;

    FixTransitonEditSrc->ShowModal();

    FillEndTransitionList();

    if (EndComboBox->Items->Count != 0)
    EndComboBox->ItemIndex = (EndComboBox->Items->Count -1);

    FillFixMemoList();
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::DeleteEndBtnClick(TObject *Sender)
{
    if (EndComboBox->Items->Count > 1)
    {
        int CurrentTransFix = EndID->Items->Strings[EndComboBox->ItemIndex].ToIntDef(0);

        EndUpdateSQL->SetParams(ukDelete);
        EndUpdateSQL->Query[ukDelete]->ParamByName("OLD_Route_Fix_Leg_ID")->AsInteger = CurrentTransFix;

        int answer = Application->MessageBox("Are you sure you want to delete the\ncurrently selected Identifying Fix, and route?", "Question", MB_YESNO+MB_ICONQUESTION);
        if(answer == IDYES)
        {
            EndUpdateSQL->ExecSQL(ukDelete);
            FillEndTransitionList();

            if (EndComboBox->Items->Count != 0)
            EndComboBox->ItemIndex = 0;

        }
        FillFixMemoList();
    }
    else
    Application->MessageBox("You can not delete the last\nIdentifying Fix for this SID.", "Warning", MB_OK+MB_ICONEXCLAMATION);
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EditEndBtnClick(TObject *Sender)
{
    FixTransitonEditSrc->IsSid = false;
    FixTransitonEditSrc->IsStar = true;

    int OriginalPos = (EndID->Items->Strings[EndComboBox->ItemIndex]).ToIntDef(0);

    FixTransitonEditSrc->RouteElement_ID = RouteElementIDEdit->Text.ToIntDef(0);

    //Get the Fix_ID from the fix_list.
    FixTransitonEditSrc->Fix_Leg_ID = EndRouteQuery->FieldByName("Route_Fix_Leg_ID")->AsInteger;
    
    // EndRouteQuery->Edit();
    FixTransitonEditSrc->ShowModal();

    FillEndTransitionList();

    if (EndComboBox->Items->Count != 0)
    EndComboBox->ItemIndex = (EndComboBox->Items->Strings[OriginalPos]).ToIntDef(0);

    FillFixMemoList();
}
//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::AddClick(TObject *Sender)
{
    RouteElementEditSrc->IsSid = true;
    RouteElementEditSrc->IsStar = false;
    RouteElementEditSrc->IsMApc = false;

    //Add a new route item
    if (SIDEditSrc->ActiveControl == StartMemoListBox)
    {
        RouteElementEditSrc->RouteLegTypeID = 0;

        RouteElementEditSrc->FixLegID = 0;
        RouteElementEditSrc->CommonLegID = 0;
        RouteElementEditSrc->RunwayLegID = (StartID->Items->Strings[StartComboBox->ItemIndex]).ToIntDef(0);
        RouteElementEditSrc->OrderNumber = StartIDListBox->Items->Count;
        RouteElementEditSrc->RunwaySegment = true;
        RouteElementEditSrc->AirfieldRunwayName = StartComboBox->Items->Strings[StartComboBox->ItemIndex];

        //open up the Route Element Leg Editor.
        RouteElementEditSrc->ShowModal();
    }
    else if (SIDEditSrc->ActiveControl == CommonMemoListBox)
    {
        RouteElementEditSrc->RouteLegTypeID = 0;

        RouteElementEditSrc->FixLegID = 0;
        RouteElementEditSrc->CommonLegID = CommonRouteQuery->FieldByName("Route_Common_Leg_ID")->AsInteger;
        RouteElementEditSrc->RunwayLegID = 0;
        RouteElementEditSrc->OrderNumber = CommonIDListBox->Items->Count;
        RouteElementEditSrc->RunwaySegment = false;

        //open up the Route Element Leg Editor.
        RouteElementEditSrc->ShowModal();
    }
    else if (SIDEditSrc->ActiveControl == EndMemoListBox)
    {
        if (EndComboBox->ItemIndex == -1)
        {
            NewEndBtnClick(NULL);
        }

        if (EndComboBox->ItemIndex != -1)
        {
            RouteElementEditSrc->RouteLegTypeID = 0;

            RouteElementEditSrc->FixLegID =(EndID->Items->Strings[EndComboBox->ItemIndex]).ToIntDef(0);
            RouteElementEditSrc->CommonLegID = 0;
            RouteElementEditSrc->RunwayLegID = 0;
            RouteElementEditSrc->OrderNumber = EndIDListBox->Items->Count+1;
            RouteElementEditSrc->RunwaySegment = false;

            //open up the Route Element Leg Editor.
            RouteElementEditSrc->ShowModal();
        }
    }

    if (SIDEditSrc->ActiveControl == StartMemoListBox)
    {
        //update the contents
        FillRunwayMemoList();
    }
    else if (SIDEditSrc->ActiveControl == CommonMemoListBox)
    {
        //update the contents
        FillCommonMemoList();
    }
    else if (SIDEditSrc->ActiveControl == EndMemoListBox)
    {
        //update the contents
        FillFixMemoList();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EditClick(TObject *Sender)
{
    //edit the existing row.
    //see what edit box you're in, and get the current ID.
    if (StartLB)
    {
        RouteElementEditSrc->RouteLegTypeID = (StartIDListBox->Items->Strings[StartMemoListBox->ItemIndex]).ToIntDef(0);

        RouteElementEditSrc->FixLegID = 0;
        RouteElementEditSrc->CommonLegID = 0;
        RouteElementEditSrc->RunwayLegID = (StartID->Items->Strings[StartComboBox->ItemIndex]).ToIntDef(0);
        RouteElementEditSrc->RunwaySegment = true;
        RouteElementEditSrc->AirfieldRunwayName = StartComboBox->Items->Strings[StartComboBox->ItemIndex];
    }
    else if (CommonLB)
    {
        RouteElementEditSrc->RouteLegTypeID = (CommonIDListBox->Items->Strings[CommonMemoListBox->ItemIndex]).ToIntDef(0);

        RouteElementEditSrc->FixLegID = 0;
        RouteElementEditSrc->CommonLegID = CommonRouteQuery->FieldByName("Route_Common_Leg_ID")->AsInteger;
        RouteElementEditSrc->RunwayLegID = 0;
        RouteElementEditSrc->RunwaySegment = false;
    }
    else if (EndLB)
    {
        RouteElementEditSrc->RouteLegTypeID = (EndIDListBox->Items->Strings[EndMemoListBox->ItemIndex]).ToIntDef(0);

        RouteElementEditSrc->FixLegID = (EndID->Items->Strings[EndComboBox->ItemIndex]).ToIntDef(0);
        RouteElementEditSrc->CommonLegID = 0;
        RouteElementEditSrc->RunwayLegID = 0;
        RouteElementEditSrc->RunwaySegment = false;
    }

    RouteElementEditSrc->IsSid = true;
    RouteElementEditSrc->IsStar = false;
    RouteElementEditSrc->IsMApc = false;

    //open up the Route Element Leg Editor.
    RouteElementEditSrc->ShowModal();

    //Redraw the memo box
    if (SIDEditSrc->ActiveControl == StartMemoListBox)
    {
        //update the contents
        FillRunwayMemoList();
    }
    else if (SIDEditSrc->ActiveControl == CommonMemoListBox)
    {
        //update the contents
        FillCommonMemoList();
    }
    else if (SIDEditSrc->ActiveControl == EndMemoListBox)
    {
        //update the contents
        FillFixMemoList();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::DeleteClick(TObject *Sender)
{
    //Delete the current route item
    //Get the route Item ID, and delete it. You must then  re-ordernumber the others.
    if (StartLB)
    {
        RunwayLegUpdateSQL->SetParams(ukDelete);
        RunwayLegUpdateSQL->Query[ukDelete]->ParamByName("OLD_Route_Leg_Type_ID")->AsInteger = (StartIDListBox->Items->Strings[StartMemoListBox->ItemIndex]).ToIntDef(0);

        //check to make sure that the deletion is correct.
        int answer = Application->MessageBox("Are you sure you want to delete the currently\nselected Runway Leg Item?", "Question", MB_YESNO+MB_ICONQUESTION);
        if(answer == IDYES)
        {
            RunwayLegUpdateSQL->ExecSQL(ukDelete);
            FillRunwayMemoList();
            StartMemoListBoxClick(NULL);
            
            //update the contents
            FillRunwayMemoList();
            StartUpBtn->Enabled = false;
            StartDownBtn->Enabled = false;

            //Rebuild the order numbers for this MemoBox.
            for (int x = 0; x != StartMemoListBox->Items->Count; x++)
            {
                ThisRunwayLegQuery->Close();
                ThisRunwayLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (StartIDListBox->Items->Strings[x]).ToIntDef(0);
                ThisRunwayLegQuery->Open();

                ThisRunwayLegUpdateSQL->SetParams(ukModify);
                ThisRunwayLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = x;
                ThisRunwayLegUpdateSQL->ExecSQL(ukModify);
            }
        }
    }
    else if (CommonLB)
    {

        CommonLegUpdateSQL->SetParams(ukDelete);
        CommonLegUpdateSQL->Query[ukDelete]->ParamByName("OLD_Route_Leg_Type_ID")->AsInteger = (CommonIDListBox->Items->Strings[CommonMemoListBox->ItemIndex]).ToIntDef(0);

        //check to make sure that the deletion is correct.
        int answer = Application->MessageBox("Are you sure you want to delete the currently\nselected Common Leg Item?", "Question", MB_YESNO+MB_ICONQUESTION);
        if(answer == IDYES)
        {
            CommonLegUpdateSQL->ExecSQL(ukDelete);
            FillCommonMemoList();
            CommonMemoListBoxClick(NULL);

            //update the contents
            FillCommonMemoList();
            CommonUpBtn->Enabled = false;
            CommonDownBtn->Enabled = false;

            //Rebuild the order numbers for this MemoBox.
            for (int x = 0; x != CommonIDListBox->Items->Count; x++)
            {
                ThisCommonLegQuery->Close();
                ThisCommonLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (CommonIDListBox->Items->Strings[x]).ToIntDef(0);
                ThisCommonLegQuery->Open();

                ThisCommonLegUpdateSQL->SetParams(ukModify);
                ThisCommonLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = x;
                ThisCommonLegUpdateSQL->ExecSQL(ukModify);
            }
        }

    }
    else if (EndLB)
    {

        FixLegUpdateSQL->SetParams(ukDelete);
        FixLegUpdateSQL->Query[ukDelete]->ParamByName("OLD_Route_Leg_Type_ID")->AsInteger = (EndIDListBox->Items->Strings[EndMemoListBox->ItemIndex]).ToIntDef(0);

        //check to make sure that the deletion is correct.
        int answer = Application->MessageBox("Are you sure you want to delete the currently\nselected Fix Leg Item?", "Question", MB_YESNO+MB_ICONQUESTION);
        if(answer == IDYES)
        {
            FixLegUpdateSQL->ExecSQL(ukDelete);
            FillFixMemoList();
            EndMemoListBoxClick(NULL);

            //update the contents
            FillFixMemoList();
            EndUpBtn->Enabled = false;
            EndDownBtn->Enabled = false;

            //Rebuild the order numbers for this MemoBox.
            for (int x = 0; x != EndMemoListBox->Items->Count; x++)
            {
                ThisFixLegQuery->Close();
                ThisFixLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (EndIDListBox->Items->Strings[x]).ToIntDef(0);
                ThisFixLegQuery->Open();

                ThisFixLegUpdateSQL->SetParams(ukModify);
                ThisFixLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = x;
                ThisFixLegUpdateSQL->ExecSQL(ukModify);
            }
        }

    }

}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::StartMemoListBoxClick(TObject *Sender)
{
    StartLB = true;
    CommonLB = false;
    EndLB = false;

    if (StartMemoListBox->ItemIndex != -1)
    {
        StartUpBtn->Enabled = true;
        StartDownBtn->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::CommonMemoListBoxClick(TObject *Sender)
{
    StartLB = false;
    CommonLB = true;
    EndLB = false;

    if (CommonMemoListBox->ItemIndex != -1)
    {
        CommonUpBtn->Enabled = true;
        CommonDownBtn->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EndMemoListBoxClick(TObject *Sender)
{
    StartLB = false;
    CommonLB = false;
    EndLB = true;

    if (EndMemoListBox->ItemIndex != -1)
    {
        EndUpBtn->Enabled = true;
        EndDownBtn->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EndComboBoxChange(TObject *Sender)
{
    //empty the Memo and ID list boxes
    EndIDListBox->Items->Clear();
    EndMemoListBox->Items->Clear();

    //fill up the Memo boxes and the ID lists.
    int ThisSelection = (EndID->Items->Strings[EndComboBox->ItemIndex]).ToIntDef(0);

    FixLegQuery->Close();
    FixLegQuery->ParamByName("CurrentID")->AsInteger = ThisSelection;
    FixLegQuery->Open();

    LongestWidth = 0;

    //Fill the Memo and record the ID's in the String list.
    while (!FixLegQuery->Eof)
    {
        if (FixLegQuery->FieldByName("Route_Leg_Type")->AsInteger != 10)
        {
            EndIDListBox->Items->Add(FixLegQuery->FieldByName("Route_Leg_Type_ID")->AsString);
            FillMemo(FixLegQuery, EndMemoListBox);
        }
        FixLegQuery->Next();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::StartComboBoxChange(TObject *Sender)
{
    //empty the Memo and ID list boxes
    StartIDListBox->Items->Clear();
    StartMemoListBox->Items->Clear();

    //fill up the Memo boxes and the ID lists.
    int ThisSelection = (StartID->Items->Strings[StartComboBox->ItemIndex]).ToIntDef(0);

    RunwayLegQuery->Close();
    RunwayLegQuery->ParamByName("CurrentID")->AsInteger = ThisSelection;
    RunwayLegQuery->Open();

    LongestWidth = 0;

    //Fill the Memo and record the ID's in the String list.
    while (!RunwayLegQuery->Eof)
    {
        StartIDListBox->Items->Add(RunwayLegQuery->FieldByName("Route_Leg_Type_ID")->AsString);

        FillMemo(RunwayLegQuery, StartMemoListBox);
        RunwayLegQuery->Next();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::RunwayComboBoxChange(TObject *Sender)
{
    //Get the item index and the Runway ID and change the Runway Trans item to the same.
    int ThisSelection = (AssociatedRunwayIDListBox->Items->Strings[RunwayComboBox->ItemIndex]).ToIntDef(0);

    for (int i = 0; i < RunwayIDListBox->Items->Count; i++)
    {
        int TempSelection = (RunwayIDListBox->Items->Strings[i]).ToIntDef(0);

        if (TempSelection == ThisSelection)
        {
            StartComboBox->ItemIndex = i;

            StartComboBoxChange(NULL);

            break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EndMemoListBoxEnter(TObject *Sender)
{
    CommonMemoListBox->ItemIndex = -1;
    StartMemoListBox->ItemIndex = -1;

    CommonUpBtn->Enabled = false;
    CommonDownBtn->Enabled = false;
    StartUpBtn->Enabled = false;
    StartDownBtn->Enabled = false;    
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::CommonMemoListBoxEnter(TObject *Sender)
{
    StartMemoListBox->ItemIndex = -1;
    EndMemoListBox->ItemIndex = -1;

    StartUpBtn->Enabled = false;
    StartDownBtn->Enabled = false;
    EndUpBtn->Enabled = false;
    EndDownBtn->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::StartMemoListBoxEnter(TObject *Sender)
{
    CommonMemoListBox->ItemIndex = -1;
    EndMemoListBox->ItemIndex = -1;

    CommonUpBtn->Enabled = false;
    CommonDownBtn->Enabled = false;
    EndUpBtn->Enabled = false;
    EndDownBtn->Enabled = false;    
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::NewAssociatedRunwayBtnClick(TObject *Sender)
{
    //get the number of items in the list, if there are more after, then one has been added.
    int StartNumber = RunwayComboBox->Items->Count,
    StartItemIndex = RunwayComboBox->ItemIndex;

    //Set up the Int values need to create the join tables.
    RunwayTransitionEditSrc->RouteElement_ID = RouteElementIDEdit->Text.ToIntDef(0);
    RunwayTransitionEditSrc->SID_ID = SID_IDDBEdit->Text.ToIntDef(0);
    RunwayTransitionEditSrc->STAR_ID = 0;
    RunwayTransitionEditSrc->MApc_ID = 0;

    //Open the RunwayTransition
    RunwayTransitionEditSrc->ShowModal();

    //Clear the combo box
    RunwayComboBox->Items->Clear();
    AssociatedRunwayIDListBox->Items->Clear();

    //Fill the Runway name list.
    CurrentSIDRunwayQuery->Close();
    CurrentSIDRunwayQuery->ParamByName("CurrentSID")->AsInteger = SID_IDDBEdit->Text.ToIntDef(0);
    CurrentSIDRunwayQuery->Open();

    while (!CurrentSIDRunwayQuery->Eof)
    {
        //Add the Airfield / runway name to the Drop down list.
        RunwayComboBox->Items->Add(CurrentSIDRunwayQuery->FieldByName("Airfield_Name")->AsString + " " + CurrentSIDRunwayQuery->FieldByName("Runway_Name")->AsString);

        AssociatedRunwayIDListBox->Items->Add(CurrentSIDRunwayQuery->FieldByName("Runway_ID")->AsString);
        CurrentSIDRunwayQuery->Next();
    }

    int EndNumber = RunwayComboBox->Items->Count;

    if (StartNumber != EndNumber)
    {
        //Refresh all of the runway boxes.
        RunwayComboBox->ItemIndex = RunwayComboBox->Items->Count -1;

        FillStartTransitionList();

        StartComboBoxChange(NULL);
    }
    else
    {
        //set the item index back to the StartItemIndex.
        RunwayComboBox->ItemIndex = StartItemIndex;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::DeleteAssociatedRunwayBtnClick(
TObject *Sender)
{
    //if there is only one item in the Runway List box, then it can't be deleted.
    if (RunwayComboBox->Items->Count == 1)
    {
        Application->MessageBox("You can not delete the last Associated Runway for this SID.", "Warning", MB_OK+MB_ICONEXCLAMATION);
    }
    else
    {
        //get the currently selected runway_ID
        int CurrentRunway_ID = (AssociatedRunwayIDListBox->Items->Strings[RunwayComboBox->ItemIndex]).ToIntDef(0);

        //look in the J_Runway_SID table, and the Route_Runway_Leg table for the items to delete.
        RunwaySIDUpdateSQL->SetParams(ukDelete);
        RunwaySIDUpdateSQL->Query[ukDelete]->ParamByName("OLD_SID_ID")->AsInteger = SID_IDDBEdit->Text.ToIntDef(0);
        RunwaySIDUpdateSQL->Query[ukDelete]->ParamByName("OLD_Runway_ID")->AsInteger = CurrentRunway_ID ;

        DeleteRunwayLegUpdateSQL->SetParams(ukDelete);
        DeleteRunwayLegUpdateSQL->Query[ukDelete]->ParamByName("OLD_Route_Element_ID")->AsInteger = RouteElementIDEdit->Text.ToIntDef(0);
        DeleteRunwayLegUpdateSQL->Query[ukDelete]->ParamByName("OLD_Runway_ID")->AsInteger = CurrentRunway_ID ;

        int answer = Application->MessageBox("Are you sure you want to delete the currently selected\nTransition Runway, and associated route?", "Question", MB_YESNO+MB_ICONQUESTION);
        if(answer == IDYES)
        {
            RunwaySIDUpdateSQL->ExecSQL(ukDelete);
            DeleteRunwayLegUpdateSQL->ExecSQL(ukDelete);
            FillStartTransitionList();

            if (StartComboBox->Items->Count != 0)
            StartComboBox->ItemIndex = 0;

            StartComboBoxChange(NULL);

            RunwayComboBox->Items->Clear();

            //Fill the Runway name list.
            CurrentSIDRunwayQuery->Close();
            CurrentSIDRunwayQuery->ParamByName("CurrentSID")->AsInteger = SID_IDDBEdit->Text.ToIntDef(0);
            CurrentSIDRunwayQuery->Open();

            while (!CurrentSIDRunwayQuery->Eof)
            {
                //Add the Airfield / runway name to the Drop down list.
                RunwayComboBox->Items->Add(CurrentSIDRunwayQuery->FieldByName("Airfield_Name")->AsString + " " + CurrentSIDRunwayQuery->FieldByName("Runway_Name")->AsString);

                AssociatedRunwayIDListBox->Items->Add(CurrentSIDRunwayQuery->FieldByName("Runway_ID")->AsString);
                CurrentSIDRunwayQuery->Next();
            }

            if (RunwayComboBox->Items->Count !=0)
            RunwayComboBox->ItemIndex = 0;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::CancelBtnClick(TObject *Sender)
{
    TransactionStarted = false;
    SIDQuery->CancelUpdates();
    MasterDataForm->TheDatabase->Rollback();
    Close();
}
//---------------------------------------------------------------------------

// initial :
// changes : 163/75-23/7/99
void __fastcall TSIDEditSrc::SaveBtnClick(TObject *Sender)
{
    TransactionStarted = false;
    SIDQuery->ApplyUpdates();
    MasterDataForm->TheDatabase->Commit();
    Close();
    MasterDataForm->AirspaceSids->Close();
    MasterDataForm->AirspaceSids->Open();
    MainForm->SetColWidths();
    MasterDataForm->SelectedSids->Close();
    MasterDataForm->SelectedSids->Open();
    MainForm->SetColWidths();
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::StartUpBtnClick(TObject *Sender)
{
    //get the current Route_Type_Leg_ID. If it Order_Number != 0, then Order_Number
    //becomes Order_Number - 1. And the one above in the list must have one added to
    //its' Order_Number.
    if (StartMemoListBox->ItemIndex != 0)
    {
        int OldItemIndex = StartMemoListBox->ItemIndex -1;

        ThisRunwayLegQuery->Close();
        ThisRunwayLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (StartIDListBox->Items->Strings[StartMemoListBox->ItemIndex]).ToIntDef(0);
        ThisRunwayLegQuery->Open();

        ThisRunwayLegUpdateSQL->SetParams(ukModify);
        ThisRunwayLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (StartMemoListBox->ItemIndex -1);
        ThisRunwayLegUpdateSQL->ExecSQL(ukModify);

        ThisRunwayLegQuery->Close();
        ThisRunwayLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (StartIDListBox->Items->Strings[StartMemoListBox->ItemIndex -1]).ToIntDef(0);
        ThisRunwayLegQuery->Open();

        ThisRunwayLegUpdateSQL->SetParams(ukModify);
        ThisRunwayLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (StartMemoListBox->ItemIndex);
        ThisRunwayLegUpdateSQL->ExecSQL(ukModify);

        FillRunwayMemoList();

        StartMemoListBox->ItemIndex = OldItemIndex;

        StartMemoListBox->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::StartDownBtnClick(TObject *Sender)
{
    //get the current Route_Type_Leg_ID. If it Order_Number the Last Item in the List,
    //then Order_Number becomes Order_Number + 1. And the one above in the
    //list must have one added to its' Order_Number.
    if (StartMemoListBox->ItemIndex != (StartMemoListBox->Items->Count -1))
    {
        int OldItemIndex = StartMemoListBox->ItemIndex +1;

        ThisRunwayLegQuery->Close();
        ThisRunwayLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (StartIDListBox->Items->Strings[StartMemoListBox->ItemIndex]).ToIntDef(0);
        ThisRunwayLegQuery->Open();

        ThisRunwayLegUpdateSQL->SetParams(ukModify);
        ThisRunwayLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (StartMemoListBox->ItemIndex +1);
        ThisRunwayLegUpdateSQL->ExecSQL(ukModify);

        ThisRunwayLegQuery->Close();
        ThisRunwayLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (StartIDListBox->Items->Strings[StartMemoListBox->ItemIndex+1]).ToIntDef(0);
        ThisRunwayLegQuery->Open();

        ThisRunwayLegUpdateSQL->SetParams(ukModify);
        ThisRunwayLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (StartMemoListBox->ItemIndex);
        ThisRunwayLegUpdateSQL->ExecSQL(ukModify);

        FillRunwayMemoList();

        StartMemoListBox->ItemIndex = OldItemIndex;

        StartMemoListBox->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::CommonUpBtnClick(TObject *Sender)
{
    //get the current Route_Type_Leg_ID. If it Order_Number != 0, then Order_Number
    //becomes Order_Number - 1. And the one above in the list must have one added to
    //its' Order_Number.
    if (CommonMemoListBox->ItemIndex != 0)
    {
        int OldItemIndex = CommonMemoListBox->ItemIndex -1;

        ThisCommonLegQuery->Close();
        ThisCommonLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (CommonIDListBox->Items->Strings[CommonMemoListBox->ItemIndex]).ToIntDef(0);
        ThisCommonLegQuery->Open();

        ThisCommonLegUpdateSQL->SetParams(ukModify);
        ThisCommonLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (CommonMemoListBox->ItemIndex -1);
        ThisCommonLegUpdateSQL->ExecSQL(ukModify);

        ThisCommonLegQuery->Close();
        ThisCommonLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (CommonIDListBox->Items->Strings[CommonMemoListBox->ItemIndex -1]).ToIntDef(0);
        ThisCommonLegQuery->Open();

        ThisCommonLegUpdateSQL->SetParams(ukModify);
        ThisCommonLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (CommonMemoListBox->ItemIndex);
        ThisCommonLegUpdateSQL->ExecSQL(ukModify);

        FillCommonMemoList();

        CommonMemoListBox->ItemIndex = OldItemIndex;

        CommonMemoListBox->SetFocus();
    }    
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::CommonDownBtnClick(TObject *Sender)
{
    //get the current Route_Type_Leg_ID. If it Order_Number the Last Item in the List,
    //then Order_Number becomes Order_Number + 1. And the one above in the
    //list must have one added to its' Order_Number.
    if (CommonMemoListBox->ItemIndex != (CommonMemoListBox->Items->Count -1))
    {
        int OldItemIndex = CommonMemoListBox->ItemIndex +1;

        ThisCommonLegQuery->Close();
        ThisCommonLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (CommonIDListBox->Items->Strings[CommonMemoListBox->ItemIndex]).ToIntDef(0);
        ThisCommonLegQuery->Open();

        ThisCommonLegUpdateSQL->SetParams(ukModify);
        ThisCommonLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (CommonMemoListBox->ItemIndex +1);
        ThisCommonLegUpdateSQL->ExecSQL(ukModify);

        ThisCommonLegQuery->Close();
        ThisCommonLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (CommonIDListBox->Items->Strings[CommonMemoListBox->ItemIndex+1]).ToIntDef(0);
        ThisCommonLegQuery->Open();

        ThisCommonLegUpdateSQL->SetParams(ukModify);
        ThisCommonLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (CommonMemoListBox->ItemIndex);
        ThisCommonLegUpdateSQL->ExecSQL(ukModify);

        FillCommonMemoList();

        CommonMemoListBox->ItemIndex = OldItemIndex;

        CommonMemoListBox->SetFocus();
    }    
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EndUpBtnClick(TObject *Sender)
{
    //get the current Route_Type_Leg_ID. If it Order_Number != 0, then Order_Number
    //becomes Order_Number - 1. And the one above in the list must have one added to
    //its' Order_Number.
    if (EndMemoListBox->ItemIndex != 0)
    {
        int OldItemIndex = EndMemoListBox->ItemIndex -1;

        ThisFixLegQuery->Close();
        ThisFixLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (EndIDListBox->Items->Strings[EndMemoListBox->ItemIndex]).ToIntDef(0);
        ThisFixLegQuery->Open();

        ThisFixLegUpdateSQL->SetParams(ukModify);
        ThisFixLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (EndMemoListBox->ItemIndex);
        ThisFixLegUpdateSQL->ExecSQL(ukModify);

        ThisFixLegQuery->Close();
        ThisFixLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (EndIDListBox->Items->Strings[EndMemoListBox->ItemIndex -1]).ToIntDef(0);
        ThisFixLegQuery->Open();

        ThisFixLegUpdateSQL->SetParams(ukModify);
        ThisFixLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (EndMemoListBox->ItemIndex+1);
        ThisFixLegUpdateSQL->ExecSQL(ukModify);

        FillFixMemoList();

        EndMemoListBox->ItemIndex = OldItemIndex;

        EndMemoListBox->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EndDownBtnClick(TObject *Sender)
{
    //get the current Route_Type_Leg_ID. If it Order_Number the Last Item in the List,
    //then Order_Number becomes Order_Number + 1. And the one above in the
    //list must have one added to its' Order_Number.
    if (EndMemoListBox->ItemIndex != (EndMemoListBox->Items->Count -1))
    {
        int OldItemIndex = EndMemoListBox->ItemIndex +1;

        ThisFixLegQuery->Close();
        ThisFixLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (EndIDListBox->Items->Strings[EndMemoListBox->ItemIndex]).ToIntDef(0);
        ThisFixLegQuery->Open();

        ThisFixLegUpdateSQL->SetParams(ukModify);
        ThisFixLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (EndMemoListBox->ItemIndex +2);
        ThisFixLegUpdateSQL->ExecSQL(ukModify);

        ThisFixLegQuery->Close();
        ThisFixLegQuery->ParamByName("CurrentRouteLeg")->AsInteger = (EndIDListBox->Items->Strings[EndMemoListBox->ItemIndex+1]).ToIntDef(0);
        ThisFixLegQuery->Open();

        ThisFixLegUpdateSQL->SetParams(ukModify);
        ThisFixLegUpdateSQL->Query[ukModify]->ParamByName("Order_Number")->AsInteger = (EndMemoListBox->ItemIndex+1);
        ThisFixLegUpdateSQL->ExecSQL(ukModify);

        FillFixMemoList();

        EndMemoListBox->ItemIndex = OldItemIndex;

        EndMemoListBox->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::NewBtnClick(TObject *Sender)
{
    NewBtn->Enabled = false;
    DeleteBtn->Enabled = false;
    //Things to be added for a new btn click.
    SIDQuery->Open();
    SIDUpdateSQL->SetParams(ukInsert);
    SIDUpdateSQL->Query[ukInsert]->ParamByName("SID_Name")->AsString = "";
    SIDUpdateSQL->Query[ukInsert]->ParamByName("Min_Alt")->AsString = "";
    SIDUpdateSQL->Query[ukInsert]->ParamByName("Max_Alt")->AsString = "";
    SIDUpdateSQL->ExecSQL(ukInsert);

    //create a route element_ID for it
    NewSIDQuery->Close();
    NewSIDQuery->Open();
    NewSIDQuery->Last();

    RouteElementQuery->Open();
    RouteElementUpdateSQL->SetParams(ukInsert);
    RouteElementUpdateSQL->Query[ukInsert]->ParamByName("SID_ID")->AsInteger = NewSIDQuery->FieldByName("SID_ID")->AsInteger;
    RouteElementUpdateSQL->ExecSQL(ukInsert);

    NewRouteElementQuery->Close();
    NewRouteElementQuery->Open();
    NewRouteElementQuery->Last();

    //Add the common Leg ID
    CommonRouteQuery->Open();
    CommonRouteUpdateSQL->SetParams(ukInsert);
    CommonRouteUpdateSQL->Query[ukInsert]->ParamByName("Route_Element_ID")->AsInteger = NewRouteElementQuery->FieldByName("Route_Element_ID")->AsInteger;
    CommonRouteUpdateSQL->ExecSQL(ukInsert);

    SID_IDDBEdit->Text = NewSIDQuery->FieldByName("SID_ID")->AsString;

    MainForm->CreateNewInstance = false;

    RunwayComboBox->ItemIndex = -1;
    StartComboBox->ItemIndex = -1;
    EndComboBox->ItemIndex = -1;
    StartMemoListBox->Items->Clear();
    CommonMemoListBox->Items->Clear();
    EndMemoListBox->Items->Clear();

    FormMainShow();
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::FormCreate(TObject *Sender)
{
    TransactionStarted = false;    
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::CommonMemoListBoxDblClick(TObject *Sender)
{
    StartLB = false;
    CommonLB = true;
    EndLB = false;

    if (CommonMemoListBox->ItemIndex != -1)
    {
        CommonUpBtn->Enabled = true;
        CommonDownBtn->Enabled = true;

        EditClick(NULL);
    }

}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::StartMemoListBoxDblClick(TObject *Sender)
{
    StartLB = true;
    CommonLB = false;
    EndLB = false;

    if (StartMemoListBox->ItemIndex != -1)
    {
        StartUpBtn->Enabled = true;
        StartDownBtn->Enabled = true;
        
        EditClick(NULL);
    }

}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EndMemoListBoxDblClick(TObject *Sender)
{
    StartLB = false;
    CommonLB = false;
    EndLB = true;

    if (EndMemoListBox->ItemIndex != -1)
    {
        EndUpBtn->Enabled = true;
        EndDownBtn->Enabled = true;

        EditClick(NULL);
    }

}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::DeleteBtnClick(TObject *Sender)
{
    NewBtn->Enabled = false;
    DeleteBtn->Enabled = false;
    //find all of the Route_elements for this SID and delete them, then delete the SID
    CommonLegQuery->First();

    while (!CommonLegQuery->Eof)
    {
        CommonLegQuery->Delete();
    }

    StartRouteQuery->First();

    while (!StartRouteQuery->Eof)
    {
        //run the route_element query to get all route_elements for this runway leg.
        RunwayLegQuery->Close();
        RunwayLegQuery->ParamByName("CurrentID")->AsInteger = StartRouteQuery->FieldByName("Route_Runway_Leg_ID")->AsInteger;
        RunwayLegQuery->Open();
        RunwayLegQuery->First();

        while (!RunwayLegQuery->Eof)
        {
            RunwayLegQuery->Delete();
        }
        StartRouteQuery->Next();
    }

    EndRouteQuery->First();

    while (!EndRouteQuery->Eof)
    {
        //run the route_element query to get all route_elements for this runway leg.
        FixLegQuery->Close();
        FixLegQuery->ParamByName("CurrentID")->AsInteger = EndRouteQuery->FieldByName("Route_Fix_Leg_ID")->AsInteger;
        FixLegQuery->Open();
        FixLegQuery->First();

        while (!FixLegQuery->Eof)
        {
            FixLegQuery->Delete();
        }
        EndRouteQuery->Next();
    }


    SIDQuery->Delete();
    RunwayComboBox->ItemIndex = -1;
    StartComboBox->ItemIndex = -1;
    EndComboBox->ItemIndex = -1;
    StartMemoListBox->Items->Clear();
    CommonMemoListBox->Items->Clear();
    EndMemoListBox->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::FormClose(TObject *Sender,
TCloseAction &Action)
{
    //close all queries
    SIDQuery->Close();
    RouteElementQuery->Close();
    CurrentSIDRunwayQuery->Close();
    NewSIDQuery->Close();
    NewRouteElementQuery->Close();
    HoldNameQuery->Close();
    RunwaySidQuery->Close();
    DeleteRunwayLegQuery->Close();
    StartRouteQuery->Close();
    RunwayNameQuery->Close();
    RunwayLegQuery->Close();
    ThisRunwayLegQuery->Close();
    CommonRouteQuery->Close();
    CommonLegQuery->Close();
    ThisCommonLegQuery->Close();
    FixLegQuery->Close();
    ThisFixLegQuery->Close();
    EndRouteQuery->Close();
    FixNameQuery->Close();
    FixNameTwoQuery->Close();

    RunwayComboBox->ItemIndex = -1;
    StartComboBox->ItemIndex = -1;
    EndComboBox->ItemIndex = -1;
    StartMemoListBox->Items->Clear();
    CommonMemoListBox->Items->Clear();
    EndMemoListBox->Items->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::FormMainShow()
{
    //Set up the Form
    StartMemoListBox->Height = 109;
    StartMemoListBox->Width = 416;
    CommonMemoListBox->Height = 109;
    CommonMemoListBox->Width = 416;
    EndMemoListBox->Height = 109;
    EndMemoListBox->Width = 416;

    if (!TransactionStarted)
    {
        //START TRANSACTION
        MasterDataForm->TheDatabase->StartTransaction();
        TransactionStarted = true;

        //set the data source to the correct query.
        SIDDataSource->DataSet = SIDQueryName;
    }

    if (!MainForm->CreateNewInstance)
    {
        //bool to say if the Start, common or end list box is active.
        StartLB = false;
        CommonLB = false;
        EndLB = false;

        //Clear the combo box
        RunwayComboBox->Items->Clear();
        AssociatedRunwayIDListBox->Items->Clear();

        //Fill the Runway name list.
        CurrentSIDRunwayQuery->Close();
        CurrentSIDRunwayQuery->ParamByName("CurrentSID")->AsInteger = SID_IDDBEdit->Text.ToIntDef(0);
        CurrentSIDRunwayQuery->Open();

        while (!CurrentSIDRunwayQuery->Eof)
        {
            //Add the Airfield / runway name to the Drop down list.
            RunwayComboBox->Items->Add(CurrentSIDRunwayQuery->FieldByName("Airfield_Name")->AsString + " " + CurrentSIDRunwayQuery->FieldByName("Runway_Name")->AsString);

            AssociatedRunwayIDListBox->Items->Add(CurrentSIDRunwayQuery->FieldByName("Runway_ID")->AsString);
            CurrentSIDRunwayQuery->Next();
        }

        if (RunwayComboBox->Items->Count !=0)
        RunwayComboBox->ItemIndex = 0;

        SIDEditSrc->ClientHeight = 609;
        SIDEditSrc->Width = 473;

        SIDQuery->Close();
        SIDQuery->ParamByName("CurrentSID")->AsInteger = SID_IDDBEdit->Text.ToIntDef(0);
        SIDQuery->Open();

        RouteElementQuery->Close();
        RouteElementQuery->ParamByName("CurrentSID")->AsInteger = SID_IDDBEdit->Text.ToIntDef(0);
        RouteElementQuery->Open();

        RouteElementIDEdit->Text = RouteElementQuery->FieldByName("Route_Element_ID")->AsString;

        //fill up the transion lists, and set them to the first value (if any)
        FillStartTransitionList();

        if (StartComboBox->Items->Count != 0)
        {
            StartComboBox->ItemIndex = 0;
            StartRouteQuery->First();
            FillRunwayMemoList();
        }

        FillEndTransitionList();
        if (EndComboBox->Items->Count != 0)
        {
            EndComboBox->ItemIndex = 0;
            EndRouteQuery->First();
            FillFixMemoList();
        }

        //Run the EndRouteQuery.
        CommonRouteQuery->Close();
        CommonRouteQuery->ParamByName("CurrentRouteID")->AsInteger = RouteElementIDEdit->Text.ToIntDef(0);
        CommonRouteQuery->Open();

        //fill up the Memo boxes and the ID lists.
        FillCommonMemoList();

    }
    else
    {
        NewBtnClick(NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TSIDEditSrc::StartMemoListBoxMouseMove(TObject *Sender,
TShiftState Shift, int X, int Y)
{
    SIDEditSrc->ActiveControl = StartMemoListBox;
    CommonMemoListBox->ItemIndex = -1;
    EndMemoListBox->ItemIndex = -1;
    StartLB = true;
    CommonLB = false;
    EndLB = false;
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::CommonMemoListBoxMouseMove(TObject *Sender,
TShiftState Shift, int X, int Y)
{
    SIDEditSrc->ActiveControl = CommonMemoListBox;
    StartMemoListBox->ItemIndex = -1;
    EndMemoListBox->ItemIndex = -1;
    StartLB = false;
    CommonLB = true;
    EndLB = false;
}
//---------------------------------------------------------------------------

void __fastcall TSIDEditSrc::EndMemoListBoxMouseMove(TObject *Sender,
TShiftState Shift, int X, int Y)
{
    SIDEditSrc->ActiveControl = EndMemoListBox;
    CommonMemoListBox->ItemIndex = -1;
    StartMemoListBox->ItemIndex = -1;
    StartLB = false;
    CommonLB = false;
    EndLB = true;
}
//---------------------------------------------------------------------------


