//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CreatorSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCreator *Creator;
//---------------------------------------------------------------------------

__fastcall TCreator::TCreator(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool TCreator::Create(String dir)
{
    bool bReturnValue = false;
    Show();

    bReturnValue = FindHeaders(dir);

    Hide();
    return bReturnValue;
}
// -----------------------------------------------------------------------------

bool TCreator::FindHeaders(String dir)
{
    TStringList *dirList = new TStringList;

}
// -----------------------------------------------------------------------------

TStringList
{
    TSearchRec sr;

    bool bFound = (FindFirst(dir + "*.h", 0, sr) == 0);

    while (bFound)
    {
        // copy the name
        String exercise = sr.Name.UpperCase();
        // add it to the list
        dirList->Add(exercise);
        // try for the next one
        bFound = (FindNext(sr) == 0);
    }
    FindClose(sr);
}
