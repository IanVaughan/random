//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GroundVehicleEditorSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGroundVehicleEditorForm *GroundVehicleEditorForm;
//---------------------------------------------------------------------------

__fastcall TGroundVehicleEditorForm::TGroundVehicleEditorForm(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TGroundVehicleEditorForm::FormShow(TObject *Sender)
{
    CentreWheel->Text = "";
    WheelBase->Text = "";
    NameEdit->Text = "";
    LengthEdit->Text = "";
    WidthEdit->Text = "";
    HeightEdit->Text = "";
    TowBarLengthEdit->Text = "";
    HoverTaxiHeightEdit->Text = "";

//    TImage *VehicleImage;

//    AirTypeRadioButton->Checked = true;

    AirGroundExtraDataNotebook->ActivePage = 0;

    HasArresterHookCheckBox->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TGroundVehicleEditorForm::SaveButtonClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TGroundVehicleEditorForm::CancelButtonClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TGroundVehicleEditorForm::AirTypeRadioButtonClick(TObject *Sender)
{
    AirGroundExtraDataNotebook->ActivePage = "Air";
}
//---------------------------------------------------------------------------

void __fastcall TGroundVehicleEditorForm::GroundTypeRadioButtonClick(
      TObject *Sender)
{
    AirGroundExtraDataNotebook->ActivePage = "Ground";
}
//---------------------------------------------------------------------------

