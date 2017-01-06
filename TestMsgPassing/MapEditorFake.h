#ifndef TDLL_H
#define TDLL_H
//---------------------------------------------------------------------------

#ifdef __BUILDING_THE_DLL
#define __EXPORT_TYPE __export
#else
#define __EXPORT_TYPE __import
#endif
// -----------------------------------------------------------------------------

typedef struct
{
    char Name[20];
    char LatLong[30];
}DPBasicData;

typedef struct
{
    TList *test;
}DPFormShowData;
// -----------------------------------------------------------------------------

typedef bool (__closure *CallMeBack)(DPFormShowData*);

void __EXPORT_TYPE RegCallback(CallMeBack method);

void SendMsg(DPFormShowData *df);

#endif TDLL_H
