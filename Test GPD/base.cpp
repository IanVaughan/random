//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
#include "GroundPerformanceSrc.h"
GroundPerformanceList *gpl;

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    delete gpl;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
    gpl = new GroundPerformanceList;
    if(!gpl->LoadPerfData("GPD Ex Full.gpd"))
        return;

    int perfCount = gpl->GetPerfCount();
    
    for(int i=0; i< perfCount; i++)
    {
        GroundVehiclePerformance *perfData = gpl->GetPerfByIndex(i);
        if(perfData)
        {
            if(perfData->m_eType == vtAIR)
                airPerfLB->Items->Add(perfData->m_cVehicleName);
            else if(perfData->m_eType == vtGROUND)
                gndPerfLB->Items->Add(perfData->m_cVehicleName);
        }
    }

    int vehCount = gpl->GetVehCount();

    for(int i=0; i< vehCount; i++)
    {
        GroundVehicleData *vehData = gpl->GetVehByIndex(i);

        vehLB->Items->Add(vehData->m_cModelName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::vehLBClick(TObject *Sender)
{
    //unselect all
    airPerfLB->ItemIndex = -1;
    gndPerfLB->ItemIndex = -1;
                
    GroundVehicleData *vehData = gpl->GetVehByIndex(vehLB->ItemIndex);
    //GroundVehiclePerformance *perfData = gpl->GetVehAtIndex(vehLB->ItemIndex);
    //vehLB->ItemIndexGetVehByName(vehLB->Items->Strings[vehLB->ItemIndex]);


    GroundVehiclePerformance *perfData = vehData->m_pGroundVehiclePerformance;

    if(perfData->m_eType == vtAIR)
    {
        String vName = perfData->m_cVehicleName;
        int nIndex = airPerfLB->Items->IndexOf(vName);
        airPerfLB->ItemIndex = nIndex;
    }
    else if(perfData->m_eType == vtGROUND)
    {
        String strName = perfData->m_cVehicleName;
        int nIndex = gndPerfLB->Items->IndexOf(strName);
        gndPerfLB->ItemIndex = nIndex;
    }
}
//---------------------------------------------------------------------------


