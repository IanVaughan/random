//---------------------------------------------------------------------------
#ifndef GroundVehiclePerformanceEditorSrcH
#define GroundVehiclePerformanceEditorSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGroundVehiclePerformanceEditor : public TForm
{
__published:
    TGroupBox *SpeedGroupBox;
    TGroupBox *GroupBox1;

    TLabel *SlowSpeedLabel;
    TLabel *NormalSpeedLabel;
    TLabel *MaximumSpeedLabel;
    TLabel *AccelerationLabel;
    TLabel *DecelerationLabel;
    TLabel *EmergencyDecelerationLabel;
    TLabel *GroundTypeLabel;
    TEdit *SlowSpeedEdit;
    TEdit *NormalSpeedEdit;
    TEdit *MaximumSpeedEdit;
    TEdit *AccelerationEdit;
    TEdit *DecelerationEdit;
    TEdit *EmergencyDecelerationEdit;
    TComboBox *GroundTypeComboBox;
    TButton *SaveButton;
    TButton *CancelButton;

    TGroupBox *GroupBox2;
    TLabel *LabelName;
    TLabel *TypeLabel;
    TEdit *NameEdit;
    TComboBox *TypeComboBox;
    TGroupBox *MiscDataGroupBox;
    TLabel *TaxiPitchLabel;
    TLabel *MinimumTurnRadiusLabel;
    TEdit *TaxiPitchEdit;
    TEdit *MinimumTurnRadiusEdit;
    TLabel *HiddelTextLabel;
    TPageControl *AirborneDataPageControl;
    TTabSheet *Airbourne;
    TTabSheet *Engine;
    TTabSheet *Pitch;
    TTabSheet *Takeoff;
    TTabSheet *Landing;
    TGroupBox *GroupBox3;
    TLabel *AirbourneType;
    TLabel *VortexWakeCategoryLabel;
    TComboBox *AirborneTypeComboBox;
    TComboBox *VortextWakeCategoryComboBox;
    TCheckBox *CanReverseCheckBox;
    TGroupBox *EngineGroupBox;
    TLabel *EnginePowerUpPeriodLabel;
    TLabel *EngineStartDurationLabel;
    TEdit *EnginePowerUpPeriodEdit;
    TEdit *EngineStartDurationEdit;
    TGroupBox *PitchGroupBox;
    TLabel *RateOfChangePitchLabel;
    TLabel *LevelFlightPitchLabel;
    TLabel *NormalRateOfClimbPitchLabel;
    TLabel *NormalRateOfDecentPitchLabel;
    TLabel *ExpeditedRateOfClimbPitchLabel;
    TLabel *GlidePitchLabel;
    TLabel *ApproachPitchLabel;
    TLabel *FlaplessApproachPitchLabel;
    TLabel *LandingFlarePitchLabel;
    TLabel *TakeoffPitchLabel;
    TEdit *RateOfChangePitchEdit;
    TEdit *LevelFlightPitchEdit;
    TEdit *NormalRateOfClimbPitchEdit;
    TEdit *NormalRateOfDecentPitchEdit;
    TEdit *ExpeditedRateOfClimbPitchEdit;
    TEdit *GlidePitchEdit;
    TEdit *ApproachPitchEdit;
    TEdit *FlaplessApproachPitchEdit;
    TEdit *LandingFlarePitchEdit;
    TEdit *TakeoffPitchEdit;
    TGroupBox *TakeoffGroupBox;
    TLabel *V1SpeedLabel;
    TLabel *RotateSpeedLabel;
    TLabel *TakeoffSpeedLabel;
    TLabel *TakeoffRollDistanceLabel;
    TLabel *TakeoffRollTimeLabel;
    TEdit *V1SpeedEdit;
    TEdit *RotateSpeedEdit;
    TEdit *TakeoffSpeedEdit;
    TEdit *TakeoffRollDistanceEdit;
    TEdit *TakeoffRollTimeEdit;
    TGroupBox *LandingGroupBox;
    TLabel *FlareDecelerationSpeedLabel;
    TLabel *LandingSpeedDistanceLabel;
    TLabel *ThrustReverseOffSpeedLabel;
    TLabel *ThrustReverseDecelerationRateLabel;
    TLabel *LandingDecelerationRateLabel;
    TLabel *RunwayRolloutSpeedLabel;
    TEdit *FlareDecelerationSpeedEdit;
    TEdit *LandingSpeedDistanceEdit;
    TEdit *ThrustReverseOffSpeedEdit;
    TEdit *ThrustReverseDecelerationRateEdit;
    TEdit *LandingDecelerationRateEdit;
    TEdit *RunwayRolloutSpeedEdit;
    TLabel *SecondsLabel1;
    TLabel *SecondsLabel2;
    TEdit *TakeoffProceduresPeriodEdit;
    TLabel *TakeoffProceduresPeriodLabel;
    TLabel *SecondsLabel3;
    TLabel *FlareHeightLabel;
    TEdit *FlareHeightEdit;
    TLabel *RateOfRollLabel;
    TEdit *RateOfRollEdit;
    TLabel *PushbackSpeedLabel;
    TEdit *PushbackEdit;
    TLabel *LandingSpeedLabel;
    TEdit *LandingSpeedEdit;
    TLabel *Label1;
    TLabel *Label2;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall SaveButtonClick(TObject *Sender);
    void __fastcall CancelButtonClick(TObject *Sender);



    
private:

public:
    __fastcall TGroundVehiclePerformanceEditor(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TGroundVehiclePerformanceEditor *GroundVehiclePerformanceEditor;
//---------------------------------------------------------------------------
#endif
