//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DrawMeshSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDrawMeshForm *DrawMeshForm;
//---------------------------------------------------------------------------

__fastcall TDrawMeshForm::TDrawMeshForm(TComponent* Owner) : TForm(Owner)
{
    SetData();
}
//---------------------------------------------------------------------------

void __fastcall TDrawMeshForm::FormDestroy(TObject *Sender)
{
    ClearData();
}
//---------------------------------------------------------------------------

void TDrawMeshForm::SetData()
{
    m_bFirst = true;
    m_iCurrentPoint = 0; //we want to close the object after user has finished

    m_tPairsHeader = new PairPoints;
    m_tPairsHeader->Prev = NULL;
    m_tPairsHeader->Next = NULL;
}
// -----------------------------------------------------------------------------

void TDrawMeshForm::ClearData()
{
    PairPoints *ptDeletePair = m_tPairsHeader;
    PairPoints *ptPairPointer = ptDeletePair;

    while(ptPairPointer)
    {
        ptPairPointer = ptPairPointer->Next;

        ptDeletePair->Prev = NULL;
        ptDeletePair->Next = NULL;
        delete ptDeletePair;
        ptDeletePair = NULL;

        ptDeletePair = ptPairPointer;
    }
    m_tPairsHeader = NULL;
}
// -----------------------------------------------------------------------------

void __fastcall TDrawMeshForm::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(m_bFirst)
    {
        Canvas->MoveTo(X, Y);
        m_bFirst = false;
    }

    if(m_iCurrentPoint < MAX_POINT_COUNT)
    {
        Canvas->LineTo(X, Y);

        aPoints[m_iCurrentPoint].x = X;
        aPoints[m_iCurrentPoint].y = Y;
        m_iCurrentPoint++;
    }
}
//---------------------------------------------------------------------------

void __fastcall TDrawMeshForm::CreateMeshBTNClick(TObject *Sender)
{
    CloseObject();

    CreateMesh();

    ClearData();
    SetData();
}
//---------------------------------------------------------------------------

bool TDrawMeshForm::CloseObject()
{
//    aPoints[m_iCurrentPoint].x = aPoints[0].x;
//    aPoints[m_iCurrentPoint].y = aPoints[0].y;

    Canvas->LineTo(aPoints[0].x, aPoints[0].y);

    return true;
}
// -----------------------------------------------------------------------------

void TDrawMeshForm::ShowProgress(TColor color)
{
    Canvas->Pen->Color = color;

    PairPoints *tLoopPairs = m_tPairsHeader;
    while(tLoopPairs)
    {
        Canvas->MoveTo(tLoopPairs->startPoint.x, tLoopPairs->startPoint.y);
        Canvas->LineTo(tLoopPairs->endPoint.x, tLoopPairs->endPoint.y);

        tLoopPairs = tLoopPairs->Next;
    }
}
//------------------------------------------------------------------------------

bool TDrawMeshForm::CreateMesh()
{
    bool bReturnValue = false;

    bReturnValue = AddAllPointsToEachOther();

    if(bReturnValue)
    {
        bReturnValue = RemoveJoinedPairs();
    }

    ShowProgress(clGreen);

    if(bReturnValue)
    {
        bReturnValue = RemoveVoidPairs();
    }

    ShowProgress(clBlue);

    return bReturnValue;
}
// -----------------------------------------------------------------------------

PairPoints* TDrawMeshForm::CreateNewPairPoint(PairPoints *pPair)
{
    //if this is the 1st point, then use the first
    if(pPair->startPoint.x == 0 || pPair->startPoint.y == 0)
    {
        return m_tPairsHeader;
    }

    //create a new point
    PairPoints *pNewPair = new PairPoints;

    //set the one passed in to point to the new one
    pPair->Next = pNewPair;

    pNewPair->Prev = pPair;

    //return the new one
    return pNewPair;
}
// -----------------------------------------------------------------------------

bool TDrawMeshForm::RemovePairPoint(PairPoints *&ptAPair)
{
    //set the prev PairPoint Next value of what was passed in
    // to point to the next one after this one

    if(ptAPair->Prev == NULL)
    {
        ptAPair->Next->Prev = NULL;
    }
    else
    {
        ptAPair->Prev->Next = ptAPair->Next;
    }

    if(ptAPair->Next == NULL)
    {
        ptAPair->Prev->Next = NULL;
    }
    else
    {
        ptAPair->Next->Prev = ptAPair->Prev;
    }

/*    PairPoints *returnPair = ptAPair;
    if(returnPair->Prev) returnPair = returnPair->Prev;
    else if(returnPair->Next) returnPair = returnPair->Next;
    else returnPair = NULL;*/
    
    //delete this one.
    ptAPair->Next = NULL;
    ptAPair->Prev = NULL;
    delete ptAPair;
    ptAPair = NULL;

    ptAPair = m_tPairsHeader;

    return true;
}
// -----------------------------------------------------------------------------

bool TDrawMeshForm::AddAllPointsToEachOther()
{
    PairPoints *pairs = m_tPairsHeader;

    for (int firstJoin=0; firstJoin<m_iCurrentPoint; firstJoin++)
    {
        //start from one, no need to add the same point
        for (int secondJoin=0; secondJoin<m_iCurrentPoint; secondJoin++)
        {
            if(aPoints[firstJoin].x != aPoints[secondJoin].x
            && aPoints[firstJoin].y != aPoints[secondJoin].y)
            {
              pairs = CreateNewPairPoint(pairs);

              pairs->startPoint.x = aPoints[firstJoin].x;
              pairs->startPoint.y = aPoints[firstJoin].y;

              pairs->endPoint.x = aPoints[secondJoin].x;
              pairs->endPoint.y = aPoints[secondJoin].y;

              Canvas->Pen->Color = clRed;
              Canvas->MoveTo(pairs->startPoint.x, pairs->startPoint.y);
              Canvas->LineTo(pairs->endPoint.x, pairs->endPoint.y);
            }
        }
    }

    return true;
}
// -----------------------------------------------------------------------------

bool TDrawMeshForm::RemoveJoinedPairs()
{
    PairPoints *tRefPairs = m_tPairsHeader;
    PairPoints *tTestPairs = m_tPairsHeader;

    while(tRefPairs)
    {
        while(tTestPairs)
        {
            if(tTestPairs != NULL)
            {
                if(tRefPairs->startPoint.x == tTestPairs->endPoint.x
                && tRefPairs->startPoint.y == tTestPairs->endPoint.y
                && tRefPairs->endPoint.x == tTestPairs->startPoint.x
                && tRefPairs->endPoint.y == tTestPairs->startPoint.y)
                {
                    RemovePairPoint(tTestPairs);
                }
            }
            tTestPairs = tTestPairs->Next;
        }
        tRefPairs = tRefPairs->Next;

        tTestPairs = m_tPairsHeader;
    }
    return true;
}
// -----------------------------------------------------------------------------

bool TDrawMeshForm::RemoveVoidPairs()
{
    //pairs that cross any line

    PairPoints *tTestPair = m_tPairsHeader;

    while(tTestPair)
    {
        if(CrossesLine(tTestPair))
        {
            RemovePairPoint(tTestPair);
        }

        tTestPair = tTestPair->Next;
    }
    
    return true;
}
//------------------------------------------------------------------------------

bool TDrawMeshForm::CrossesLine(PairPoints *&pAPair)
{
/*
                 |
                 |
                 |
          ----------------
                 |
                 |
                 |


*/

    bool bReturnValue = false;

    PairPoints *tTestPair = m_tPairsHeader;

    while(tTestPair && !bReturnValue)
    {
        if((    tTestPair->startPoint.x > pAPair->startPoint.x   && tTestPair->endPoint.x > pAPair->endPoint.x)
        && (    tTestPair->startPoint.y < pAPair->startPoint.y   && tTestPair->endPoint.y > pAPair->endPoint.y))
        /*&& tTestPair->endPoint.x == pAPair->startPoint.x
        && tTestPair->endPoint.y == pAPair->startPoint.y)*/
        {
            bReturnValue = true;
        }

        tTestPair = tTestPair->Next;
    }

    return bReturnValue;
}
//------------------------------------------------------------------------------

