//---------------------------------------------------------------------------
#ifndef PSortaSrcH
#define PSortaSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <FileCtrl.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TProjectSorta : public TForm
{
__published:
    TFileListBox *othersFLB;
    TFileListBox *projectFLB;
    TNotebook *Notebook1;
    TProgressBar *progressBar;
    TLabel *Label1;
    TTreeView *fileViewTL;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton1;
    TLabel *Label2;
    TMemo *memo;
    TButton *startBTN;
    TButton *cancelBTN;
    TButton *saveOutput;
    TButton *backBTN;
    TLabel *Label3;
    TLabel *Label4;
    void __fastcall startBTNClick(TObject *Sender);
    void __fastcall cancelBTNClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall backBTNClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);

private:
    TStringList* findBPRfiles();
    void addProjectFiles(TStringList*);
    void readDataFromProjectFile(TStringList*, TTreeNode*);

    void groupMatchingFiles();
    bool compareThisNodeWithOthers(TTreeNode*&);

    void updateTree();

    TTreeNode *commonNode;

    TList *deleteNodesList;
    TList *moveNodesList;

public:
    __fastcall TProjectSorta(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TProjectSorta *ProjectSorta;
//---------------------------------------------------------------------------
#endif
