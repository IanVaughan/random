//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GroundVehiclePerformanceEditorSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGroundVehiclePerformanceEditor *GroundVehiclePerformanceEditor;
//---------------------------------------------------------------------------

__fastcall TGroundVehiclePerformanceEditor::TGroundVehiclePerformanceEditor(TComponent* Owner) : TForm(Owner)
{
    //master vehicle type
    TypeComboBox->Items->Add("Air Vehicle"); //0
    TypeComboBox->Items->Add("Ground Vehicle"); //1

    //vehicle sub-type for Airbourne data
//    AirborneTypeComboBox->Items->Add("Piston"); //0
//    AirborneTypeComboBox->Items->Add("Turbo Prop"); //1
//    AirborneTypeComboBox->Items->Add("Jet"); //2
    AirborneTypeComboBox->Items->Add("Aircraft"); //3
    AirborneTypeComboBox->Items->Add("Helicopter"); //3
//    AirborneTypeComboBox->Items->Add("Glider"); //4
//    AirborneTypeComboBox->Items->Add("Parachute"); //5
//    AirborneTypeComboBox->Items->Add("Balloon"); //6

    //vehicle sub-type for Ground data
    GroundTypeComboBox->Items->Add("Tug"); //0
    GroundTypeComboBox->Items->Add("Snow Plough"); //1
    GroundTypeComboBox->Items->Add("Fire Engine"); //2
    GroundTypeComboBox->Items->Add("Airport Manager"); //3
    GroundTypeComboBox->Items->Add("Other"); //4

/*    ModelComboBox->Items->Add("This list");
    ModelComboBox->Items->Add("will contain");
    ModelComboBox->Items->Add("all of the");
    ModelComboBox->Items->Add("GROUND Vehicles");
    ModelComboBox->Items->Add("that have been saved");
    ModelComboBox->Items->Add("in the");
    ModelComboBox->Items->Add("Vehicle Editor.");
*/
    VortextWakeCategoryComboBox->Items->Add("Light");
    VortextWakeCategoryComboBox->Items->Add("Small");
    VortextWakeCategoryComboBox->Items->Add("Medium");
    VortextWakeCategoryComboBox->Items->Add("Heavy");
}
//---------------------------------------------------------------------------

void __fastcall TGroundVehiclePerformanceEditor::FormShow(TObject *Sender)
{
    NameEdit->Text = "";


    MinimumTurnRadiusEdit->Text = "";//air=7.62m gnd=3.05m
    TaxiPitchEdit->Text = "";

    TypeComboBox->ItemIndex = 0; //select 'air' as default

    GroundTypeComboBox->ItemIndex = 4; //other

    // -----------------------------------------------------------------------------
    //speeds group
    SlowSpeedEdit->Text = "18.52";
    NormalSpeedEdit->Text = "37.04";
    MaximumSpeedEdit->Text = "55.56";

    // -------------------------------------------------------------------------
    //Moveing Group
    AccelerationEdit->Text = "1.28";
    DecelerationEdit->Text = "1.28";
    EmergencyDecelerationEdit->Text = "3.85";

    // -----------------------------------------------------------------------------
    //set default data for airbourne stuff
    // -----------------------------------------------------------------------------
    // Airbourne page

    AirborneTypeComboBox->ItemIndex = 0; //jet

    //which type to use?
//    MediumVortextWakeCategoryComboBoxRadioButton->Checked = true;
    VortextWakeCategoryComboBox->ItemIndex = 2; // medium

    TakeoffProceduresPeriodEdit->Text = "";


    PushbackEdit->Text = "1.25";

    CanReverseCheckBox->Checked = false;

    // -------------------------------------------------------------------------
    // Engine Page
    EngineStartDurationEdit->Text = "60";
    EnginePowerUpPeriodEdit->Text = "10";

    // -------------------------------------------------------------------------
    // Pitch Page

    // -------------------------------------------------------------------------
    // Takeoff Page
    TakeoffProceduresPeriodEdit->Text = "0";

    // -------------------------------------------------------------------------
    // Landing Page

}
//---------------------------------------------------------------------------

void __fastcall TGroundVehiclePerformanceEditor::SaveButtonClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TGroundVehiclePerformanceEditor::CancelButtonClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------




