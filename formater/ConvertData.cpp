//---------------------------------------------------------------------------
// Copyright (C) 1998 : Micro Nav Limited
//---------------------------------------------------------------------------
// Current Revision $Revision: 1.40 $
//
// Revision Date    $Date: Thu Sep 09 15:47:40 1999 $
//
// Revised By       $Author: KevinCrump $
//---------------------------------------------------------------------------
/*
$Log20: I:\Best\Source\ConvertData.dqq $
*  
*    
*  
*  Revision 1.40  by: ChrisKnight  Rev date: Thu Sep 09 15:49:32 1999
*    163-CR-241-001
*  
*  Revision 1.39  by: ChrisKnight  Rev date: Fri Jan 29 10:20:46 1999
*    Change the order of the AC_Perf data
*  
*  Revision 1.38  by: ChrisKnight  Rev date: Fri Jan 29 09:51:32 1999
*    Move all of the speed vairables to the AC_Level.
*  
*  Revision 1.37  by: ChrisKnight  Rev date: Thu Jan 28 16:33:34 1999
*    Remove RV data from weather, and changes to Airways.
*  
*  Revision 1.36  by: ChrisKnight  Rev date: Fri Jan 15 12:39:04 1999
*    Add emergencies data
*  
*  Revision 1.35  by: ChrisKnight  Rev date: Mon Jan 11 14:26:30 1999
*    
*  
*  Revision 1.34  by: ChrisKnight  Rev date: Thu Dec 24 12:57:06 1998
*    
*  
*  Revision 1.33  by: ChrisKnight  Rev date: Wed Dec 23 12:11:24 1998
*    
*  
*  Revision 1.32  by: ChrisKnight  Rev date: Mon Dec 21 12:25:24 1998
*    
*  
*  Revision 1.31  by: ChrisKnight  Rev date: Mon Dec 21 09:24:24 1998
*    Correction to EHHO destination Runways
*  
*  Revision 1.30  by: ChrisKnight  Rev date: Thu Dec 17 12:59:26 1998
*    Addition of the Max ILS in Exercise data.
*  
*  Revision 1.29  by: ChrisKnight  Rev date: Wed Dec 16 09:15:20 1998
*    Visibility corrections.
*  
*  Revision 1.28  by: ChrisKnight  Rev date: Mon Dec 14 16:44:46 1998
*    Add the Master-Sim Sector data.
*  
*  Revision 1.27  by: ChrisKnight  Rev date: Mon Dec 14 10:29:28 1998
*    Add bits to allow Exercise FP to be sorted by callsign name.
*  
*  Revision 1.26  by: ChrisKnight  Rev date: Fri Dec 04 12:28:14 1998
*    Multi sector support added
*  
*  Revision 1.25  by: ChrisKnight  Rev date: Thu Dec 03 13:49:34 1998
*    
*  
*  Revision 1.24  by: ChrisKnight  Rev date: Wed Dec 02 11:19:24 1998
*    
*  
*  Revision 1.23  by: ChrisKnight  Rev date: Tue Dec 01 12:24:16 1998
*    
*  
*  Revision 1.22  by: ChrisKnight  Rev date: Fri Nov 27 15:11:26 1998
*    Change Field name for Critical Mach.
*  
*  Revision 1.21  by: ChrisKnight  Rev date: Fri Nov 27 14:09:48 1998
*    Converters added for the Mach fields in the AC Perf data. And the
*    Airspace field now inc. TransAlt  and Mach AppLev.
*  
*  $Endlog$
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <fstream.h>
#include "ConvertData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
/*
Things to note about this converter -
-Visibility is only set up to extract distances in Km at present.


*/
//Main Program for converting Airspace.
void ConvertAirspace (String Buffer);

//Main Program for converting Exercise.
void ConvertExercise (String Buffer);

//Conversion function to get the Lat Long lay out correct.
void GetLatLong(String Buffer);

//Function to convert the Mask Data to On/Off to Y/N in exercise data.
void ConvertMaskData (String MaskData);

//---------------------------------------------------------------------------
//Function to Sort out the Route Data in all Sids, Stars, and Maps.
void ConvertRouteElement (String Buffer, String RunwayID);

//Sub-Function to Route data.
void ConvertIdentifyingFix (String Buffer);

//Sub-Function to Route data.
void ConvertFlyDirectTo (String Buffer);

//Sub-Function to Route data.
void ConvertHoldAt (String Buffer);

//Sub-Function to Route data.
void ConvertFlyFrom (String Buffer, String RunwayID);

//Sub-Function to Route data.
void ConvertTrack (String Buffer);

//Sub-Function to Route data.
void ConvertHeading (String Buffer);

//Sub-Function to Route data.
void ConvertFlyDirectFrom (String Buffer, String RunwayID);

//Sub-Function to Route data.
void ConvertHeightTerminator (String Buffer);

//Sub-Function to Route data.
void ConvertDistanceTerminator (String Buffer, String FixName, String ToOrFrom);

//Sub-Function to Route data.
void ConvertRadialTerminator (String Buffer, String ToOrFrom, String FixName);

//Function to see if the cureent Airport name is valid
void ConvertAirportName (String Buffer);


TConvertDataForm *ConvertDataForm;
char buf[256];
String  Buffer,
TempBuffer,
OpenFileName,
ConvertedMaskData;

String  Latitude,
Longitude,
RouteElementData,
FixName;

//---------------------------------------------------------------------------
__fastcall TConvertDataForm::TConvertDataForm(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TConvertDataForm::ExtractBtnClick(TObject *Sender)
{
    //Begin Main Program.
    fstream input;


    //Opens up the data file.
    input.open(OpenFileName.c_str());
    while (!input.eof())
    {
        //Gets and trims a line of data.
        input.getline(buf, sizeof(buf));
        Buffer = buf;
        Buffer = Buffer.Trim();
        //If the line contains 'AIRSPACE DATA' then the file should be converted by
        //the ConvertAirspace function.
        if (Buffer.SubString(0,13) == "AIRSPACE DATA")
        {
            input.close();
            ConvertAirspace(Buffer);

            //Close the progress section of the form
            ConvertDataForm->CurrentTextLabel->Visible = false;
            ConvertDataForm->Edit1->Visible = false;
            ConvertDataForm->Height = 160;
        }
        //If the line contains 'EXERCISE DATA' then the file should be converted by
        //the ConvertExercise function.
        if (Buffer.SubString(0,13) == "EXERCISE DATA")
        {
            input.close();
            ConvertExercise(Buffer);

            //Close the progress section of the form
            ConvertDataForm->CurrentTextLabel->Visible = false;
            ConvertDataForm->Edit1->Visible = false;
            ConvertDataForm->Height = 160;
        }
    }//End while.


    //If the Label 'Finished' isn't shown, then the data file selected is null,
    //therefore close the input file, and show the message 'Null Data'.
    if (ConvertDataForm->Label->Visible != true)
    {
        input.close();
        ConvertDataForm->NullLabel->Visible = true;
    }

}//End of Conversion Program.


//---------------------------------------------------------------------------
void __fastcall TConvertDataForm::OpenFileBtnClick(TObject *Sender)
{
    //If the user is converting several data files, this will reset the messages
    //each time they use the open dialog box.
    ConvertDataForm->NullLabel->Visible = false;
    ConvertDataForm->Label->Visible = false;
    OpenDialog->Execute();
    OpenFileName = OpenDialog->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TConvertDataForm::CancelBtnClick(TObject *Sender)
{
    //If the user opens the wrong file the cancel button will allow them to open
    //another file.
    OpenDialog->Execute();
    OpenFileName = OpenDialog->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TConvertDataForm::ExitBtnClick(TObject *Sender)
{
    //Close buttom to close the conversion program.
    ConvertDataForm->Close();     
}
//---------------------------------------------------------------------------

void __fastcall TConvertDataForm::OpenDialogCanClose(TObject *Sender,
bool &CanClose)
{
    //Allows the conversion button to be enabled once a valid file has been sellected
    if (OpenDialog->FileName != "")
    ConvertDataForm->ExtractBtn->Enabled = true;
}

/*---------------------------------------------------------------------------
This section of code will convert a text print out of several exercise data
files. The output will be created as several individual files, each of which
will be named 'Exercise Name'.dax.
//--------------------------------------------------------------------------*/

void ConvertExercise (String Buffer)
{
    String  ConflictAlert,  //holds the alert radius (Trim off the Nm).
    ExStartTime,    //holds the start time of each exercise.
    ExerciseName,   //holds the exercise name that will be used to name the output file.
    LatLong,        //holds any lat/long.
    MaskData,       //holds the data for the screeen layers (Converts On/Off to Y/N)
    MasterSimData,  //holds the data for the master sim.(Sector)
    MaxILSCloseAng, //holds the angle of the ILS closure angle.
    PrimaryRadar,   //holds the name of the primary radar
    RangeSelect,    //holds the default value for the radar range (Trim off the nMiles).
    RangeData,      //holds the radar range data .
    SetupSelect,    //holds the Display setup number to be used (Trim off 'SETUP '#).
    SectorData,     //holds all of the sector data for outputting at the end of each exercise.
    SectorName,     //holds the sector name.
    SectorFreq,     //holds the sector freqency (Trim off the MHz).
    SecondRadar,    //holds the name of the secondary radar
    SectorUppAltFlt,
    SectorLowAltFlt;

    String  FPStartTime,    //All of the variables that begin with FP hold all of
    FPFreqency,     //the flight plan data, and are intuitively named.
    FPCallsign,
    FPACType,
    FPSSRFit,
    FPRouteCode,
    FPAlloSSR,
    FPSelectSSR,
    FPModeCErr,
    FPClearLev,
    FPCurrentLev,
    FPRequestedLev,
    FPATCSpeed,
    FPTargetSpd,
    FPCurrentSpd,
    FPDeptPoint,
    FPDestination,
    FPStPos,
    FPNavState,
    FPRoute,
    FPEnroute,
    FPCurrentHead,
    FPDirOfTurn,
    FPDeptRunway,
    FPSidSelect,
    FPArrRunway,
    FPStarSelect,
    FPStripColour,
    FPAppType;


    int     Sector;


    ofstream output;
    fstream input;

    //open up the exercise file.
    input.open(OpenFileName.c_str());

    //sort out the data until the end of the file is reached.
    while (!input.eof())
    {//open while
        //gets the first line of the file.
        input.getline(buf, sizeof(buf));
        Buffer = buf;
        Buffer = Buffer.Trim();

        //---Starts to get exercise data--------------------------------------------
        if (Buffer == "EXERCISE CONTROL DATA")
        {
            //While the next line isn't 'A new exercise' or it is not the end of
            //file...get exercise data.
            while (Buffer.SubString(0,24) != "1) EXERCISE CONTROL DATA" && !input.eof())
            {
                //Get exercise name so that the output file can be opened.
                if (Buffer.SubString(0,13) == "Exercise Name")
                {
                    //Start of a new exercise, therefore set Sector Data to Null.
                    Sector = 1;
                    SectorData = "";
                    Buffer = Buffer.SubString(14,Buffer.Length()-13);
                    Buffer = Buffer.Trim();
                    ExerciseName = Buffer;
                    //while not end of this section loop.
                    while (Buffer.SubString(0,22) != "Automated Apc Variance")
                    {
                        //Get and store the exercise start time.
                        if (Buffer.SubString(0,10) == "Start Time")
                        {
                            Buffer = Buffer.SubString(11,Buffer.Length()-10);
                            Buffer = Buffer.Trim();
                            ExStartTime = Buffer;
                        }
                        //Get and store the conflict alert radius.
                        if (Buffer.SubString(0,21) == "Conflict Alert Radius")
                        {
                            Buffer = Buffer.SubString(22,Buffer.Length()-21);
                            Buffer = Buffer.Trim();
                            ConflictAlert = Buffer;
                            ConflictAlert = ConflictAlert.SubString(0,ConflictAlert.Length() -3);
                        }
                        if (Buffer.SubString(0,21) == "Max ILS Closure Angle")
                        {
                            Buffer = Buffer.SubString(22,Buffer.Length()-21);
                            Buffer = Buffer.Trim();
                            MaxILSCloseAng = Buffer;
                            MaxILSCloseAng = MaxILSCloseAng.SubString(0,MaxILSCloseAng.Length() -5);
                        }

                        //Gets next line.
                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }//end while....!= Automated Apc Variance.

                    //--------------------------------------------------------------
                    //Add the file extension to the exercise name.
                    ExerciseName += ".dax";
                    //Open Storage file for this exercise.
                    output.open(ExerciseName.c_str());

                    //Show the current file being processed.
                    ConvertDataForm->Height = 190;
                    ConvertDataForm->CurrentTextLabel->Visible = true;
                    ConvertDataForm->CurrentTextLabel->Repaint();
                    ConvertDataForm->Edit1->Text = ExerciseName;
                    ConvertDataForm->Edit1->Visible = true;
                    ConvertDataForm->Edit1->Repaint();


                    //--------------------------------------------------------------
                    //Output Main Exercise Data.
                    output<<"EX "<<ExStartTime.c_str()<<endl;
                    output<<"CA "<<ConflictAlert.c_str()<<endl;
                    output<<"MI "<<MaxILSCloseAng.c_str()<<endl;
                    output<<endl;
                }//end if == exercise name.

                //------------------------------------------------------------------

                // Get all of the Sector Data.
                if (Buffer == "SECTOR DATA")
                {
                    //while != To the begining of the flight plan data....loop
                    while (Buffer.SubString(0,10) != "START TIME" && Buffer.SubString(0,9) != "CALL SIGN" && Buffer.SubString(0, 38) != "Exercise Parameters will be printed in")
                    {
                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();

                        //Get and store the sector name.
                        if (Buffer.SubString(0,12) == "Sector  Name")
                        {
                            Buffer = Buffer.SubString(13,Buffer.Length()-12);
                            Buffer = Buffer.Trim();
                            SectorName = Buffer;
                            if (Sector == 1)
                            MasterSimData = "SE MASTER-SIM&FR 133.300&";
                            //Get all of the data for the 1st display only.
                            while (Buffer != "DISPLAY 2 SERVICES")
                            {
                                //Get and store the sector frequency.
                                if (Buffer.SubString(0,16) == "Sector Frequency")
                                {
                                    Buffer = Buffer.SubString(17,Buffer.Length()-16);
                                    Buffer = Buffer.Trim();
                                    SectorFreq = Buffer;
                                    SectorFreq = SectorFreq.SubString(0,SectorFreq.Length() -4);
                                    //Add a zero to the freq
                                    SectorFreq += "0";
                                }

                                //The display will use one of three setups, this is specified
                                //as the Setup Selected. The value is given as 'SETUP #'.
                                //Therefore, the 'SETUP ' must be trimmed.
                                if (Buffer.SubString(0,14) == "Setup Selected")
                                {
                                    Buffer = Buffer.SubString(15,Buffer.Length()-14);
                                    Buffer = Buffer.Trim();
                                    SetupSelect = Buffer;
                                    SetupSelect = SetupSelect.SubString(6,SetupSelect.Length()-5);
                                }

                                //Gets and process the range data.
                                if (Buffer.SubString(0,7) == "Range 1")
                                {
                                    RangeData = Buffer.SubString(10,4);
                                    RangeData += Buffer.SubString(36,4);
                                    //Gets second line of data.
                                    input.getline(buf, sizeof(buf));
                                    Buffer = buf;
                                    Buffer = Buffer.Trim();
                                    RangeData += Buffer.SubString(10,4);
                                    RangeData += Buffer.SubString(36,4);
                                    //Gets third line of data.
                                    input.getline(buf, sizeof(buf));
                                    Buffer = buf;
                                    Buffer = Buffer.Trim();
                                    RangeData += Buffer.SubString(10,4);
                                    RangeData += Buffer.SubString(36,4);
                                    //Gets last line of data.
                                    input.getline(buf, sizeof(buf));
                                    Buffer = buf;
                                    Buffer = Buffer.Trim();
                                    RangeData += Buffer.SubString(10,4);
                                    RangeData += Buffer.SubString(36,3);
                                }

                                if (Buffer.SubString(0,21) == "Upper Altitude Filter")
                                {
                                    Buffer = Buffer.SubString(22,Buffer.Length()-21);
                                    Buffer = Buffer.Trim();
                                    SectorUppAltFlt = Buffer;
                                    SectorUppAltFlt = SectorUppAltFlt.SubString(0,SectorUppAltFlt.Length()-3);
                                }

                                if (Buffer.SubString(0,21) == "Lower Altitude Filter")
                                {
                                    Buffer = Buffer.SubString(22,Buffer.Length()-21);
                                    Buffer = Buffer.Trim();
                                    SectorLowAltFlt = Buffer;
                                    SectorLowAltFlt = SectorLowAltFlt.SubString(0,SectorLowAltFlt.Length()-3);
                                }

                                //Using the setup selected number from above, only the correct
                                //setup data is extracted. EG. Only the data below SETUP#, where
                                //# = SetupSelected (Number).
                                if (Buffer.SubString(0,5) == "SETUP" && Buffer.SubString(8,1) == SetupSelect)
                                {
                                    //while not the end of the setup data....loop
                                    while (Buffer.SubString(0,24) != "Permanent Cursor Display")
                                    {
                                        //Get all the data that is required.
                                        if (Buffer.SubString(0,13) == "Primary Radar")
                                        {
                                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                                            Buffer = Buffer.Trim();
                                            PrimaryRadar = Buffer;
                                        }
                                        if (Buffer.SubString(0,15) == "Secondary Radar")
                                        {
                                            Buffer = Buffer.SubString(16,Buffer.Length()-15);
                                            Buffer = Buffer.Trim();
                                            SecondRadar = Buffer;
                                        }
                                        if (Buffer.SubString(0,14) == "Range Selected")
                                        {
                                            Buffer = Buffer.SubString(15,Buffer.Length()-14);
                                            Buffer = Buffer.Trim();
                                            RangeSelect = Buffer;
                                            RangeSelect = RangeSelect.SubString(0,RangeSelect.Length() -7);
                                        }
                                        //Get the Mask data, and convert to Y/N...(using the ConvertMaskData)
                                        if (Buffer.SubString(0,11) == "Screen Mask")
                                        {
                                            input.getline(buf, sizeof(buf));
                                            Buffer = buf;
                                            Buffer = Buffer.Trim();
                                            
                                            MaskData = (Buffer.SubString(10,3));
                                            MaskData += (Buffer.SubString(27,3));
                                            MaskData += (Buffer.SubString(44,3));
                                            //Gets second line of data.
                                            input.getline(buf, sizeof(buf));
                                            Buffer = buf;
                                            Buffer = Buffer.Trim();
                                            MaskData += (Buffer.SubString(10,3));
                                            MaskData += (Buffer.SubString(27,3));
                                            MaskData += (Buffer.SubString(44,3));
                                            //Gets third line of data.
                                            input.getline(buf, sizeof(buf));
                                            Buffer = buf;
                                            Buffer = Buffer.Trim();
                                            MaskData += (Buffer.SubString(10,3));
                                            MaskData += (Buffer.SubString(27,3));
                                            MaskData += (Buffer.SubString(44,3));
                                            //Gets last line of data.
                                            input.getline(buf, sizeof(buf));
                                            Buffer = buf;
                                            Buffer = Buffer.Trim();
                                            MaskData += (Buffer.SubString(10,3));
                                            MaskData += (Buffer.SubString(27,3));
                                            MaskData += (Buffer.SubString(44,3));

                                            //Send MaskData to the ConvertMaskData function.
                                            ConvertMaskData (MaskData);
                                        }
                                        //All Lat / Longs need to be processed, this is done in
                                        //the function GetLatLong.
                                        if (Buffer.SubString(0,15) == "Centre Latitude")
                                        {
                                            Buffer = Buffer.SubString(17,Buffer.Length()-16);
                                            Buffer = Buffer.Trim();
                                            GetLatLong(Buffer);
                                            LatLong = Latitude;
                                        }
                                        if (Buffer.SubString(0,16) == "Centre Longitude")
                                        {
                                            Buffer = Buffer.SubString(17,Buffer.Length()-16);
                                            Buffer = Buffer.Trim();
                                            GetLatLong(Buffer);
                                            LatLong += " " + Longitude;
                                        }

                                        //Get next line.
                                        input.getline(buf, sizeof(buf));
                                        Buffer = buf;
                                        Buffer = Buffer.Trim();
                                    }//end while != Permanent Cursor Display

                                }//end if == "SETUP" && Buffer.SubString(8,1) == SetupSelect)

                                input.getline(buf, sizeof(buf));
                                Buffer = buf;
                                Buffer = Buffer.Trim();
                            }//end while != Display 2...
                            if (Sector == 1)
                            {
                                MasterSimData += "LL " + LatLong + "&" + "PR " + PrimaryRadar + "&" + "SR "
                                + SecondRadar + "&" + "RL " + RangeData + "&" + "RS " + RangeSelect + "&" + "ML "
                                + ConvertedMaskData + "&" + "UF " + SectorUppAltFlt + "&" + "LF " + SectorLowAltFlt + "&";
                            }
                            SectorData += "SE " + SectorName + "&" + "FR " + SectorFreq + "&" + "LL " + LatLong +
                            "&" + "PR " + PrimaryRadar + "&" + "SR " + SecondRadar + "&" + "RL " + RangeData +
                            "&" + "RS " + RangeSelect + "&" + "ML " + ConvertedMaskData +
                            "&" + "UF " + SectorUppAltFlt + "&" + "LF " + SectorLowAltFlt + "&";

                            Sector++;
                        }//end if...Sector Name.
                        
                    }//end while... != Flight Plan Data in Start Time Order.

                }//end if....Sector data.


                //Get and output all Flight Plan Data.
                if (Buffer.SubString(0,12) == "START TIME :" || Buffer.SubString(0,11) == "CALL SIGN :")
                {
                    //while != Begining of next exercise or End of file....loop
                    while ((Buffer != "Exercise Parameters will be printed in the following order:-") && (!input.eof()))
                    {
                        if (Buffer.SubString(0,10) == "Start Time")
                        {
                            Buffer = Buffer.SubString(11,Buffer.Length()-10);
                            Buffer = Buffer.Trim();
                            FPStartTime = Buffer;
                        }
                        if (Buffer.SubString(0,9) == "Frequency")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            FPFreqency = Buffer;
                        }
                        if (Buffer.SubString(0,10) == "Callsign  ")
                        {
                            Buffer = Buffer.SubString(9,Buffer.Length()-8);
                            Buffer = Buffer.Trim();
                            FPCallsign = Buffer;

                        }
                        if (Buffer.SubString(0,13) == "Aircraft Type")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(3,Buffer.Length()-2);
                            FPACType = Buffer;
                        }
                        if (Buffer.SubString(0,7) == "SSR Fit")
                        {
                            Buffer = Buffer.SubString(8,Buffer.Length()-7);
                            Buffer = Buffer.Trim();
                            if (Buffer.SubString(0,1) == "N")
                            FPSSRFit = "N";
                            else
                            if (Buffer.SubString(6,1) == "C")
                            FPSSRFit = "C";
                            else
                            if (Buffer.SubString(6,1) == "A")
                            FPSSRFit = "A";
                        }
                        if (Buffer.SubString(0,12) == "Routing Code")
                        {
                            Buffer = Buffer.SubString(13,Buffer.Length()-12);
                            Buffer = Buffer.Trim();
                            FPRouteCode = Buffer;
                        }
                        if (Buffer.SubString(0,13) == "Allocated SSR")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            FPAlloSSR = Buffer;
                        }
                        if (Buffer.SubString(0,12) == "Selected SSR")
                        {
                            Buffer = Buffer.SubString(13,Buffer.Length()-12);
                            Buffer = Buffer.Trim();
                            FPSelectSSR = Buffer;
                        }
                        if (Buffer.SubString(0,11) == "ModeC Error")
                        {
                            Buffer = Buffer.SubString(12,Buffer.Length()-11);
                            Buffer = Buffer.Trim();
                            FPModeCErr = Buffer;
                            FPModeCErr = FPModeCErr.SubString(0,FPModeCErr.Length() -3);
                        }
                        if (Buffer.SubString(0,13) == "Cleared Level")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            FPClearLev = Buffer;
                        }
                        if (Buffer.SubString(0,13) == "Current Level")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            FPCurrentLev = Buffer;
                        }
                        if (Buffer.SubString(0,15) == "Requested Level")
                        {
                            Buffer = Buffer.SubString(16,Buffer.Length()-15);
                            Buffer = Buffer.Trim();
                            FPRequestedLev = Buffer;
                        }

                        if (Buffer.SubString(0,17) == "ATC Speed Control")
                        {
                            Buffer = Buffer.SubString(18,Buffer.Length()-17);
                            Buffer = Buffer.Trim();
                            FPATCSpeed = Buffer;
                            if (FPATCSpeed.SubString(0,1) == "A")
                            FPATCSpeed = "Y";
                            else
                            FPATCSpeed = "N";
                        }
                        if (Buffer.SubString(0,12) == "Target Speed")
                        {
                            Buffer = Buffer.SubString(13,Buffer.Length()-12);
                            Buffer = Buffer.Trim();
                            FPTargetSpd = Buffer;
                            FPTargetSpd = FPTargetSpd.SubString(0,FPTargetSpd.Length()-4);
                            FPTargetSpd = FPTargetSpd.SubString(2,FPTargetSpd.Length()-1);
                        }
                        if (Buffer.SubString(0,13) == "Current Speed")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            FPCurrentSpd = Buffer;
                            FPCurrentSpd = FPCurrentSpd.SubString(0,FPCurrentSpd.Length()-4);
                            FPCurrentSpd = FPCurrentSpd.SubString(2,FPCurrentSpd.Length()-1);
                        }
                        if (Buffer.SubString(0,15) == "Departure Point")
                        {
                            Buffer = Buffer.SubString(16,Buffer.Length()-15);
                            Buffer = Buffer.Trim();
                            FPDeptPoint = Buffer;
                            ConvertAirportName (Buffer);
                            FPDeptPoint = TempBuffer;
                        }
                        if (Buffer.SubString(0,11) == "Destination")
                        {
                            Buffer = Buffer.SubString(12,Buffer.Length()-11);
                            Buffer = Buffer.Trim();
                            FPDestination = Buffer;
                            ConvertAirportName (Buffer);
                            FPDestination = TempBuffer;
                        }
                        if (Buffer.SubString(0,14) == "Start Position")
                        {
                            Buffer = Buffer.SubString(15,Buffer.Length()-14);
                            Buffer = Buffer.Trim();
                            FPStPos = Buffer;
                        }
                        if (Buffer.SubString(0,16) == "Navigation State")
                        {
                            Buffer = Buffer.SubString(17,Buffer.Length()-16);
                            Buffer = Buffer.Trim();
                            FPNavState = Buffer;
                        }
                        if (Buffer.SubString(0,5) == "ROUTE")
                        {
                            input.getline(buf, sizeof(buf));
                            Buffer = buf;
                            Buffer = Buffer.Trim();
                            FPRoute = "";
                            while (Buffer.SubString(0,12) != "Enroute Hold")
                            {
                                FPRoute = FPRoute + " "+Buffer;

                                input.getline(buf, sizeof(buf));
                                Buffer = buf;
                                Buffer = Buffer.Trim();
                                //ConvertAirportName (Buffer);
                                //FPRoute = TempBuffer;
                            }

                        }
                        if (Buffer.SubString(0,12) == "Enroute Hold")
                        {
                            Buffer = Buffer.SubString(13,Buffer.Length()-12);
                            Buffer = Buffer.Trim();
                            FPEnroute = Buffer;
                        }
                        if (Buffer.SubString(0,16) == "Departure Runway")
                        {
                            Buffer = Buffer.SubString(17,Buffer.Length()-16);
                            Buffer = Buffer.Trim();
                            FPDeptRunway = Buffer;
                        }
                        if (Buffer.SubString(0,12) == "Sid Selected")
                        {
                            Buffer = Buffer.SubString(13,Buffer.Length()-12);
                            Buffer = Buffer.Trim();
                            FPSidSelect = Buffer;
                        }
                        if (Buffer.SubString(0,14) == "Arrival Runway")
                        {
                            Buffer = Buffer.SubString(15,Buffer.Length()-14);
                            Buffer = Buffer.Trim();
                            FPArrRunway = Buffer;
                        }
                        if (Buffer.SubString(0,13) == "Star Selected")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            FPStarSelect = Buffer;
                        }
                        if (Buffer.SubString(0,13) == "Approach Type")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            FPAppType = Buffer;
                        }
                        if (Buffer.SubString(0,14) == "Target Heading")
                        {
                            Buffer = Buffer.SubString(15,Buffer.Length()-14);
                            Buffer = Buffer.Trim();
                            if (FPNavState.SubString(0,1) == "O")
                            FPNavState = "O";
                            else
                            FPNavState = Buffer;
                        }
                        if (Buffer.SubString(0,15) == "Current Heading")
                        {
                            Buffer = Buffer.SubString(16,Buffer.Length()-15);
                            Buffer = Buffer.Trim();
                            FPCurrentHead = Buffer;
                        }
                        if (Buffer.SubString(0,17) == "Direction of Turn")
                        {
                            Buffer = Buffer.SubString(18,Buffer.Length()-17);
                            Buffer = Buffer.Trim();
                            FPDirOfTurn = Buffer;
                        }
                        if (Buffer.SubString(0,23) == "Electronic Strip Colour")
                        {
                            Buffer = Buffer.SubString(24,Buffer.Length()-23);
                            Buffer = Buffer.Trim();
                            FPStripColour = Buffer;
                        }

                        //if Buffer = the end of a flight plan record, then output the data.
                        if (Buffer.SubString(0,9) == "Endurance")
                        {
                            // Output all data for this Flight Plan.
                            output<<"FP "<<FPCallsign.c_str()<<endl;
                            output<<"TY "<<FPACType.c_str()<<endl;
                            output<<"FR "<<FPFreqency.c_str()<<endl;
                            output<<"SF "<<FPSSRFit.c_str()<<endl;
                            output<<"CO "<<FPRouteCode.c_str()<<endl;
                            if (FPAlloSSR == "")
                            FPAlloSSR = "0000";
                            output<<"SA "<<FPAlloSSR.c_str()<<endl;
                            if (FPSelectSSR == "")
                            FPSelectSSR = "0000";
                            output<<"SS "<<FPSelectSSR.c_str()<<endl;
                            output<<"MC "<<FPModeCErr.c_str()<<endl;
                            output<<"SP "<<FPStPos.c_str()<<endl;
                            output<<"TI "<<FPStartTime.c_str()<<endl;
                            output<<"CL "<<FPCurrentLev.c_str()<<endl;
                            output<<"TL "<<FPClearLev.c_str()<<endl;
                            output<<"CH "<<FPCurrentHead.c_str()<<endl;
                            output<<"NA "<<FPNavState.c_str()<<endl;
                            output<<"TD "<<FPDirOfTurn.c_str()<<endl;
                            output<<"CS "<<FPCurrentSpd.c_str()<<endl;
                            output<<"TS "<<FPTargetSpd.c_str()<<endl;
                            output<<"SC "<<FPATCSpeed.c_str()<<endl;
                            output<<"DP "<<FPDeptPoint.c_str()<<endl;
                            output<<"DN "<<FPDestination.c_str()<<endl;
                            output<<"RO "<<FPRoute.c_str()<<endl;
                            output<<"HO "<<FPEnroute.c_str()<<endl;
                            output<<"RQ "<<FPRequestedLev.c_str()<<endl;

                            if (FPDeptRunway != "Default" && FPDeptRunway != "")
                            {
                                output<<"YA "<<FPDeptRunway.c_str()<<endl;
                                FPDeptRunway = "Default";
                            }
                            if (FPSidSelect != "Default" && FPSidSelect != "")
                            {
                                output<<"YB "<<FPSidSelect.c_str()<<endl;
                                FPSidSelect = "Default";
                            }
                            if (FPArrRunway != "Default" && FPArrRunway != "")
                            {
                                output<<"YC "<<FPArrRunway.c_str()<<endl;
                                FPArrRunway = "Default";
                            }
                            if (FPStarSelect != "Default" && FPStarSelect != "")
                            {
                                output<<"YD "<<FPStarSelect.c_str()<<endl;
                                FPStarSelect = "Default";
                            }
                            if (FPAppType != "Default" && FPAppType != "")
                            {
                                output<<"YE "<<FPAppType.c_str()<<endl;
                                FPAppType = "Default";
                            }
                            output<<"DC "<<FPStripColour.c_str()<<endl;
                            output<<endl;
                        }

                        //get next line.
                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }//end while != Exercise Parameters will be printed.

                }// end if...START TIME

                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                //if the begining of a new exercise or the end of the file has been reached,
                //then output the sector data, and close the output file.
                if (Buffer.SubString(0,24) == "1) EXERCISE CONTROL DATA" || input.eof())
                {

                    String ThisData;
                    while (MasterSimData != NULL)
                    {
                        int i =1;
                        //Read in the bearing reading.
                        while (MasterSimData[i] != '&')
                        {
                            i++;
                        }

                        //Store the reading.
                        ThisData = MasterSimData.SubString(0,i-1);

                        //Output this line of data.
                        output<<ThisData.c_str()<<endl;

                        //Trim off the heading value.
                        MasterSimData = MasterSimData.SubString(i+1 , MasterSimData.Length()-(i));
                        MasterSimData = MasterSimData.Trim();

                        if (MasterSimData.Length() == 0)
                        MasterSimData = NULL;
                    }

                    output<<endl;

                    while (SectorData != NULL)
                    {
                        int i =1;
                        //Read in the bearing reading.
                        while (SectorData[i] != '&')
                        {
                            i++;
                        }

                        //Store the reading.
                        ThisData = SectorData.SubString(0,i-1);

                        //Output this line of data.
                        output<<ThisData.c_str()<<endl;

                        //Trim off the heading value.
                        SectorData = SectorData.SubString(i+1 , SectorData.Length()-(i));
                        SectorData = SectorData.Trim();

                        if (SectorData.Length() == 0)
                        SectorData = NULL;
                    }
                    output<<endl;
                    output.close();
                }
            }//End while ...Exercise Parameters

        }//End if.


    }//end while.

    //Once the end of file marker has been reached, close the file, and show the
    //finish dialog.
    input.close();
    ConvertDataForm->Label->Visible = True;

}//End of procedure.

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

//Converts the MaskData from On/Off to Y/N.
void ConvertMaskData (String MaskData)
{

    String  TempMask,
    Buffer;

    TempMask = "";

    while (MaskData != NULL)
    {
        //gets the first 3 chars.
        Buffer = MaskData.SubString(0,3);
        if (Buffer == "Off")
        TempMask += "N";
        else
        TempMask += "Y";

        //Cut off the first 3 chars.
        MaskData = MaskData.SubString(4,MaskData.Length() -3);
        if (MaskData == "")
        MaskData = NULL;
    }
    //Give ConvertedMaskData the string of Y's and N's.
    ConvertedMaskData = TempMask;
}

//------------------------------------------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*------------------------------------------------------------------------------
This section of code will convert a text print out of an airspace data file. The
output will be created as several individual files, each of which will be named
'Airspace Name'.dat, .dap, .daw. These file types stand for the following, .dat
is the airspace data, .dap is the aircraft performace data for the airspace, and
.daw is the weather data for the airspace.
//----------------------------------------------------------------------------*/

void ConvertAirspace (String Buffer)
{
    String  AirspaceFileName,
    AirportName,
    AirwayName,
    AirwayRoute,
    ApproachName,
    ApproachType,
    Acceleration,
    ACTypeData,
    AirportLL,
    Ceiling,
    Climb,
    Cruise,
    CircuitDirection,
    CriticalMach,
    ClimbMach,
    CruiseMach,
    DefaultApp,
    Descent,
    Deceleration,
    DescentRate,
    ExpediteClb,
    ExpediteDes,
    FileName,
    FixType,
    FixCat,
    FinalAPCTrack,
    FinalAPC,
    GroundCoverRng,
    GlidePathAngle,
    GlideSpeed,
    Holding,
    HeightData,
    HeightNum,
    Intermediate,
    InboundHeading,
    Landing,
    LocaliserMDA,
    MachAppLev,
    MAPName,
    MaxRange,
    MaxSlant,
    MaxVertCover,
    MaxSpeed,
    MaxHoldHeight,
    MaxLowLevSpd,
    MaxLowLev,
    MinHoldHeight,
    MinSlant,
    MinRange,
    MinCruiseLev,
    MinSpeed,
    MinDecisionAlt,
    MinTurnHeight,
    MinArrSep,
    MinDepSep,
    MissedApcName,
    NormalBkAngle,
    OuterMarkerRng,
    PerformanceGrp,
    PartialEngineFailureCruiseSpeed,
    PowerOffDescentRate,
    PartialPowerFailureCeiling,
    RadarName,
    RadarElevation,
    RadarType,
    RadarScanRate,
    ROCNum,
    RunwayID,
    RunwayHeading,
    RunwayLL,
    RunwayElevation,
    SafeAltLev,
    SatAirportName,
    SatRunwayID,
    SIDName,
    STARName,
    SSAltLevel,
    TempLongitude,
    TakeOff,
    Terminal,
    TempHeight,
    TempTypeData,
    TempType,
    TempGroup,
    ThisRoute,
    Type,
    TerminationRange,
    TurnDir,
    TransAlt,
    Wake;


    int     ExpROC,
    ExpDesRate,
    i = 1,
    NextSpace;

    fstream input;
    ofstream output;
    input.open(OpenFileName.c_str());

    //string list to make sure that a missed approach exists for a give approach.
    TStringList* MApc_List = new TStringList;

    // The first while loop will get the following data, Airspace Record, Radar
    // details for the airspace, Fix records, and Airport Details.
    while (Buffer.SubString(0,11) != "AIRWAY NAME")
    {//start main while

        //gets the first line of the file.
        input.getline(buf, sizeof(buf));
        Buffer = buf;
        Buffer = Buffer.Trim();

        if (Buffer == "AIRSPACE  MASTER PAGE")
        //Then begin the get airspace data section.
        {
            while (Buffer.SubString(0,11) != "AIRWAY NAME")
            {
                if (Buffer.SubString(0,13) == "Airspace Name")
                {
                    Buffer = Buffer.SubString(14,Buffer.Length()-13);
                    Buffer = Buffer.Trim();
                    AirspaceFileName = Buffer;
                    FileName = AirspaceFileName + ".dat";
                    output.open(FileName.c_str());

                    //Show the current file being processed.
                    ConvertDataForm->Height = 190;
                    ConvertDataForm->CurrentTextLabel->Visible = true;
                    ConvertDataForm->CurrentTextLabel->Repaint();
                    ConvertDataForm->Edit1->Text = FileName;
                    ConvertDataForm->Edit1->Visible = true;
                    ConvertDataForm->Edit1->Repaint();
                }//End if.

                if (Buffer.SubString(0,9) == "Reference")
                {
                    Buffer = Buffer.SubString(10,Buffer.Length()-9);
                    Buffer = Buffer.Trim();
                    Type = Buffer.SubString(0,3);
                    Buffer = Buffer.SubString(10,Buffer.Length()-9);
                    Buffer = Buffer.Trim();
                    GetLatLong(Buffer);
                }//End if.

                if (Buffer.SubString(0,19) == "Transition Altitude")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();
                    Buffer = Buffer.SubString(0,Buffer.Length()-3);
                    TransAlt = Buffer;
                }//End if.

                if (Buffer.SubString(0,22) == "MACH Application Level")
                {
                    Buffer = Buffer.SubString(23,Buffer.Length()-22);
                    Buffer = Buffer.Trim();
                    Buffer = Buffer.SubString(0,Buffer.Length()-5);
                    Buffer = "F" + Buffer;
                    MachAppLev = Buffer;
                }//End if.

                if (Buffer.SubString(0,21) == "Max Low Level Speed  ")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();
                    Buffer = Buffer.SubString(0,Buffer.Length()-4);
                    MaxLowLevSpd = Buffer;
                }

                if (Buffer.SubString(0,25) == "Max Low Level Speed Level")
                {
                    Buffer = Buffer.SubString(26,Buffer.Length()-25);
                    Buffer = Buffer.Trim();
                    Buffer = Buffer.SubString(0,Buffer.Length()-5);
                    MaxLowLev = Buffer;
                }

                if (Buffer.SubString(0,14) == "RADAR DATA FOR")
                {
                    output<<"AS "<<Latitude.c_str()<<" "<<Longitude.c_str()<<endl;
                    output<<"SC "<<MaxLowLevSpd.c_str()<<endl;
                    output<<"SL "<<MaxLowLev.c_str()<<endl;
                    output<<"TA "<<TransAlt.c_str()<<endl;
                    output<<"SM "<<MachAppLev.c_str()<<endl;
                    output<<endl;
                    
                    while (Buffer.SubString(0,12) != "VDF DATA FOR")
                    {
                        //Get and output all of the Radar Data.
                        if (Buffer.SubString(0,4) == "Name")
                        {
                            Buffer = Buffer.SubString(5,Buffer.Length()-4);
                            Buffer = Buffer.Trim();
                            RadarName = Buffer;
                            output<<"RA "<<RadarName.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,4) == "Lati")
                        {
                            Buffer = Buffer.SubString(32,Buffer.Length()-31);
                            Buffer = Buffer.Trim();
                            GetLatLong(Buffer);
                        }
                        if (Buffer.SubString(0,4) == "Long")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            GetLatLong(Buffer);
                            output<<"LL "<<Latitude.c_str()<<" "<<Longitude.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,4) == "Elev")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(0,Buffer.Length()-3);
                            RadarElevation = Buffer;
                            output<<"EL "<<RadarElevation.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,4) == "Type")
                        {
                            Buffer = Buffer.SubString(5,Buffer.Length()-4);
                            Buffer = Buffer.Trim();
                            RadarType = Buffer;
                            output<<"TY "<<RadarType.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,4) == "Scan")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(0,Buffer.Length()-8);
                            RadarScanRate = Buffer;
                            output<<"UP "<<RadarScanRate.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,4) == "COVE")
                        {
                            Buffer = Buffer.SubString(30,Buffer.Length()-29);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(0,Buffer.Length()-7);
                            MinRange = Buffer;
                            output<<"RM "<<MinRange.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,5) == "Max R")
                        {
                            Buffer = Buffer.SubString(16,Buffer.Length()-15);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(0,Buffer.Length()-7);
                            MaxRange = Buffer;
                            output<<"RX "<<MaxRange.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,4) == "Grou")
                        {
                            Buffer = Buffer.SubString(20,Buffer.Length()-19);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(0,Buffer.Length()-7);
                            GroundCoverRng = Buffer;
                            output<<"GC "<<GroundCoverRng.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,4) == "Mini")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(0,Buffer.Length()-8);
                            MinSlant = Buffer;
                            output<<"MS "<<MinSlant.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,4) == "Maxi")
                        {
                            Buffer = Buffer.SubString(14,Buffer.Length()-13);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(0,Buffer.Length()-8);
                            MaxSlant = Buffer;
                            output<<"XS "<<MaxSlant.c_str()<<endl;
                        }
                        if (Buffer.SubString(0,5) == "Max V")
                        {
                            Buffer = Buffer.SubString(19,Buffer.Length()-18);
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(0,Buffer.Length()-3);
                            MaxVertCover = Buffer;
                            output<<"MV "<<MaxVertCover.c_str()<<endl;
                            output<<endl;
                        }
                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }//end while != VDF DATA FOR
                }//End if RADAR DATA

                if (Buffer.SubString(0,12) == "FIX DATA FOR")
                {
                    while (Buffer.SubString(0,16) != "AIRPORT DATA FOR")
                    {
                        if (Buffer.SubString(0,8) == "FIX NAME")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            FixName = Buffer;
                        }
                        if (Buffer.SubString(0,8) == "Latitude")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            GetLatLong(Buffer);
                        }
                        if (Buffer.SubString(0,9) == "Longitude")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            GetLatLong(Buffer);
                        }
                        if (Buffer.SubString(0,19) == "Navigation Aid Type")
                        {
                            Buffer = Buffer.SubString(20,Buffer.Length()-19);
                            Buffer = Buffer.Trim();
                            FixType = Buffer;
                        }
                        if (Buffer.SubString(0,12) == "Fix Category")
                        {
                            Buffer = Buffer.SubString(13,Buffer.Length()-12);
                            Buffer = Buffer.Trim();
                            FixCat = Buffer;
                            
                            //Output Fix Data
                            output<<"FI "<<FixName.c_str()<<endl;
                            output<<"LL "<<Latitude.c_str()<<" "<<Longitude.c_str()<<endl;
                            output<<"TY "<<FixType.c_str()<<endl;
                            output<<"FX "<<FixCat.c_str()<<endl;
                            output<<endl;
                        }
                        
                        
                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }
                }//end if Fix Data.

                if (Buffer.SubString(0,16) == "AIRPORT DATA FOR")
                {
                    while (Buffer.SubString(0,15) != "AIRWAY DATA FOR")
                    {
                        if (Buffer.SubString(0,4) == "Name")
                        {
                            Buffer = Buffer.SubString(5,Buffer.Length()-4);
                            Buffer = Buffer.Trim();
                            AirportName = Buffer;
                            //Get the next line (Latitude)
                            input.getline(buf, sizeof(buf));
                            Buffer = buf;
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            GetLatLong(Buffer);
                            AirportLL = Latitude;
                            //Get the next line (Longitude)
                            input.getline(buf, sizeof(buf));
                            Buffer = buf;
                            Buffer = Buffer.Trim();
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            TempLongitude = Buffer;

                            while (Buffer.SubString(0,19) != "Landing Glide Slope")
                            {
                                if (Buffer.SubString(0,21) == "Local Safety Altitude")
                                {
                                    Buffer = Buffer.SubString(22,Buffer.Length()-21);
                                    Buffer = Buffer.Trim();
                                    //The LSA comes as a '02300 Ft' format, and must be
                                    //output as '23'. Therefore, trim off the last 5 ch.
                                    Buffer = Buffer.SubString(0,Buffer.Length()-3);
                                    if (Buffer.SubString(0,1) == "0")
                                    {
                                        i=1;
                                        while (Buffer[i] == '0')
                                        {
                                            //Trim off the first char.
                                            Buffer = Buffer.SubString(2,Buffer.Length()-1);
                                            Buffer = Buffer.Trim();
                                        }

                                    }
                                    SafeAltLev = Buffer;
                                }
                                if (Buffer.SubString(0,9) == "Longitude")
                                {
                                    //Extra processing required to fix the data error in the
                                    //Airport longitude. The last two chars are needed from
                                    //the runway long. to make the Airport long. valid.

                                    Buffer = Buffer.SubString(10,Buffer.Length()-9);
                                    Buffer = Buffer.Trim();

                                    //get just the last two chars off the co-ord. to add on
                                    //to the Airport long.
                                    Buffer = Buffer.SubString(11,Buffer.Length()-10);
                                    TempLongitude += Buffer;
                                    Buffer = TempLongitude;
                                    GetLatLong(Buffer);
                                    //GetLatLong returns the Airport Long. Add it to the
                                    //AirportLL.
                                    AirportLL += " " + Longitude;
                                }

                                input.getline(buf, sizeof(buf));
                                Buffer = buf;
                                Buffer = Buffer.Trim();
                                if (Buffer.SubString(0,19) == "Landing Glide Slope")
                                {
                                    //Output Airport Data.
                                    output<<"AF "<<AirportName.c_str()<<endl;
                                    output<<"LL "<<AirportLL.c_str()<<endl;
                                    output<<"SH "<<SafeAltLev.c_str()<<endl;
                                    output<<endl;
                                }
                            }//end while != Landing Glide Slope

                        }//End if buffer = Name.
                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }//end while != "AIRWAY DATA FOR"

                }//end if = "AIRPORT DATA FOR"

                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
            }//end while != "AIRWAY NAME"
        }//end if = "AIRSPACE  MASTER PAGE"
    }//end while != "AIRWAY NAME"
    //------------------------------------------------------------------------------

    input.close();
    input.open(OpenFileName.c_str());

    //------------------------------------------------------------------------------
    //This while loop will gather the Hold data, and the Airway Records.
    while (Buffer.SubString(0,16) != "Route Parameters")
    {
        if (Buffer.SubString(0,12) == "FIX DATA FOR")
        {
            while (Buffer.SubString(0,16) != "AIRPORT DATA FOR")
            {
                if (Buffer.SubString(0,8) == "FIX NAME")
                {
                    Buffer = Buffer.SubString(10,Buffer.Length()-9);
                    Buffer = Buffer.Trim();
                    FixName = Buffer;
                }

                //If there is a hold for this fix then get data.
                if (Buffer.SubString(0,15) == "Inbound Heading")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();
                    Buffer = Buffer.SubString(0,Buffer.Length()-8);
                    InboundHeading = Buffer;
                }
                if (Buffer.SubString(0,17) == "Direction of turn")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();
                    TurnDir = Buffer;
                }
                if (Buffer.SubString(0,19) == "Maximum Hold Height")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();

                    //The data is of type Alt, convert to FL. (06000 Ft)->(F60)
                    //Therefore trim off the last five chars.
                    Buffer = Buffer.SubString(0,Buffer.Length() -5);
                    //if the first number is a zero, it isn't needed.
                    while (Buffer.SubString(0,1) == "0")
                    {
                        //Trim off the first char.
                        Buffer = Buffer.SubString(2,Buffer.Length()-1);
                    }
                    //If level is not set then set it to zero.
                    if (Buffer.Length() == 0)
                    Buffer = "00";

                    MaxHoldHeight = "F" + Buffer;
                }
                if (Buffer.SubString(0,19) == "Minimum Hold Height")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();

                    //The data is of type Alt, convert to FL. (06000 Ft)->(F60)
                    //Therefore trim off the last five chars.
                    Buffer = Buffer.SubString(0,Buffer.Length() -5);
                    //if the first number is a zero, it isn't needed.
                    while (Buffer.SubString(0,1) == "0")
                    {
                        //Trim off the first char.
                        Buffer = Buffer.SubString(2,Buffer.Length()-1);
                    }
                    //If level is not set then set it to zero.
                    if (Buffer.Length() == 0)
                    Buffer = "00";

                    MinHoldHeight = "F" + Buffer;

                    //end of a Hold record, therefore output the data.
                    output<<"HP "<<FixName.c_str()<<endl;
                    output<<"IB "<<InboundHeading.c_str()<<endl;
                    output<<"TD "<<TurnDir.c_str()<<endl;
                    output<<"XH "<<MaxHoldHeight.c_str()<<endl;
                    output<<"MH "<<MinHoldHeight.c_str()<<endl;
                    output<<endl;
                }
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
            }
        }//end if Fix Data.
        if (Buffer.SubString(0,15) == "AIRWAY DATA FOR")
        {
            bool first_item;
            while (Buffer.SubString(0,14) != "ROUTE DATA FOR")
            {
                if (Buffer.SubString(0,11) == "AIRWAY NAME")
                {
                    Buffer = Buffer.SubString(12,Buffer.Length()-11);
                    Buffer = Buffer.Trim();
                    AirwayName = Buffer;
                    output<<"AW "<<AirwayName.c_str()<<endl;
                }

                if (Buffer.SubString(0,20) == "Minimum Cruise Level")
                {
                    first_item = true;

                    String  Width = "0",
                    MaxCruiseLev = "F999",
                    Direction = "B";

                    //Trim off the ID.
                    Buffer = Buffer.SubString(21,Buffer.Length()-20);
                    Buffer = Buffer.Trim();

                    //The data is of type Alt, convert to FL. (06000 Ft)->(FL60)
                    //Therefore trim off the last five chars.
                    Buffer = Buffer.SubString(0,Buffer.Length() -5);
                    while (Buffer.SubString(0,1) == "0")
                    {
                        //Trim off the first char.
                        Buffer = Buffer.SubString(2,Buffer.Length()-1);
                    }
                    Buffer = FormatFloat("000", Buffer.ToDouble());
                    MinCruiseLev = "&MI F"+Buffer;
                    //This data will be added to the first line of Route data.
                    //MinCruiseLev = "MI " + Width + " " + "F" + Buffer + " " + MaxCruiseLev + " " + Direction;
                    //output<<MinCruiseLev.c_str()<<endl;
                }

                if (Buffer.SubString(0,6) == "ROUTE:")
                {
                    Buffer = Buffer.SubString(7,Buffer.Length()-6);
                    Buffer = Buffer.Trim();
                    AirwayRoute = Buffer;

                    //while the next line is not blank, then keep getting the Route Data.
                    while (Buffer != NULL)
                    {
                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                        if (Buffer == "")
                        Buffer = NULL;
                        else
                        //Add the next line of Route data.
                        AirwayRoute += " " + Buffer;
                    }

                    //Output the rest of the Route data.
                    while (AirwayRoute != NULL)
                    {
                        //To find out if this is the last bit of data on the line.
                        NextSpace = AirwayRoute.Pos(" ");

                        if (NextSpace != 0)
                        {
                            i=1;
                            //AirwayRoute String now holds all of the Route data for this Airway.
                            while (AirwayRoute[i] != ' ')
                            {
                                i++;
                            }
                            //Store this section of the Route.
                            ThisRoute = AirwayRoute.SubString(0,i-1);

                            //Trim off the Bearing from the buffer.
                            AirwayRoute = AirwayRoute.SubString(i,AirwayRoute.Length()-(i-1));
                            AirwayRoute = AirwayRoute.Trim();

                            //Output the this line of Route Data.
                            if (first_item)
                            {
                                ThisRoute = ThisRoute+MinCruiseLev;
                                first_item = false;
                            }

                            output<<"RO "<<ThisRoute.c_str()<<endl;
                        }

                        //If this is the last bit of data on the line.
                        else
                        {
                            //What is left is the last FixName.
                            ThisRoute = AirwayRoute;

                            //Output the last line of Route Data.
                            output<<"RO "<<ThisRoute.c_str()<<endl;

                            //Output the spacer.
                            output<<endl;

                            //End of line, therefore set String to NULL.
                            AirwayRoute = NULL;
                        }
                    }
                }

                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
            }//end while != "ROUTE DATA FOR"
        }//end if = "AIRWAY DATA FOR"

        input.getline(buf, sizeof(buf));
        Buffer = buf;
        Buffer = Buffer.Trim();
    }// end while != Route Parameters...
    //------------------------------------------------------------------------------

    input.close();
    input.open(OpenFileName.c_str());

    //------------------------------------------------------------------------------
    // This while loop will extract the Runway and Missed approach data.
    while (Buffer.SubString(0,13) != "A/C PERF DATA" && !input.eof())
    {
        if (Buffer.SubString(0,16) == "AIRPORT DATA FOR")
        {
            while (Buffer.SubString(0,15) != "AIRWAY DATA FOR")
            {
                if (Buffer.SubString(0,4) == "Name")
                {
                    Buffer = Buffer.SubString(5,Buffer.Length()-4);
                    Buffer = Buffer.Trim();
                    AirportName = Buffer;
                }
                // Get the Runway Data.
                if (Buffer.SubString(0,11) == "RUNWAY DATA")
                {
                    while (Buffer.SubString(0,19) != "Landing Glide Slope")
                    {
                        if (Buffer.SubString(0,21) == "Runway Identification")
                        {
                            Buffer = Buffer.SubString(22,Buffer.Length()-21);
                            Buffer = Buffer.Trim();
                            RunwayID = Buffer;
                        }

                        if (Buffer.SubString(0,14) == "Runway Heading")
                        {
                            Buffer = Buffer.SubString(15,Buffer.Length()-14);
                            Buffer = Buffer.Trim();
                            RunwayHeading = Buffer;
                            RunwayHeading = RunwayHeading.SubString(0,RunwayHeading.Length() -8);
                        }

                        if (Buffer.SubString(0,26) == "Minimum Arrival Separation")
                        {
                            Buffer = Buffer.SubString(27,Buffer.Length()-26);
                            Buffer = Buffer.Trim();
                            MinArrSep = Buffer;
                            MinArrSep = MinArrSep.SubString(0,MinArrSep.Length() -5);
                        }

                        if (Buffer.SubString(0,24) == "Min Departure Separation")
                        {
                            Buffer = Buffer.SubString(25,Buffer.Length()-24);
                            Buffer = Buffer.Trim();
                            MinDepSep = Buffer;
                            MinDepSep = MinDepSep.SubString(0,MinDepSep.Length() -5);
                        }

                        if (Buffer.SubString(0,20) == "Take Off Turn Height")
                        {
                            Buffer = Buffer.SubString(21,Buffer.Length()-20);
                            Buffer = Buffer.Trim();
                            MinTurnHeight = Buffer;
                            MinTurnHeight = MinTurnHeight.SubString(0,MinTurnHeight.Length() -3);
                        }

                        if (Buffer.SubString(0,8) == "Latitude")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            GetLatLong(Buffer);
                            RunwayLL = Latitude;
                        }

                        if (Buffer.SubString(0,9) == "Longitude")
                        {
                            Buffer = Buffer.SubString(10,Buffer.Length()-9);
                            Buffer = Buffer.Trim();
                            GetLatLong(Buffer);
                            RunwayLL += " " + Longitude;
                        }

                        if (Buffer.SubString(0,19) == "Touchdown Elevation")
                        {
                            Buffer = Buffer.SubString(20,Buffer.Length()-19);
                            Buffer = Buffer.Trim();
                            RunwayElevation = Buffer;
                            RunwayElevation = RunwayElevation.SubString(0,RunwayElevation.Length() -3);
                        }

                        if (Buffer.SubString(0,16) == "Default Approach")
                        {
                            Buffer = Buffer.SubString(17,Buffer.Length()-16);
                            Buffer = Buffer.Trim();
                            DefaultApp = Buffer;
                        }

                        if (Buffer.SubString(0,25) == "Default Circuit Direction")
                        {
                            Buffer = Buffer.SubString(26,Buffer.Length()-25);
                            Buffer = Buffer.Trim();
                            CircuitDirection = Buffer;

                            //Output Airport and Runway Data.
                            output<<"RU "<<RunwayID.c_str()<<endl;
                            output<<"RT "<<RunwayHeading.c_str()<<endl;
                            output<<"AM "<<MinArrSep.c_str()<<endl;
                            output<<"DM "<<MinDepSep.c_str()<<endl;
                            output<<"TH "<<MinTurnHeight.c_str()<<endl;
                            output<<"LL "<<RunwayLL.c_str()<<endl;
                            output<<"EL "<<RunwayElevation.c_str()<<endl;
                            output<<"CD "<<CircuitDirection.c_str()<<endl;
                            output<<"AD "<<DefaultApp.c_str()<<endl;
                            output<<"AN "<<AirportName.c_str()<<endl;
                            output<<endl;
                        }
                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }
                }

                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
            }//end while != "AIRWAY DATA FOR"

        }//end if = "AIRPORT DATA FOR"

        if (Buffer.SubString(0,14) == "MAP ROUTE DATA")
        {
            while (Buffer.SubString(0,17) != "A/C PERF DATA FOR")
            {
                if (Buffer.SubString(0,8) == "MAP Name")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();
                    MAPName = Buffer;
                }
                if (Buffer.SubString(0,11) == "MainAirport")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();
                    AirportName = Buffer;
                }
                //code changed for 163-241
                if (Buffer.SubString(0,10) == "MainRwySet")
                {
                    RunwayID = "";
                    Buffer = Buffer.SubString(11, Buffer.Length()-10);

                    while (Buffer.SubString(0,22) != "MAP ROUTE ELEMENT DATA")
                    {
                        RunwayID = RunwayID+ " "+Buffer;

                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }
                }
                /*if (Buffer.SubString(0,10) == "MainRwySet")
                {
                    Buffer = Buffer.SubString(20,Buffer.Length()-19);
                    Buffer = Buffer.Trim();
                    RunwayID = Buffer;
                } */

                if (Buffer.SubString(0,22) == "MAP ROUTE ELEMENT DATA")
                {
                    //new code added for changes 241.
                    TStringList* route_list = new TStringList;

                    //add all of the route items for this mapc.
                    input.getline(buf, sizeof(buf));
                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();

                    while (Buffer != "")
                    {
                        if (Buffer.SubString(3,1) == ":")
                        route_list->Add(Buffer);

                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }

                    //now loop though each of the runways, create a mapc and any legs for the current runway.
                    //if the route item is common then it should be added for ever leg.
                    while (RunwayID != "")
                    {
                        RunwayID = RunwayID.Trim();
                        int pos_space = RunwayID.Pos(" ");
                        String current_rw;

                        if (pos_space != 0)
                        {
                            current_rw = RunwayID.SubString(0,pos_space-1);
                            RunwayID = RunwayID.SubString(pos_space+1, RunwayID.Length()-pos_space);
                        }
                        else
                        {
                            current_rw = RunwayID;
                            RunwayID = "";
                        }

                        String missed_apc_name = MAPName + current_rw;

                        if (current_rw != "NONE")
                        {
                            output<<"MA "<<missed_apc_name.c_str()<<endl;
                            //add the MApc name to the list.
                            MApc_List->Add(missed_apc_name);

                            output<<"AN "<<AirportName.c_str()<<endl;
                            output<<"RY "<<current_rw.c_str()<<endl;
                            output<<"RB"<<endl;
                            //loop through all of the route elements for this mapc, any that are found
                            //with the current runway id or are common then add.
                            for (int x = 0; x < route_list->Count; x++)
                            {
                                String temp_route = route_list->Strings[x];
                                int pos_common = temp_route.Pos("Common");
                                int pos_runway = temp_route.Pos(AirportName+":"+current_rw);

                                if (pos_common != 0 || pos_runway != 0)
                                {
                                    ConvertRouteElement(temp_route, current_rw);
                                    output<<RouteElementData.c_str()<<endl;
                                }
                            }
                            output<<"RE"<<endl;
                            output<<endl;
                        }
                    }

                    delete route_list;
                }
                /*
                if (MAPName != "" && AirportName != "" && RunwayID != "")
                {
                    output<<endl;
                    output<<"MA "<<MAPName.c_str()<<endl;
                    output<<"AN "<<AirportName.c_str()<<endl;
                    output<<"RY "<<RunwayID.c_str()<<endl;

                    //Signal the start of the Route Element Data
                    output<<"RB"<<endl;
                    input.getline(buf, sizeof(buf));
                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();
                    while (Buffer != "")
                    {
                        if (Buffer.SubString(3,1) == ":")
                        {
                            ConvertRouteElement(Buffer, RunwayID);
                            output<<RouteElementData.c_str()<<endl;
                        }

                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }
                    output<<"RE"<<endl;
                }
            }*/
            input.getline(buf, sizeof(buf));
            Buffer = buf;
            Buffer = Buffer.Trim();
        }//end while != "A/C PERF DATA FOR"
        output<<endl;
    }//end if = "MAP ROUTE DATA"
    input.getline(buf, sizeof(buf));
    Buffer = buf;
    Buffer = Buffer.Trim();
}
//------------------------------------------------------------------------------

input.close();
input.open(OpenFileName.c_str());

//------------------------------------------------------------------------------
// This while loop will extract the Approach, SID and Star data.
while (Buffer.SubString(0,14) != "MAP ROUTE DATA")
{
    if (Buffer.SubString(0,16) == "AIRPORT DATA FOR")
    {
        while (Buffer.SubString(0,15) != "AIRWAY DATA FOR")
        {
            if (Buffer.SubString(0,4) == "Name")
            {
                Buffer = Buffer.SubString(5,Buffer.Length()-4);
                Buffer = Buffer.Trim();
                AirportName = Buffer;
            }

            if (Buffer.SubString(0,21) == "Runway Identification")
            {
                Buffer = Buffer.SubString(22,Buffer.Length()-21);
                Buffer = Buffer.Trim();
                RunwayID = Buffer;
            }

            //Get and process any approaches of type ILS
            if (Buffer.SubString(0,12) == "ILS APPROACH")
            {
                Buffer = Buffer.SubString(13,Buffer.Length()-12);
                Buffer = Buffer.Trim();
                ApproachName = Buffer;

                //Get Approach Type.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(18,Buffer.Length()-17);
                Buffer = Buffer.Trim();
                ApproachType = Buffer;

                //Get Final Approach Track.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(21,Buffer.Length()-20);
                Buffer = Buffer.Trim();
                FinalAPCTrack = Buffer;
                FinalAPCTrack = FinalAPCTrack.SubString(0,FinalAPCTrack.Length() -8);

                //Get Min Decision Alt.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(26,Buffer.Length()-25);
                Buffer = Buffer.Trim();
                MinDecisionAlt = Buffer;
                MinDecisionAlt = MinDecisionAlt.SubString(0,MinDecisionAlt.Length() -3);

                //Get Outer Marker Rng.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(19,Buffer.Length()-18);
                Buffer = Buffer.Trim();
                OuterMarkerRng = Buffer;
                OuterMarkerRng = OuterMarkerRng.SubString(0,OuterMarkerRng.Length() -7);

                //Get Glide Path Angle.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(19,Buffer.Length()-18);
                Buffer = Buffer.Trim();
                //if the first number is a zero, it isn't needed.
                while (Buffer.SubString(0,1) == "0")
                {
                    //Trim off the first char.
                    Buffer = Buffer.SubString(2,Buffer.Length()-1);
                }
                GlidePathAngle = Buffer;
                GlidePathAngle = GlidePathAngle.SubString(0,GlidePathAngle.Length() -5);

                //Get Localiser only MDA.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(19,Buffer.Length()-18);
                Buffer = Buffer.Trim();
                LocaliserMDA = Buffer;
                LocaliserMDA = LocaliserMDA.SubString(0,LocaliserMDA.Length() -3);

                //Get Missed Approach.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                MissedApcName = Buffer;

                //code added for fault 241.
                bool found = false;

                //see if the MAPC Name exists in the MApc_List, if not, then try to add the current
                //runway to the end of the name.
                for (int x = 0; x < MApc_List->Count; x++)
                {
                    String temp = MApc_List->Strings[x];

                    if (temp == MissedApcName)
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    //try adding the current runway to the MissedApproach name.
                    MissedApcName = MissedApcName+RunwayID;
                    
                    for (int x = 0; x < MApc_List->Count; x++)
                    {
                        String temp = MApc_List->Strings[x];

                        if (temp == MissedApcName)
                        {
                            found = true;
                            break;
                        }
                    }
                }

                if (found)
                {
                    //Output all Data
                    output<<"AP "<<ApproachName.c_str()<<endl;
                    output<<"TY "<<ApproachType.c_str()<<endl;
                    output<<"MD "<<MinDecisionAlt.c_str()<<endl;
                    output<<"OM "<<OuterMarkerRng.c_str()<<endl;
                    output<<"FT "<<FinalAPCTrack.c_str()<<endl;
                    output<<"GS "<<GlidePathAngle.c_str()<<endl;
                    output<<"LO "<<LocaliserMDA.c_str()<<endl;
                    output<<"MP "<<MissedApcName.c_str()<<endl;
                    output<<"AN "<<AirportName.c_str()<<endl;
                    output<<"RY "<<RunwayID.c_str()<<endl;
                    output<<endl;
                }
            }
            //------------------------------------------------------------------
            //Get and process any approaches of type SRA
            if (Buffer.SubString(0,12) == "SRA APPROACH")
            {
                Buffer = Buffer.SubString(13,Buffer.Length()-12);
                Buffer = Buffer.Trim();
                ApproachName = Buffer;

                //Get Final Approach Track.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(21,Buffer.Length()-20);
                Buffer = Buffer.Trim();
                FinalAPCTrack = Buffer;
                FinalAPCTrack = FinalAPCTrack.SubString(0,FinalAPCTrack.Length() -8);

                //Get Min Decision Alt.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(26,Buffer.Length()-25);
                Buffer = Buffer.Trim();
                MinDecisionAlt = Buffer;
                MinDecisionAlt = MinDecisionAlt.SubString(0,MinDecisionAlt.Length() -3);

                //Get Termination Range.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(19,Buffer.Length()-18);
                Buffer = Buffer.Trim();
                TerminationRange = Buffer;
                TerminationRange = TerminationRange.SubString(0,TerminationRange.Length() -7);
                
                //Get Glide Path Angle.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(19,Buffer.Length()-18);
                Buffer = Buffer.Trim();
                //if the first number is a zero, it isn't needed.
                while (Buffer.SubString(0,1) == "0")
                {
                    //Trim off the first char.
                    Buffer = Buffer.SubString(2,Buffer.Length()-1);
                }
                GlidePathAngle = Buffer;
                GlidePathAngle = GlidePathAngle.SubString(0,GlidePathAngle.Length() -5);

                //Get Missed Approach.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                MissedApcName = Buffer;
                //code added for fault 241.
                bool found = false;

                //see if the MAPC Name exists in the MApc_List, if not, then try to add the current
                //runway to the end of the name.
                for (int x = 0; x < MApc_List->Count; x++)
                {
                    String temp = MApc_List->Strings[x];

                    if (temp == MissedApcName)
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    //try adding the current runway to the MissedApproach name.
                    MissedApcName = MissedApcName+RunwayID;
                    
                    for (int x = 0; x < MApc_List->Count; x++)
                    {
                        String temp = MApc_List->Strings[x];

                        if (temp == MissedApcName)
                        {
                            found = true;
                            break;
                        }
                    }
                }

                if (found)
                {
                    //Output all Data
                    output<<"AP "<<ApproachName.c_str()<<endl;
                    //As there is no type given, just output the text SRA.
                    output<<"TY "<<"SRA"<<endl;
                    output<<"MD "<<MinDecisionAlt.c_str()<<endl;
                    output<<"FT "<<FinalAPCTrack.c_str()<<endl;
                    output<<"GS "<<GlidePathAngle.c_str()<<endl;
                    output<<"MP "<<MissedApcName.c_str()<<endl;
                    output<<"TR "<<TerminationRange.c_str()<<endl;
                    output<<"AN "<<AirportName.c_str()<<endl;
                    output<<"RY "<<RunwayID.c_str()<<endl;
                    output<<endl;
                }
            }
            input.getline(buf, sizeof(buf));
            Buffer = buf;
            Buffer = Buffer.Trim();
        }//end while != "AIRWAY DATA FOR"

    }//end if = "AIRPORT DATA FOR"

    //Get the SID Data.
    if (Buffer.SubString(0,15) == "SID ROUTES DATA")
    {
        while (Buffer.SubString(0,15) != "STAR ROUTE DATA")
        {
            if (Buffer.SubString(0,8) == "SID Name")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                SIDName = Buffer;
            }

            if (Buffer.SubString(0,11) == "MainAirport")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                AirportName = Buffer;
            }

            if (Buffer.SubString(0,16) == "SatelliteAirport")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                SatAirportName = Buffer;
            }

            if (Buffer.SubString(0,10) == "MainRwySet")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                RunwayID = Buffer;

            }

            if (Buffer.SubString(0,15) == "SatelliteRwySet")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                SatRunwayID = Buffer;

            }

            if (Buffer.SubString(0,11) == "MinAltitude")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0,Buffer.Length() -3);
                SSAltLevel = "F" + Buffer;
                //Get next line of data.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                //Sort out the Max data.
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0,Buffer.Length() -3);
                SSAltLevel += " F" + Buffer;
            }

            if (Buffer.SubString(0,22) == "SID ROUTE ELEMENT DATA")
            {
                //new code added for changes 241.
                TStringList* route_list = new TStringList;

                //add all of the route items for this mapc.
                input.getline(buf, sizeof(buf));
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();

                while (Buffer != "")
                {
                    if (Buffer.SubString(3,1) == ":")
                    route_list->Add(Buffer);

                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();
                }

                //now loop though each of the runways, create a SID and any legs for the current runway.
                //if the route item is common then it should be added for every leg.
                while (RunwayID != "")
                {
                    RunwayID = RunwayID.Trim();
                    int pos_space = RunwayID.Pos(" ");
                    String current_rw;

                    if (pos_space != 0)
                    {
                        current_rw = RunwayID.SubString(0,pos_space-1);
                        RunwayID = RunwayID.SubString(pos_space+1, RunwayID.Length()-pos_space);
                    }
                    else
                    {
                        current_rw = RunwayID;
                        RunwayID = "";
                    }

                    String sid_name = SIDName + current_rw;

                    if (current_rw != "NONE")
                    {
                        output<<"PD "<<sid_name.c_str()<<endl;
                        output<<"AY "<<AirportName.c_str()<<" "<<current_rw.c_str()<<endl;
                        if (SatAirportName != "NONE")
                        output<<"AY "<<SatAirportName.c_str()<<" "<<SatRunwayID.c_str()<<endl;
                        output<<"AL "<<SSAltLevel.c_str()<<endl;
                        //Signal the start of the Route Element Data
                        output<<"RB"<<endl;

                        //loop through all of the route elements for this mapc, any that are found
                        //with the current runway id or are common then add.
                        for (int x = 0; x < route_list->Count; x++)
                        {
                            String temp_route = route_list->Strings[x];
                            int pos_common = temp_route.Pos("Common");
                            int pos_id_fix = temp_route.Pos("Identifying Fix :");
                            int pos_runway = temp_route.Pos(AirportName+":"+current_rw);

                            if (pos_common != 0 || pos_runway != 0 || pos_id_fix != 0)
                            {
                                ConvertRouteElement(temp_route, current_rw);
                                output<<RouteElementData.c_str()<<endl;
                            }
                        }
                        output<<"RE"<<endl;
                        output<<endl;
                    }
                }

                /*if (SIDName != "" && AirportName != "" && RunwayID != "")
                {
                    output<<endl;
                    output<<"PD "<<SIDName.c_str()<<endl;
                    output<<"AY "<<AirportName.c_str()<<" "<<RunwayID.c_str()<<endl;
                    if (SatAirportName != "NONE")
                    output<<"AY "<<SatAirportName.c_str()<<" "<<SatRunwayID.c_str()<<endl;
                    output<<"AL "<<SSAltLevel.c_str()<<endl;

                    //Signal the start of the Route Element Data
                    output<<"RB"<<endl;
                    input.getline(buf, sizeof(buf));
                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();
                    while (Buffer != "")
                    {
                        if (Buffer.SubString(3,1) == ":")
                        {
                            ConvertRouteElement(Buffer, RunwayID);
                            output<<RouteElementData.c_str()<<endl;
                        }

                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }
                    output<<"RE"<<endl;
                }*/
                delete route_list;
            }

            input.getline(buf, sizeof(buf));
            Buffer = buf;
            Buffer = Buffer.Trim();
        }//end while != "ROUTE DATA FOR"
    }//end if = "SID ROUTES DATA"
    //Get the SID Data.
    if (Buffer.SubString(0,15) == "STAR ROUTE DATA")
    {
        while (Buffer.SubString(0,14) != "MAP ROUTE DATA")
        {
            if (Buffer.SubString(0,9) == "STAR Name")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                STARName = Buffer;
            }

            if (Buffer.SubString(0,11) == "MainAirport")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                AirportName = Buffer;
            }

            if (Buffer.SubString(0,16) == "SatelliteAirport")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                SatAirportName = Buffer;
            }

            if (Buffer.SubString(0,10) == "MainRwySet")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                RunwayID = Buffer;
            }

            if (Buffer.SubString(0,15) == "SatelliteRwySet")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                SatRunwayID = Buffer;
            }

            if (Buffer.SubString(0,11) == "MinAltitude")
            {
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0,Buffer.Length() -3);
                SSAltLevel = "F" + Buffer;
                //Get next line of data.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                //Sort out the Max data.
                Buffer = Buffer.SubString(20,Buffer.Length()-19);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0,Buffer.Length() -3);
                SSAltLevel += " F" + Buffer;
            }

            if (Buffer.SubString(0,23) == "STAR ROUTE ELEMENT DATA")
            {
                //new code added for changes 241.
                TStringList* route_list = new TStringList;

                //add all of the route items for this mapc.
                input.getline(buf, sizeof(buf));
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();

                while (Buffer != "")
                {
                    if (Buffer.SubString(3,1) == ":")
                    route_list->Add(Buffer);

                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();
                }

                //now loop though each of the runways, create a STAR and any legs for the current runway.
                //if the route item is common then it should be added for every leg.
                //a new star must also be created for every identifiying fix defined in the route.
                while (RunwayID != "")
                {
                    RunwayID = RunwayID.Trim();
                    int pos_space = RunwayID.Pos(" ");
                    int ident_count = 0;
                    String current_rw;

                    if (pos_space != 0)
                    {
                        current_rw = RunwayID.SubString(0,pos_space-1);
                        RunwayID = RunwayID.SubString(pos_space+1, RunwayID.Length()-pos_space);
                    }
                    else
                    {
                        current_rw = RunwayID;
                        RunwayID = "";
                    }

                    String star_name = STARName + current_rw;

                    TStringList* temp_route_list = new TStringList;

                    //copy the route_list to the temp list.
                    for (int y = 0; y < route_list->Count; y++)
                    {
                        String temp_route = route_list->Strings[y];
                        temp_route_list->Add(temp_route);
                        int pos_ident_fix = temp_route.Pos("Identifying Fix :");

                        if (pos_ident_fix != 0)
                        ident_count++;
                    }

                    for (int z = 0; z < ident_count; z++)
                    {
                        //add the number of STARS for this runway.
                        bool ident_found = false;
                        bool first_item = true;
                        int ident_index = 0;

                        for (int x = 0; x < temp_route_list->Count; x++)
                        {
                            String temp_route = temp_route_list->Strings[x];
                            int pos_common = temp_route.Pos("Common");
                            int pos_id_fix = temp_route.Pos("Identifying Fix :");
                            int pos_runway = temp_route.Pos(AirportName+":"+current_rw);

                            if (pos_common != 0 || pos_runway != 0 || (pos_id_fix != 0 && !ident_found))
                            {
                                if (first_item)
                                {
                                    temp_route = temp_route.Trim();
                                    int index = 0,
                                    length = temp_route.Length();

                                    while (index < length)
                                    {
                                        if (temp_route[length] == ' ')
                                        break;
                                        else
                                        length--;
                                    }

                                    String fix_name = temp_route.SubString(length+1, temp_route.Length()-(length+1));
                                    String name = STARName+current_rw+fix_name;
                                    output<<"PE "<<name.c_str()<<endl;
                                    output<<"AY "<<AirportName.c_str()<<" "<<current_rw.c_str()<<endl;
                                    if (SatAirportName != "NONE")
                                    output<<"AY "<<SatAirportName.c_str()<<" "<<SatRunwayID.c_str()<<endl;
                                    output<<"AL "<<SSAltLevel.c_str()<<endl;

                                    //Signal the start of the Route Element Data
                                    output<<"RB"<<endl;
                                }
                                ConvertRouteElement(temp_route, current_rw);
                                output<<RouteElementData.c_str()<<endl;

                                first_item = false;
                            }

                            if (pos_id_fix != 0 && !ident_found)
                            {
                                ident_found = true;
                                ident_index = x;
                            }
                        }
                        output<<"RE"<<endl;
                        output<<endl;
                        //delete the first ident route leg.
                        temp_route_list->Delete(ident_index);
                    }

                    

                    delete temp_route_list;
                }

                /*if (STARName != "" && AirportName != "" && RunwayID != "")
                {
                    output<<endl;
                    output<<"PE "<<STARName.c_str()<<endl;
                    output<<"AY "<<AirportName.c_str()<<" "<<RunwayID.c_str()<<endl;
                    if (SatAirportName != "NONE")
                    output<<"AY "<<SatAirportName.c_str()<<" "<<SatRunwayID.c_str()<<endl;
                    output<<"AL "<<SSAltLevel.c_str()<<endl;

                    //Signal the start of the Route Element Data
                    output<<"RB"<<endl;
                    input.getline(buf, sizeof(buf));
                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();
                    while (Buffer != "")
                    {
                        if (Buffer.SubString(3,1) == ":")
                        {
                            ConvertRouteElement(Buffer, RunwayID);
                            output<<RouteElementData.c_str()<<endl;
                        }

                        input.getline(buf, sizeof(buf));
                        Buffer = buf;
                        Buffer = Buffer.Trim();
                    }
                    output<<"RE"<<endl;
                }*/
            }


            input.getline(buf, sizeof(buf));
            Buffer = buf;
            Buffer = Buffer.Trim();
        }//end while != "MAP ROUTE DATA"
    }//end if = "STAR ROUTE DATA"
    input.getline(buf, sizeof(buf));
    Buffer = buf;
    Buffer = Buffer.Trim();
}
delete MApc_List;
output.close();

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

while (Buffer.SubString(0,16) != "WEATHER DATA FOR")
{
    input.getline(buf, sizeof(buf));
    Buffer = buf;
    Buffer = Buffer.Trim();
    // FINISH WITH AIRSPACE DATA....
    // CONVERT AC PERFORMANCE DATA....
    if (Buffer.SubString(0,17) == "º  TYPE  GROUP  º")
    {
        FileName = AirspaceFileName + ".dap";
        output.open(FileName.c_str());

        //Show the current file being processed.
        ConvertDataForm->Height = 190;
        ConvertDataForm->CurrentTextLabel->Visible = true;
        ConvertDataForm->CurrentTextLabel->Repaint();
        ConvertDataForm->Edit1->Text = FileName;
        ConvertDataForm->Edit1->Visible = true;
        ConvertDataForm->Edit1->Repaint();

        while (Buffer.SubString(0,16) != "WEATHER DATA FOR" && !input.eof())
        {
            input.getline(buf, sizeof(buf));
            Buffer = buf;
            Buffer = Buffer.Trim();
            if (Buffer.SubString(0,1) == "Ì")
            {
                //Get the position of the Aircraft types for later.
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                while (Buffer.SubString(0,1) != "È")
                {
                    ACTypeData += Buffer;
                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();
                }
            }//End if.
            //---------------------------------------------------------------------------

            if (Buffer.SubString(0,5) == "GROUP")
            {//open if
                Buffer = Buffer.SubString(6,Buffer.Length()-5);
                Buffer = Buffer.Trim();
                PerformanceGrp = Buffer;
                if (PerformanceGrp.Length() == 1)
                PerformanceGrp = "0" + PerformanceGrp;

                //Get all of Aircraft group data.
                while (Buffer.SubString(0,26) != "LEVEL MODIFIER DEFINITIONS")
                {//open while
                    if (Buffer.SubString(0,13) == "Maximum Speed")
                    {
                        Buffer = Buffer.SubString(14,Buffer.Length()-13);
                        Buffer = Buffer.Trim();
                        MaxSpeed = Buffer;
                        MaxSpeed = MaxSpeed.SubString(0,MaxSpeed.Length() -6);
                    }
                    if (Buffer.SubString(0,15) == "Flap Down Stall")
                    {
                        Buffer = Buffer.SubString(16,Buffer.Length()-15);
                        Buffer = Buffer.Trim();
                        MinSpeed = Buffer;
                        MinSpeed = MinSpeed.SubString(0,MinSpeed.Length() -6);
                    }
                    if (Buffer.SubString(0,14) == "Take Off Speed")
                    {
                        Buffer = Buffer.SubString(15,Buffer.Length()-14);
                        Buffer = Buffer.Trim();
                        TakeOff = Buffer;
                        TakeOff = TakeOff.SubString(0,TakeOff.Length() -6);
                    }
                    if (Buffer.SubString(0,11) == "Climb Speed")
                    {
                        Buffer = Buffer.SubString(12,Buffer.Length()-11);
                        Buffer = Buffer.Trim();
                        Climb = Buffer;
                        Climb = Climb.SubString(0,Climb.Length() -6);
                    }
                    if (Buffer.SubString(0,12) == "Cruise Speed")
                    {
                        Buffer = Buffer.SubString(13,Buffer.Length()-12);
                        Buffer = Buffer.Trim();
                        Cruise = Buffer;
                        Cruise = Cruise.SubString(0,Cruise.Length() -6);
                    }
                    if (Buffer.SubString(0,13) == "Holding Speed")
                    {
                        Buffer = Buffer.SubString(14,Buffer.Length()-13);
                        Buffer = Buffer.Trim();
                        Holding = Buffer;
                        Holding = Holding.SubString(0,Holding.Length() -6);
                    }
                    if (Buffer.SubString(0,13) == "Descent Speed")
                    {
                        Buffer = Buffer.SubString(14,Buffer.Length()-13);
                        Buffer = Buffer.Trim();
                        Descent = Buffer;
                        Descent = Descent.SubString(0,Descent.Length() -6);
                    }
                    if (Buffer.SubString(0,19) == "Terminal Area Speed")
                    {
                        Buffer = Buffer.SubString(20,Buffer.Length()-19);
                        Buffer = Buffer.Trim();
                        Terminal = Buffer;
                        Terminal = Terminal.SubString(0,Terminal.Length() -6);
                    }
                    if (Buffer.SubString(0,16) == "Intermediate APC")
                    {
                        Buffer = Buffer.SubString(17,Buffer.Length()-16);
                        Buffer = Buffer.Trim();
                        Intermediate = Buffer;
                        Intermediate = Intermediate.SubString(0,Intermediate.Length() -6);
                    }
                    if (Buffer.SubString(0,15) == "Final APC Speed")
                    {
                        Buffer = Buffer.SubString(16,Buffer.Length()-15);
                        Buffer = Buffer.Trim();
                        FinalAPC = Buffer;
                        FinalAPC = FinalAPC.SubString(0,FinalAPC.Length() -6);
                    }
                    if (Buffer.SubString(0,13) == "Landing Speed")
                    {
                        Buffer = Buffer.SubString(14,Buffer.Length()-13);
                        Buffer = Buffer.Trim();
                        Landing = Buffer;
                        Landing = Landing.SubString(0,Landing.Length() -6);
                    }
                    if (Buffer.SubString(0,13) == "Critical Mach")
                    {
                        Buffer = Buffer.SubString(14,Buffer.Length()-13);
                        Buffer = Buffer.Trim();
                        CriticalMach = Buffer;
                    }
                    if (Buffer.SubString(0,12) == "Acceleration")
                    {
                        Buffer = Buffer.SubString(13,Buffer.Length()-12);
                        Buffer = Buffer.Trim();
                        Acceleration = Buffer;
                        Acceleration = Acceleration.SubString(0,Acceleration.Length() -10);
                    }
                    if (Buffer.SubString(0,12) == "Deceleration")
                    {
                        Buffer = Buffer.SubString(13,Buffer.Length()-12);
                        Buffer = Buffer.Trim();
                        Deceleration = Buffer;
                        Deceleration = Deceleration.SubString(0,Deceleration.Length() -10);
                    }
                    if (Buffer.SubString(0,17) == "Normal Bank Angle")
                    {
                        Buffer = Buffer.SubString(18,Buffer.Length()-17);
                        Buffer = Buffer.Trim();
                        NormalBkAngle = Buffer;
                        NormalBkAngle = NormalBkAngle.SubString(0,NormalBkAngle.Length() -8);
                    }
                    if (Buffer.SubString(0,10) == "Climb Mach")
                    {
                        Buffer = Buffer.SubString(11,Buffer.Length()-10);
                        Buffer = Buffer.Trim();
                        ClimbMach = Buffer;
                    }
                    if (Buffer.SubString(0,11) == "Cruise Mach")
                    {
                        Buffer = Buffer.SubString(12,Buffer.Length()-11);
                        Buffer = Buffer.Trim();
                        CruiseMach = Buffer;
                    }
                    if (Buffer.SubString(0,7) == "Ceiling")
                    {
                        Buffer = Buffer.SubString(8,Buffer.Length()-7);
                        Buffer = Buffer.Trim();
                        Ceiling = Buffer;
                        Ceiling = Ceiling.SubString(0,Ceiling.Length() -3);
                    }
                    if (Buffer.SubString(0,12) == "Descent Rate")
                    {
                        Buffer = Buffer.SubString(13,Buffer.Length()-12);
                        Buffer = Buffer.Trim();
                        DescentRate = Buffer;
                        DescentRate = DescentRate.SubString(0,DescentRate.Length() -7);
                    }
                    if (Buffer.SubString(0,18) == "HEIGHT         ROC")
                    {
                        while (Buffer.SubString(0,23) != "EMERGENCY HANDLING DATA")
                        {
                            input.getline(buf, sizeof(buf));
                            Buffer = buf;
                            Buffer = Buffer.Trim();
                            HeightData += Buffer;
                        }
                    }

                    if (Buffer.SubString(0,11) == "Glide Speed")
                    {
                        Buffer = Buffer.SubString(12,Buffer.Length()-11);
                        Buffer = Buffer.Trim();
                        GlideSpeed = Buffer;
                        GlideSpeed = GlideSpeed.SubString(0,GlideSpeed.Length() -4);
                    }

                    if (Buffer.SubString(0,35) == "Partial Engine Failure Cruise Speed")
                    {
                        Buffer = Buffer.SubString(36,Buffer.Length()-35);
                        Buffer = Buffer.Trim();
                        PartialEngineFailureCruiseSpeed = Buffer;
                        PartialEngineFailureCruiseSpeed = PartialEngineFailureCruiseSpeed.SubString(0,PartialEngineFailureCruiseSpeed.Length() -4);
                    }

                    if (Buffer.SubString(0,22) == "Power Off Descent Rate")
                    {
                        Buffer = Buffer.SubString(23,Buffer.Length()-22);
                        Buffer = Buffer.Trim();
                        PowerOffDescentRate = Buffer;
                        PowerOffDescentRate = PowerOffDescentRate.SubString(0,PowerOffDescentRate.Length() -7);
                    }

                    if (Buffer.SubString(0,29) == "Partial Power Failure Ceiling")
                    {
                        Buffer = Buffer.SubString(30,Buffer.Length()-29);
                        Buffer = Buffer.Trim();
                        PartialPowerFailureCeiling = Buffer;
                        PartialPowerFailureCeiling = PartialPowerFailureCeiling.SubString(0,PartialPowerFailureCeiling.Length() -3);
                    }

                    if (Buffer.SubString(0,19) == "Expedite Climb Rate")
                    {
                        Buffer = Buffer.SubString(20,Buffer.Length()-19);
                        Buffer = Buffer.Trim();
                        ExpediteClb = Buffer;
                        ExpediteClb = ExpediteClb.SubString(0,ExpediteClb.Length() -2);
                    }
                    if (Buffer.SubString(0,21) == "Expedite Descent Rate")
                    {
                        Buffer = Buffer.SubString(22,Buffer.Length()-21);
                        Buffer = Buffer.Trim();
                        ExpediteDes = Buffer;
                        ExpediteDes = ExpediteDes.SubString(0,ExpediteDes.Length() -2);
                    }
                    //Gets next line.
                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();
                    //Data Output.....
                    if (Buffer.SubString(0,26) == "LEVEL MODIFIER DEFINITIONS")
                    {
                        output<<"PF "<<PerformanceGrp.c_str()<<endl;
                        
                        output<<"PC "<<PartialPowerFailureCeiling.c_str()<<endl;
                        if (CriticalMach != "")
                        output<<"MT "<<CriticalMach.c_str()<<endl;
                        output<<"CE "<<Ceiling.c_str()<<endl;
                        
                        //Output the HeightData
                        while (HeightData != NULL)
                        {
                            if (HeightData.SubString(7,2) != "Ft")
                            {
                                HeightData = HeightData.SubString(2,HeightData.Length() -1);
                                HeightData = HeightData.Trim();
                            }
                            if (HeightData.SubString(7,2) == "Ft")
                            {
                                TempHeight = HeightData.SubString(0,28);
                                HeightData = HeightData.SubString(29,HeightData.Length() -28);
                                HeightNum = TempHeight.SubString(0,5);
                                TempHeight = TempHeight.SubString(9,TempHeight.Length() -8);
                                TempHeight = TempHeight.Trim();
                                ROCNum = TempHeight.SubString(0,6);
                                ExpROC = (ROCNum.ToIntDef(0) * ExpediteClb.ToIntDef(0) /100);
                                //Output Data
                                output<<"LD "<<HeightNum.c_str()<<" "<<ROCNum.c_str()<<" "<<ExpROC<<endl;
                                output<<"MX "<<MaxSpeed.c_str()<<endl;
                                output<<"MN "<<MinSpeed.c_str()<<endl;
                                output<<"TO "<<TakeOff.c_str()<<endl;
                                output<<"CB "<<Climb.c_str()<<endl;
                                output<<"CR "<<Cruise.c_str()<<endl;
                                output<<"HS "<<Holding.c_str()<<endl;
                                output<<"DS "<<Descent.c_str()<<endl;
                                output<<"GI "<<GlideSpeed.c_str()<<endl;
                                output<<"PI "<<PartialEngineFailureCruiseSpeed.c_str()<<endl;
                                output<<"GR "<<PowerOffDescentRate.c_str()<<endl;
                                output<<"TM "<<Terminal.c_str()<<endl;
                                output<<"IS "<<Intermediate.c_str()<<endl;
                                output<<"FS "<<FinalAPC.c_str()<<endl;
                                output<<"LS "<<Landing.c_str()<<endl;
                                if (ClimbMach != "")
                                output<<"MB "<<ClimbMach.c_str()<<endl;
                                if (CruiseMach != "")
                                output<<"ME "<<CruiseMach.c_str()<<endl;
                                output<<"AR "<<Acceleration.c_str()<<endl;
                                output<<"DR "<<Deceleration.c_str()<<endl;
                                output<<"RD "<<DescentRate.c_str()<<endl;
                                output<<"NB "<<NormalBkAngle.c_str()<<endl;
                                //Calculate ExpDesRate data.
                                ExpDesRate = (DescentRate.ToIntDef(0) * ExpediteDes.ToIntDef(0) /100);
                                output<<"XD "<<ExpDesRate<<endl;
                            }
                            if (HeightData == "")
                            {
                                HeightData = NULL;
                            }

                        }//end while
                        output<<endl;
                    }//end if.
                }//end while.
            }//End if.
        }//End While.
        while (ACTypeData != NULL)
        {
            if (ACTypeData.SubString(2,1) != "/")
            {
                ACTypeData = ACTypeData.SubString(2,ACTypeData.Length() -1);
                ACTypeData = ACTypeData.Trim();
            }
            if (ACTypeData.SubString(2,1) == "/")
            {
                Wake = ACTypeData.SubString(0,1);
                TempTypeData = ACTypeData.SubString(0,9);
                ACTypeData = ACTypeData.SubString(10,ACTypeData.Length() -9);
                TempGroup = TempTypeData.SubString(0,6);
                TempGroup = TempGroup.Trim();
                TempGroup = TempGroup.SubString(3,TempGroup.Length() -2);
                TempTypeData = TempTypeData.SubString(7,TempTypeData.Length() -6);
                TempTypeData = TempTypeData.Trim();
                TempType = TempTypeData;
                if (TempType.Length() == 1)
                TempType = "0" + TempType;

                //Output Data

                output<<"AC "<<TempGroup.c_str()<<endl;
                output<<"PG "<<TempType.c_str()<<endl;
                output<<"VW "<<Wake.c_str()<<endl;
                output<<endl;
            }
            if (ACTypeData == "")
            ACTypeData = NULL;


        }//End While.
        output.close();
    }//End if.

}//End While

//------------------------------------------------------------------------------
String      AltSetting,
AreaName,
CloudData,
CloudGrade,
CloudLevel,
DewPoint,
GustDirection,
GustSpeed,
NextLevel,
SurfaceWind,
Temperature,
TempBuffer,
ThisCloudData,
ThisRunWay,
ThisWindData,
UpperWindData,
Visibility,
Weather,
rvr_start,
rvr_mid,
rvr_stop;

int         UnitPos = 0,
TempVis;

while (!input.eof())
{
    input.getline(buf, sizeof(buf));
    Buffer = buf;
    Buffer = Buffer.Trim();
    //See if the data is at the begining of a new weather section.
    if (Buffer.SubString(0,19) == "AIRFIELD WEATHER AT")
    {
        while (Buffer != "UPPER WIND DATA FOR AREA")
        {
            if (Buffer.SubString(0,12) == "Surface Wind")
            {
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                SurfaceWind = Buffer;
            }

            if (Buffer.SubString(0,10) == "Gust Speed")
            {
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(2,Buffer.Length() -1);
                Buffer = Buffer.SubString(0,Buffer.Length() -4);
                GustSpeed = Buffer;
            }

            if (Buffer.SubString(0,14) == "Gust Direction")
            {
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(2,Buffer.Length() -1);
                Buffer = Buffer.SubString(0,Buffer.Length() -8);
                GustDirection = Buffer;
            }

            if (Buffer.SubString(0,10) == "Visibility")
            {
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                //see if the Vis is in Km or something else.
                UnitPos = Buffer.Pos("Km");
                //If UnitPos is not 0 then the distance is Km's, the dist needs,
                //to be in M therefore *1000.
                if (UnitPos != 0)
                {
                    Buffer = Buffer.SubString(0,Buffer.Length() -2);
                    TempVis = Buffer.ToIntDef(0);
                    TempVis = TempVis * 1000;
                    Visibility = TempVis;
                }
                else//already in M and store it.
                {
                    Visibility = Buffer.SubString(0,Buffer.Length() -1);
                }
            }

            if (Buffer.SubString(0,7) == "Weather")
            {
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                Weather = Buffer;
            }

            if (Buffer.SubString(0,11) == "Temperature")
            {
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0,Buffer.Length() -10);
                Temperature = Buffer;
            }

            if (Buffer.SubString(0,9) == "Dew Point")
            {
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0,Buffer.Length() -10);
                DewPoint = Buffer;
            }

            if (Buffer.SubString(0,17) == "Altimeter Setting")
            {
                Buffer = Buffer.SubString(18,Buffer.Length()-17);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0,Buffer.Length() -4);
                AltSetting = Buffer;
            }

            if (Buffer.SubString(0,7) == "Cloud 1")
            {
                //Get the cloud data and store it.
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                ThisCloudData = Buffer;
                //Get cloud 2
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                Buffer = "&" + Buffer;
                ThisCloudData += Buffer;
                //Get cloud 3
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                Buffer = "&" + Buffer;
                ThisCloudData += Buffer;
                //Get cloud 4
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(16,Buffer.Length()-15);
                Buffer = Buffer.Trim();
                Buffer = "&" + Buffer;
                ThisCloudData += Buffer;
            }

            if (Buffer.SubString(0, 8) == "RVR DATA")
            {
                Buffer = Buffer.SubString(30,Buffer.Length()-29);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0, Buffer.Length()-6);

                if (Buffer.SubString(0,2) == "PS")
                rvr_start = "10000";
                else
                rvr_start = Buffer;

                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();

                Buffer = Buffer.SubString(11,Buffer.Length()-10);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0, Buffer.Length()-6);

                if (Buffer.SubString(0,2) == "PS")
                rvr_mid = "10000";
                else
                rvr_mid = Buffer;

                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();

                Buffer = Buffer.SubString(11,Buffer.Length()-10);
                Buffer = Buffer.Trim();
                Buffer = Buffer.SubString(0, Buffer.Length()-6);

                if (Buffer.SubString(0,2) == "PS")
                rvr_stop = "10000";
                else
                rvr_stop = Buffer;

            }


            if (Buffer == "UPPER WIND DATA FOR AREA                     BACKGROUND")
            {
                AreaName = "BACKGROUND";
                while (TempBuffer != "99000")
                {
                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();

                    if (Buffer.SubString(0,10) == "Surface TO")
                    {
                        UpperWindData = Buffer;
                        //while not the end of the wind data....
                        while (TempBuffer != "99000")
                        {
                            input.getline(buf, sizeof(buf));
                            Buffer = buf;
                            Buffer = Buffer.Trim();

                            if (Buffer.SubString(10,5) == "99000")
                            TempBuffer = "99000";

                            //Update the data in the UpperWindData.
                            UpperWindData += Buffer;
                        }
                    }
                }
                TempBuffer = NULL;
            }
            input.getline(buf, sizeof(buf));
            Buffer = buf;
            Buffer = Buffer.Trim();
        }

        while (Buffer != "WEATHER DATA" && Buffer.SubString(0,17) != "RT CALLS DATA FOR")
        {
            input.getline(buf, sizeof(buf));
            Buffer = buf;
            Buffer = Buffer.Trim();
            //Get the file name for this WindData.
            if (Buffer.SubString(0,4) == "PAGE")
            {

                //find out where in the line the File name is.
                int FilePos;
                int OldFile;
                String ThisFileName;

                //See if the same file is needed.
                OldFile = Buffer.Pos(FileName);

                if (OldFile == 0)
                {
                    output.close();
                    FilePos = Buffer.Pos(AirspaceFileName);
                    //trim off the data before the file name.

                    Buffer = Buffer.SubString(FilePos +(AirspaceFileName.Length()+1),Buffer.Length()-(FilePos+AirspaceFileName.Length()));

                    //Set up a counter
                    i = 1;
                    while (Buffer[i] != '.')
                    {
                        i++;
                    }

                    //Get the data.
                    FileName = Buffer.SubString(0,i-1);

                    ThisFileName = FileName + ".daw";
                    //open output file.
                    output.open(ThisFileName.c_str());

                    //Show the current file being processed.
                    ConvertDataForm->CurrentTextLabel->Repaint();
                    ConvertDataForm->Edit1->Text = ThisFileName;
                    ConvertDataForm->Edit1->Repaint();

                    //Output the data into the new file.
                    output<<"WN "<<AreaName.c_str()<<endl;
                    output<<"PS "<<AltSetting.c_str()<<endl;
                    output<<"DW "<<DewPoint.c_str()<<endl;
                    output<<"GD "<<GustDirection.c_str()<<endl;
                    output<<"GV "<<GustSpeed.c_str()<<endl;
                    output<<"SW "<<SurfaceWind.c_str()<<endl;
                    output<<"ST "<<Temperature.c_str()<<endl;
                    output<<"SV "<<Visibility.c_str()<<endl;
                    output<<"CW "<<Weather.c_str()<<endl;

                    //Split up and output the cloud data.
                    //Cloud layer data comes in groups of 4 layers. The data is in the
                    //form '2/1700' & on the following line '5/2300'...
                    //The data is to be changed in to the following format.
                    //CL 2 1700 2300
                    //CL 5 2300 3300 (if the next line of data is NULL, then add 1000 to
                    //the base level to give the upper level).
                    //See if the first Cloud level is valid.
                    CloudData = "";
                    while (ThisCloudData != NULL)
                    {

                        if (ThisCloudData.SubString(0,1) != "0")
                        {
                            //Set up a counter
                            i = 1;
                            while (ThisCloudData[i] != '/')
                            {
                                i++;
                            }

                            //Get the data.
                            CloudGrade = ThisCloudData.SubString(0,i-1);

                            //Trim off the used chars.
                            ThisCloudData = ThisCloudData.SubString(i+1,ThisCloudData.Length()-i);
                            ThisCloudData = ThisCloudData.Trim();

                            //Get the level data to go with the CloudGrade.
                            //Set up a counter
                            i = 1;
                            while (ThisCloudData[i] != '&')
                            {
                                i++;
                            }

                            //Get the data.
                            CloudLevel = ThisCloudData.SubString(0,i-1);

                            //Trim off the used chars.
                            ThisCloudData = ThisCloudData.SubString(i+1,ThisCloudData.Length()-i);
                            ThisCloudData = ThisCloudData.Trim();

                            //Add the data to the output variable.
                            CloudData = CloudGrade + " " + CloudLevel.ToIntDef(0) + " ";


                            //See if the next part of cloud data is 0 or NULL,
                            if (ThisCloudData.SubString(0,1) == "0" || ThisCloudData == "")
                            {
                                //Add the fist bit of cloud data.
                                CloudData += (CloudLevel.ToIntDef(0) + 1000);
                                ThisCloudData = NULL;
                                //Ouptput each line of data.
                                output<<"WC "<<CloudData.c_str()<<endl;
                            }


                            else //get the next CloudLevel.
                            {
                                NextLevel = ThisCloudData.SubString(3,5);
                                CloudData += NextLevel.ToIntDef(0);
                                output<<"WC "<<CloudData.c_str()<<endl;
                            }

                        }
                        else //data is null
                        ThisCloudData = NULL;
                        //and therefore no output.

                    }//end of cloud data.

                    output<<"RV "<<rvr_start.c_str()<<endl;
                    output<<"RV "<<rvr_mid.c_str()<<endl;
                    output<<"RV "<<rvr_stop.c_str()<<endl;
                    for (int x = 0; x < 10; x++)
                    {
                        String  LowLev,
                        HighLev,
                        tempWindLayer;
                        int     i=1;

                        if (UpperWindData.SubString(0,7) == "Surface")
                        {
                            //The first lay of data should read Surface To X, the line
                            //needs to read 'Half X' X.

                            //Trim off 'Surface TO'
                            UpperWindData = UpperWindData.SubString(11,UpperWindData.Length()-10);
                            UpperWindData = UpperWindData.Trim();


                            ThisWindData = UpperWindData.SubString(0,5);

                            tempWindLayer = (ThisWindData.ToIntDef(0))/2;

                            if (tempWindLayer.Length() < 5)
                            {
                                i = tempWindLayer.Length();
                                while (i != 5)
                                {
                                    tempWindLayer = "0"+tempWindLayer;
                                    i++;
                                }
                                i=1;
                            }

                            ThisWindData = tempWindLayer + " " + ThisWindData;

                            UpperWindData = UpperWindData.SubString(6,UpperWindData.Length()-5);
                            UpperWindData = UpperWindData.Trim();

                            ThisWindData = UpperWindData.SubString(0,7) +" "+ ThisWindData;
                            UpperWindData = UpperWindData.SubString(8,UpperWindData.Length()-7);

                            output<<"WD "<<ThisWindData.c_str()<<endl;
                        }

                        else
                        {
                            ThisWindData =  UpperWindData.SubString(0,14);

                            //Find and Remove the 'TO' in the height lev data.
                            while (ThisWindData.SubString(i,2) != "TO")
                            {
                                i++;
                            }

                            //Store the LowLev.
                            LowLev = ThisWindData.SubString(0,i-2);

                            //Trim off the level and the TO.
                            ThisWindData = ThisWindData.SubString(i+2 , ThisWindData.Length()-(i+1));
                            ThisWindData = ThisWindData.Trim();

                            HighLev = ThisWindData;

                            //Trim off the height data
                            UpperWindData = UpperWindData.SubString(15,UpperWindData.Length()-14);
                            UpperWindData = UpperWindData.Trim();

                            //Get the wind direction and vel.
                            ThisWindData = UpperWindData.SubString(0,7) + " " + LowLev + " " + HighLev;
                            UpperWindData = UpperWindData.SubString(8,UpperWindData.Length()-7);

                            output<<"WD "<<ThisWindData.c_str()<<endl;
                        }

                    }
                }
            }


            if (Buffer.SubString(0,15) == "RUNWAYS IN USE:")
            {
                //Display a Record ID
                output<<"IU "<<endl;
                input.getline(buf, sizeof(buf));
                Buffer = buf;
                Buffer = Buffer.Trim();
                while (Buffer != "")
                {
                    //Set up a counter
                    i = 1;
                    while (Buffer[i] != ' ')
                    {
                        i++;
                    }

                    //Get the data.
                    ThisRunWay = Buffer.SubString(0,i-1);

                    //Trim off the used chars.
                    Buffer = Buffer.SubString(i+1,Buffer.Length()-i);
                    Buffer = Buffer.Trim();

                    //Set up a counter
                    i = 1;
                    while (Buffer[i] != ' ')
                    {
                        i++;
                    }

                    //Get the data.
                    ThisRunWay += " " + Buffer.SubString(0,i-1);

                    //Trim off the used chars.
                    Buffer = Buffer.SubString(i+1,Buffer.Length()-i);
                    Buffer = Buffer.Trim();

                    ThisRunWay += " " + Buffer;

                    output<<"WR "<<ThisRunWay.c_str()<<endl;

                    input.getline(buf, sizeof(buf));
                    Buffer = buf;
                    Buffer = Buffer.Trim();
                }
            }
        }
    }
}
output.close();

input.close();
ConvertDataForm->Label->Visible = True;
}//End of procedure.


//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void GetLatLong(String Buffer)
{

int i = 1;
String  Degrees,
Minutes,
Letter;


while (Buffer[i] != ':')
{
    i++;
}

Degrees = Buffer.SubString(0,i-1);
Buffer = Buffer.SubString(i+1, Buffer.Length() -i);
Minutes = Buffer;
Letter = Buffer [Buffer.Length()];
Minutes = Minutes.SubString(0,Minutes.Length() -3);
Minutes += Letter;

if (Minutes[6] == 'N'||Minutes[6] == 'S')

Latitude = Degrees + Minutes;
else
Longitude = Degrees + Minutes;
}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertRouteElement (String Buffer, String RunwayID)
{
String  ThisName;

int     i=1;

//Trim off the first 13 chars.
//Buffer = Buffer.SubString(14,Buffer.Length()-13);

//Sort out if the Data line is for an Identifying Fix.
if (Buffer.SubString(14,11) == "Identifying")
{
    //Trim off the first 13 chars.
    Buffer = Buffer.SubString(14,Buffer.Length()-13);
    ConvertIdentifyingFix (Buffer);
}//end if Identifying....


//Sort out if the Data line is for an Fly Direct to....
if (Buffer.SubString(14,13) == "Fly Direct To")
{
    //Test to see if this fly to is part of a transition.
    //Trim off the first 3 chars.
    Buffer = Buffer.SubString(4,Buffer.Length()-3);
    Buffer = Buffer.Trim();

    //See if the following section of text is the same as the current value of
    //FixName.
    while (Buffer[i] != ' ')
    {
        i++;
    }

    //Get the data.
    ThisName = Buffer.SubString(0,i-1);
    if (ThisName == FixName)
    {
        ThisName = " &IF " + FixName;
    }
    //Trim off the next 10 chars.
    Buffer = Buffer.SubString(10,Buffer.Length()-9);

    ConvertFlyDirectTo (Buffer);

    if (ThisName.SubString(0,4) == " &IF")
    {
        RouteElementData += ThisName;
    }
}//end if == Fly Direct To...

//See if this data is A Hold At [Fix]
if (Buffer.SubString(14,4) == "Hold")
{
    //Trim off the first 13 chars.
    Buffer = Buffer.SubString(14,Buffer.Length()-13);
    ConvertHoldAt (Buffer);
}

//See if this data is a Fly From....
if (Buffer.SubString(14,8) == "Fly From")
{
    //Trim off the first 13 chars.
    Buffer = Buffer.SubString(14,Buffer.Length()-13);
    ConvertFlyFrom (Buffer, RunwayID);
}

//See if this data is a Track....
if (Buffer.SubString(14,5) == "Track")
{
    //Trim off the first 13 chars.
    Buffer = Buffer.SubString(14,Buffer.Length()-13);
    ConvertTrack (Buffer);
}

//See if this data is a Heading....
if (Buffer.SubString(14,7) == "Heading")
{
    //Trim off the first 13 chars.
    Buffer = Buffer.SubString(14,Buffer.Length()-13);
    ConvertHeading (Buffer);
}

//See if this data is a Fly Direct From....
if (Buffer.SubString(14,15) == "Fly Direct From")
{
    //Trim off the first 13 chars.
    Buffer = Buffer.SubString(14,Buffer.Length()-13);
    ConvertFlyDirectFrom (Buffer, RunwayID);
}


}// End of Function.

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertIdentifyingFix (String Buffer)
{
//Simple function to get the fix Name and output the data.
Buffer = Buffer.SubString(19,Buffer.Length()-18);
Buffer = Buffer.Trim();
//If the last char is a full stop, then add all but the full stop to the
//output, else, add all of the buffer to the output.
if (Buffer.SubString(Buffer.Length(),1) == ".")
{
    FixName = Buffer.SubString(0,Buffer.Length() -1);
    RouteElementData = "IF " + FixName;
}
else
{
    FixName = Buffer;
    RouteElementData = "IF " + FixName;
}
}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertFlyDirectTo (String Buffer)
{
String  ToOrFrom;//,
// FixName;

int     i = 1;

ToOrFrom = "T";
Buffer = Buffer.SubString(15,Buffer.Length()-14);
Buffer = Buffer.Trim();
// Get the Fix Name
while (Buffer[i] != '.' && Buffer.SubString(i,2) != " O" && Buffer[i] != '/')
{
    i++;
}

//Store the FixName.
FixName = Buffer.SubString(0,i-1);

//Start to build up the output for this line of data.
RouteElementData = "DF " + FixName;

//Trim off the FixName.
Buffer = Buffer.SubString(i , Buffer.Length()-(i-1));

//If there is data remaining on the line then....
if (Buffer != ".")
{
    if (Buffer.SubString(0,1) == "/")
    //This data is of a Distance Terminator.
    {
        ConvertDistanceTerminator (Buffer, FixName, ToOrFrom);
        Buffer = TempBuffer;
    }

    //See if the additional data is "Or Height Terminator" (Or 600 Ft. or Or 60 )
    if (Buffer.SubString(2,2) == "Or" || Buffer.SubString(0,2) == "Or")
    {
        ConvertHeightTerminator (Buffer);
    }// End Flight level......

}//end if there is more data.
}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertFlyFrom (String Buffer, String RunwayID)
{
String  TrackOrHeading,
BearingValue,
FixName,
ToOrFrom,
AF_Runway;

int     i = 1;

//Set TempBuffer to Null.
TempBuffer = NULL;

//Trim off the Runway
Buffer = Buffer.SubString(9,Buffer.Length()-8);
Buffer = Buffer.Trim();

if (Buffer.SubString(0,10) == "The Runway")
{
    //Start to store the data for output.
    RouteElementData = "RC " + RunwayID;

    //Trim off the "The Runway"
    Buffer = Buffer.SubString(11,Buffer.Length()-10);
    Buffer = Buffer.Trim();

    if (Buffer.SubString(0,1) == "T")
    {
        //Track data
        TrackOrHeading = "T";

        //Trim off the Track.
        Buffer = Buffer.SubString(6,Buffer.Length()-5);
        Buffer = Buffer.Trim();
    }

    else
    {
        //Heading data
        TrackOrHeading = "H";

        //Trim off the Heading.
        Buffer = Buffer.SubString(8,Buffer.Length()-7);
        Buffer = Buffer.Trim();
    }


    //Read in the bearing reading.
    while (Buffer[i] != 'ø')
    {
        i++;
    }

    //Store the reading.
    BearingValue = Buffer.SubString(0,i-1);

    //Trim off the heading value.
    Buffer = Buffer.SubString(i+1 , Buffer.Length()-(i));
    Buffer = Buffer.Trim();

    //Get and store the value for the ToOrFrom variable.
    if (Buffer.SubString(0,1) == "T")
    {
        //Trim off To
        Buffer = Buffer.SubString(3, Buffer.Length()-2);
        Buffer = Buffer.Trim();
        ToOrFrom = "T";
    }
    else
    {
        Buffer = Buffer.SubString(5, Buffer.Length()-4);
        Buffer = Buffer.Trim();
        ToOrFrom = "F";
    }

    //Add the data to the output line.
    RouteElementData += " " + TrackOrHeading + BearingValue;

    //Reset the counter to 1, and then get the fix-name.
    i=1;

    int pos_ft = Buffer.Pos("Ft");

    if (pos_ft == 0)
    {
        while (Buffer[i] != '/' && Buffer.SubString(i,2) != " O")
        {
            i++;
        }

        //Get the fix name.
        FixName = Buffer.SubString(0,i-1);

        //Trim off the fix name.
        Buffer = Buffer.SubString(i , Buffer.Length()-(i-1));
        Buffer = Buffer.Trim();

        if (Buffer.SubString(0,1) == "/")
        {
            //Then this has a distance or Direction Terminator.

            //Reset the counter to 1,
            i=1;
            while (Buffer[i] != 'N' && Buffer[i] != 'ø')
            {
                i++;
            }

            //If buffer[i] = N, then this is a distance terminator.
            if (Buffer[i] == 'N')
            {
                ConvertDistanceTerminator (Buffer, FixName, ToOrFrom);
                Buffer = TempBuffer;
            }
            else
            {
                ConvertRadialTerminator (Buffer, ToOrFrom, FixName);
                Buffer = TempBuffer;
            }
        }//end if =/.

        //See if the additional data is "Or Height Terminator" (Or 600 Ft. or Or 60 )
        if (Buffer.SubString(2,2) == "Or" || Buffer.SubString(0,2) == "Or")
        {
            ConvertHeightTerminator (Buffer);
            Buffer = TempBuffer;
        }// End Flight level......
    }
    else
    {
        //get the level terminator.
        String level = Buffer.SubString(0, pos_ft-2);
        level = level.Trim();
        level = level.SubString(0,level.Length()-2);

        //format the level.
        level = FormatFloat("000", level.ToDouble());
        level = " &LT A"+level;
        RouteElementData = RouteElementData+level;
    }
}
}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertHoldAt (String Buffer)
{
//Set up the counter.
int     i = 1;


//Trim off the Hold At
Buffer = Buffer.SubString(8,Buffer.Length()-7);
Buffer = Buffer.Trim();

// Get the Fix Name
while (Buffer[i] != 'U')  //others may be added for other types of Hold At Data
//&& Buffer.SubString(i,2) != " O" && Buffer[i] != '/')
{
    i++;
}

//Store the FixName.
FixName = Buffer.SubString(0,i-1);

//Trim off the FixName.
Buffer = Buffer.SubString(i , Buffer.Length()-(i-1));

//If the is data remaining on the line is....
if (Buffer.SubString(0,24) == "Until Manual Termination")
{
    RouteElementData = "HM " + FixName;
}//end if there is more data.
/*
if (Buffer.SubString(0,24) == "Until Altitude Termination")
{
    RouteElementData = "HA " + FixName;
}//end if there is more data.

if (Buffer.SubString(0,24) == "One Complete Pattern")
{
    RouteElementData = "HF " + FixName;
}//end if there is more data.
*/

}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertTrack (String Buffer)
{
String  Bearing;

int     i = 1;

//Trim the first word (Track).
Buffer = Buffer.SubString(6,Buffer.Length() -5);
Buffer = Buffer.Trim();

//Get the Bearing
while (Buffer[i] != 'ø')
{
    i++;
}
//Store the bearing, and trim off the last char...
Bearing = Buffer.SubString(0,i-1);

//Trim off the Bearing from the buffer.
Buffer = Buffer.SubString(i+1,Buffer.Length()-i);
Buffer = Buffer.Trim();

//See how the heading is terminated.
if (Buffer.SubString(0,21) == "To Manual Termination")
{
    RouteElementData = "FM T" + Bearing + " " + FixName;
}
//Others may be added here for different types of terminators

}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertHeading (String Buffer)
{
String  Bearing,
FixName;

int     i = 1;

//Trim the first word (Heading).
Buffer = Buffer.SubString(8,Buffer.Length() -7);
Buffer = Buffer.Trim();

//Get the Bearing
while (Buffer[i] != 'ø')
{
    i++;
}
//Store the bearing, and trim off the last char...
Bearing = Buffer.SubString(0,i-1);

//Trim off the Bearing from the buffer.
Buffer = Buffer.SubString(i+1,Buffer.Length()-i);
Buffer = Buffer.Trim();

//See how the heading is terminated.
if (Buffer.SubString(0,21) == "To Manual Termination")
{
    RouteElementData = "VM " + Bearing;
}

if (Buffer.SubString(0,2) == "To" && Buffer.SubString(8,1) == "/")
{
    RouteElementData = "VM " + Bearing + "&BT ";
    //Trim off the To, and get the Fix name.
    Buffer = Buffer.SubString(3,Buffer.Length()-2);
    Buffer = Buffer.Trim();

    //set i to 1.
    i=1;
    while (Buffer[i] != '/')
    {
        i++;
    }

    //Store the fix name, and trim off the last char...
    FixName = Buffer.SubString(0,i-1);

    //Trim off the Bearing from the buffer.
    Buffer = Buffer.SubString(i+1,Buffer.Length()-i);
    Buffer = Buffer.Trim();

    //update the route data.
    RouteElementData += FixName;

    //set i to 1.
    i=1;
    while (Buffer[i] != 'ø')
    {
        i++;
    }

    //Store the bearing, and trim off the last char...
    Bearing = Buffer.SubString(0,i-1);

    //update the route data.
    RouteElementData += " " + Bearing;
}
if (Buffer.SubString(0,4) == "From")
{
    //then this is a distance terminator from a fix. eg. Heading 135ø From BGN/12.0 Nm. &DT STNA 0.5 T
    Buffer = Buffer.SubString(6, Buffer.Length()-5);

    int pos_slash = Buffer.Pos("/");
    String fix_name = Buffer.SubString(0, pos_slash-1);
    Buffer = Buffer.SubString(pos_slash+1, Buffer.Length()-pos_slash);

    int pos_space = Buffer.Pos(" ");
    String distance = Buffer.SubString(0, pos_space-1);
    Buffer = Buffer.SubString(pos_space+1, Buffer.Length()-pos_space);

    RouteElementData = "VM " + Bearing +" &DT "+fix_name + " "+ distance+ " F";
}
//Others may be added here for different types of terminators

}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertFlyDirectFrom (String Buffer, String RunwayID)
{
int     i = 1;

String  FixName;
//Only one example of this at present...F D F [The Runway] To [Fix]


//Trim off the Fly Direct From.
Buffer = Buffer.SubString(16,Buffer.Length()-15);
Buffer = Buffer.Trim();

//See if next part of the buffer is an Runway.
if (Buffer.SubString(0,10) == "The Runway")
{
    //Trim off the The Runway.
    Buffer = Buffer.SubString(11,Buffer.Length()-10);
    Buffer = Buffer.Trim();

    //If next word is To, then it is a fly to fix.
    if (Buffer.SubString(0,2) == "To")
    {
        //Trim off the The Runway.
        Buffer = Buffer.SubString(3,Buffer.Length()-2);
        Buffer = Buffer.Trim();

        //Get the FixName
        while (Buffer[i] != '.')
        {
            i++;
        }

        //Store the FixName, and trim off the last char...
        FixName = Buffer.SubString(0,i-1);

        RouteElementData = "RF " + RunwayID + " " + FixName;
    }
}
}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertHeightTerminator (String Buffer)
{
String  TempRouteElementData,
LevelTerm;

int     i,
FtPos;

TempRouteElementData = " &LT ";
//Trim off the "Or"
Buffer = Buffer.SubString(4,Buffer.Length()-3);
Buffer = Buffer.Trim();

if (Buffer.SubString(0,1) != "")
{


    FtPos = Buffer.Pos("Ft");

    if (FtPos != 0)
    //This level data is a Alt type.
    {
        //reset the counter (i) to 1.
        i=1;
        while (Buffer[i] != 'F')
        {
            i++;
        }

        //Trim off the last 4 chars...
        LevelTerm = Buffer.SubString(0,i++-4);

        //Level Term now holds the value of the alt. eg 600 Ft becomes 06.
        //test to see if a 0 needs to be added.
        if (LevelTerm.Length() == 2)
        {
            LevelTerm = "A0" + LevelTerm;
            RouteElementData += TempRouteElementData + LevelTerm;
        }
        if (LevelTerm.Length() == 1)
        {
            LevelTerm = "A00" + LevelTerm;
            RouteElementData += TempRouteElementData + LevelTerm;
        }
    }
    else
    //This level data is a Flight Level Type.
    {
        //All that is in the buffer is the F.
        TempRouteElementData += "F" + Buffer;
        RouteElementData += TempRouteElementData;
    }

}//End if

//Return any data left over.
TempBuffer = Buffer;

}//End Function

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertDistanceTerminator (String Buffer, String FixName, String ToOrFrom)
{
String  TempRouteElementData,
DistTerm;

int     i = 1;


//Trim the first char off '/'.
Buffer = Buffer.SubString(2,Buffer.Length() -1);

//The data type is Fly Direct To STNA/0.5 Nm, it could also be followed by a
//Flight level terminator.
TempRouteElementData = "&DT " + FixName + " ";

//Get the Distance
while (Buffer[i] != 'N')
{
    i++;
}
//Trim off the last 2 chars...
DistTerm = Buffer.SubString(0,i++-2);
//Add the extra data.
TempRouteElementData += DistTerm + " " + ToOrFrom;

//Since the data is valid, add the extra string to the existing Data.
RouteElementData += TempRouteElementData;


//Trim off the used chars from the buffer.
Buffer = Buffer.SubString(i+2,Buffer.Length()-i+1);
Buffer = Buffer.Trim();

//Return any data left over.
TempBuffer = Buffer;
}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertRadialTerminator (String Buffer, String ToOrFrom, String FixName)
{
String  TempRouteElementData,
RadialTerm;

int     i = 1;


//Trim the first char off '/'.
Buffer = Buffer.SubString(2,Buffer.Length() -1);

//
TempRouteElementData = "&BT " + FixName + " ";

//Get the Bearing
while (Buffer[i] != 'ø')
{
    i++;
}
//Store the bearing, and trim off the last char...
RadialTerm = Buffer.SubString(0,i-1);
//Add the extra data.
TempRouteElementData = TempRouteElementData + RadialTerm;// + " " + ToOrFrom;

//Since the data is valid, add the extra string to the existing Data.
RouteElementData += TempRouteElementData;

//Trim off the used chars from the buffer.
Buffer = Buffer.SubString(i+1,Buffer.Length()-i);
Buffer = Buffer.Trim();

//Return any data left over.
TempBuffer = Buffer;
}

//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------

void ConvertAirportName (String Buffer)
{
String  BeginLine,
EndLine;

int     PosOfAirport;

PosOfAirport = Buffer.Pos("TRSN");
if (PosOfAirport != 0)
{
    if (Buffer.Length() == 4)
    {
        Buffer = "TRZN";
    }
    else //This is route data.
    {
        BeginLine = Buffer.SubString(0,PosOfAirport -1);
        Buffer = Buffer.SubString(PosOfAirport +4,Buffer.Length()-(PosOfAirport +3));
        EndLine = Buffer;
        Buffer = "TRZN";

        Buffer = BeginLine + Buffer + EndLine;
    }
}
PosOfAirport = Buffer.Pos("TRNN");
if (PosOfAirport != 0)
{
    if (Buffer.Length() == 4)
    {
        Buffer = "EHHO";
    }
    else //This is route data.
    {
        BeginLine = Buffer.SubString(0,PosOfAirport -1);
        Buffer = Buffer.SubString(PosOfAirport +4,Buffer.Length()-(PosOfAirport +3));
        EndLine = Buffer;
        Buffer = "EHHO";

        Buffer = BeginLine + Buffer + EndLine;
    }
}
PosOfAirport = Buffer.Pos("TRME");
if (PosOfAirport != 0)
{
    if (Buffer.Length() == 4)
    {
        Buffer = "EHTE";
    }
    else //This is route data.
    {
        BeginLine = Buffer.SubString(0,PosOfAirport -1);
        Buffer = Buffer.SubString(PosOfAirport +4,Buffer.Length()-(PosOfAirport +3));
        EndLine = Buffer;
        Buffer = "EHTE";

        Buffer = BeginLine + Buffer + EndLine;
    }
}
PosOfAirport = Buffer.Pos("TRMB");
if (PosOfAirport != 0)
{
    if (Buffer.Length() == 4)
    {
        Buffer = "EHDL";
    }
    else //This is route data.
    {
        BeginLine = Buffer.SubString(0,PosOfAirport -1);
        Buffer = Buffer.SubString(PosOfAirport +4,Buffer.Length()-(PosOfAirport +3));
        EndLine = Buffer;
        Buffer = "EHDL";

        Buffer = BeginLine + Buffer + EndLine;
    }
}
PosOfAirport = Buffer.Pos("TRBP");
if (PosOfAirport != 0)
{
    if (Buffer.Length() == 4)
    {
        Buffer = "EWDR";
    }
    else //This is route data.
    {
        BeginLine = Buffer.SubString(0,PosOfAirport -1);
        Buffer = Buffer.SubString(PosOfAirport +4,Buffer.Length()-(PosOfAirport +3));
        EndLine = Buffer;
        Buffer = "EWDR";

        Buffer = BeginLine + Buffer + EndLine;
    }
}
PosOfAirport = Buffer.Pos("TRLS");
if (PosOfAirport != 0)
{
    if (Buffer.Length() == 4)
    {
        Buffer = "EWLE";
    }
    else //This is route data.
    {
        BeginLine = Buffer.SubString(0,PosOfAirport -1);
        Buffer = Buffer.SubString(PosOfAirport +4,Buffer.Length()-(PosOfAirport +3));
        EndLine = Buffer;
        Buffer = "EWLE";

        Buffer = BeginLine + Buffer + EndLine;
    }
}
PosOfAirport = Buffer.Pos("TRNN");
if (PosOfAirport != 0)
{
    if (Buffer.Length() == 4)
    {
        Buffer = "EHHO";
    }
    else //This is route data.
    {
        BeginLine = Buffer.SubString(0,PosOfAirport -1);
        Buffer = Buffer.SubString(PosOfAirport +4,Buffer.Length()-(PosOfAirport +3));
        EndLine = Buffer;
        Buffer = "EHHO";

        Buffer = BeginLine + Buffer + EndLine;
    }
}

TempBuffer = Buffer;
}
