//---------------------------------------------------------------------------
#ifndef DrawMeshSrcH
#define DrawMeshSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------

const int MAX_POINT_COUNT = 100;

typedef struct PairPoints
{
    PairPoints *Prev;
    PairPoints *Next;
    POINT startPoint;
    POINT endPoint;
} _PairPoints;

// -----------------------------------------------------------------------------

class TDrawMeshForm : public TForm
{
__published:
    TButton *CreateMeshBTN;
    TMainMenu *MainMenu1;
    TPopupMenu *PopupMenu1;
    TStatusBar *StatusBar1;
    TMenuItem *File1;
    TMenuItem *Exit1;
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall CreateMeshBTNClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);

private:

    PairPoints* CreateNewPairPoint(PairPoints* ptAPair);
    bool RemovePairPoint(PairPoints *&ptAPair);

    void SetData();
    void ClearData();

    void ShowProgress(TColor color);

    bool CloseObject();
    bool CreateMesh();
    bool AddAllPointsToEachOther();
    bool RemoveJoinedPairs();
    bool RemoveVoidPairs();
    bool CrossesLine(PairPoints *&pAPair);

    int m_iCurrentPoint;
    POINT aPoints[MAX_POINT_COUNT];

    PairPoints *m_tPairsHeader;

    bool m_bFirst;
public:
    __fastcall TDrawMeshForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TDrawMeshForm *DrawMeshForm;
//---------------------------------------------------------------------------
#endif
