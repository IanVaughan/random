//---------------------------------------------------------------------------
#ifndef ReadStripH
#define ReadStripH
//---------------------------------------------------------------------------
class ReadStrip
{
public:
     ReadStrip();
     void openFile(AnsiString, TComboBox*);
     bool __fastcall createStrip(AnsiString, TStringList*, TCanvas*, TPoint);
};

#endif



