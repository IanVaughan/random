//---------------------------------------------------------------------------
#ifndef GroundVehicleEditorSrcH
#define GroundVehicleEditorSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGroundVehicleEditorForm : public TForm
{
__published:
    TGroupBox *DimensionsGroupBox;
    TGroupBox *WheelsGroupBox;
    TGroupBox *AirGroundExtraDataGroupBox;

    TLabel *NameLabel;
    TLabel *LengthLabel;
    TLabel *WidthLabel;
    TLabel *HeightLabel;
    TLabel *CenterWheelLabel;
    TLabel *WheelBaseLabel;
    TLabel *TowBarLengthLabel;
    TLabel *HoverTaxiHeightLabel;

    TEdit *CentreWheel;
    TEdit *WheelBase;
    TEdit *NameEdit;
    TEdit *LengthEdit;
    TEdit *WidthEdit;
    TEdit *HeightEdit;
    TEdit *TowBarLengthEdit;
    TEdit *HoverTaxiHeightEdit;

    TNotebook *AirGroundExtraDataNotebook;

    TCheckBox *HasArresterHookCheckBox;

    TButton *SaveButton;
    TButton *CancelButton;
    TImage *Image1;
    TLabel *PerformaceGroupLabel;
    TComboBox *PerfRefComboBox;
    TLabel *ModelRefLabel;
    TComboBox *ModelRefComboBox;
    void __fastcall SaveButtonClick(TObject *Sender);
    void __fastcall CancelButtonClick(TObject *Sender);
    void __fastcall AirTypeRadioButtonClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

    void __fastcall GroundTypeRadioButtonClick(TObject *Sender);
private:

public:
    __fastcall TGroundVehicleEditorForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TGroundVehicleEditorForm *GroundVehicleEditorForm;
//---------------------------------------------------------------------------
#endif
