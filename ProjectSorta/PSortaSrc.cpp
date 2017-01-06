//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PSortaSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProjectSorta *ProjectSorta;
//---------------------------------------------------------------------------

__fastcall TProjectSorta::TProjectSorta(TComponent* Owner) : TForm(Owner)
{
    deleteNodesList = new TList;
    moveNodesList = new TList;
}
//---------------------------------------------------------------------------

void __fastcall TProjectSorta::FormDestroy(TObject *Sender)
{
    delete deleteNodesList;
    delete moveNodesList;
}
//---------------------------------------------------------------------------

void __fastcall TProjectSorta::FormShow(TObject *Sender)
{
    //goto the projects dir
    bool found = SetCurrentDir("c:\\projects\\best\\source");
    if(!found)
    {
        MessageBox(NULL, "Could not find the Projects Directory!", "Error", MB_OK|MB_ICONERROR);
        return;
    }

    projectFLB->Directory = "c:\\projects\\best\\source";
    othersFLB->Directory = "c:\\projects\\best\\source";

    progressBar->Max = projectFLB->Items->Count;

    //set the correct page
    Notebook1->ActivePage = "Start";

    memo->Clear();

    Label1->Caption = "";
    Label2->Caption = "";
    Label3->Caption = "";
}
//---------------------------------------------------------------------------

//******************************************************************************
//* buttons

void __fastcall TProjectSorta::backBTNClick(TObject *Sender)
{
    if(Notebook1->ActivePage == "Sorta")
    {
        Notebook1->ActivePage = "Start";
        startBTN->Caption = "Next >>";
        backBTN->Enabled = false;
        return;
    }
    else if(Notebook1->ActivePage == "Result")
    {
        Notebook1->ActivePage = "Sorta";
        startBTN->Caption = "Next >>";
        return;
    }
}
//---------------------------------------------------------------------------

void __fastcall TProjectSorta::startBTNClick(TObject *Sender)
{
    static bool sorted = false;

    if(Notebook1->ActivePage == "Start")
    {
        Notebook1->ActivePage = "Sorta";
        if(sorted)
            startBTN->Caption = "Next >>";
        else
            startBTN->Caption = "Start";
        backBTN->Enabled = true;
        return;
    }
    else if(Notebook1->ActivePage == "Sorta")
    {
        if(sorted)
        {
            Notebook1->ActivePage = "Result";
            startBTN->Caption = "Apply";
            backBTN->Enabled = true;
        }
        else
        {
            //disable the buttons
            startBTN->Enabled = false;
            backBTN->Enabled = false;
            cancelBTN->Caption = "Stop";

            memo->Lines->Add("------------------------------- Step 1 -------------------------------");
            Label1->Caption = "Step 1 : Finding Project files...";
            TStringList *result = findBPRfiles();

            memo->Lines->Add("------------------------------- Step 2 -------------------------------");
            Label1->Caption = "Step 2 : Adding Project files from Project files...";
            addProjectFiles(result);

            memo->Lines->Add("------------------------------- Step 3 -------------------------------");
            Label1->Caption = "Step 3 : Searching for duplicate files...";
            groupMatchingFiles();

            memo->Lines->Add("------------------------------- Step 4 -------------------------------");
            Label1->Caption = "Step 4 : Updating Tree...";
            updateTree();


            fileViewTL->FullCollapse();

            startBTN->Enabled = true;
            startBTN->Caption = "Next >>";
            cancelBTN->Caption = "Cancel";

            backBTN->Enabled = true;

            sorted = true;
        }
    }
    else
    {
    }
}
//---------------------------------------------------------------------------

void __fastcall TProjectSorta::cancelBTNClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------





//******************************************************************************
//* private methods

TStringList* TProjectSorta::findBPRfiles()
{
    //list to hold all the .bpr files in
    TStringList *bprFiles = new TStringList;

    //---------------------------------------------------------------------------

    //create a parernt node
    TTreeNode *firstNode = fileViewTL->Items->Add(NULL, "Projects");
    TTreeNode *selectNode = NULL;

    //add the 'common' files node & save the position of the common node
    commonNode = fileViewTL->Items->AddChild(firstNode, "Common Files");

    String addName;
    //get all the files in the dir
    for(int i=0; i < projectFLB->Items->Count; i++)
    {
        //get the item in the file list
        addName = projectFLB->Items->Strings[i];

        //removed the .bpr extension from the name
        addName = addName.Delete(addName.Length()-3, 4);

        //add to the string list
        bprFiles->Add(addName);

        //and add to the Ttree list
        selectNode = fileViewTL->Items->AddChild(firstNode, addName);

        //this auto-scrolls down the tree list box as the items are added
        fileViewTL->Selected = selectNode;

        Label2->Caption = selectNode->Text;
        Label3->Caption = AnsiString(i) +"/"+ AnsiString(projectFLB->Items->Count);
        progressBar->StepIt();
        Refresh();
    }

    //done

    Label1->Caption = "";
    Label3->Caption = "";
    progressBar->Position = 0;

    return bprFiles;
}
//---------------------------------------------------------------------------

void TProjectSorta::addProjectFiles(TStringList *bprList)
{
    progressBar->Max = bprList->Count;

    //read each bpr file
    for(int i=0; i < bprList->Count; i++)
    {
        TStringList *file = new TStringList ;
        file->LoadFromFile(bprList->Strings[i] + ".cpp");

        TTreeNode *addTo = fileViewTL->Items->GetFirstNode();

        //+1 for the common node
        addTo = addTo->Item[i+1];

        readDataFromProjectFile(file, addTo);

        Label3->Caption = AnsiString(i) + "/"+ AnsiString(bprList->Count);
    }

    Label1->Caption = "";
    Label3->Caption = "";
    progressBar->Position = 0;
}
//---------------------------------------------------------------------------

void TProjectSorta::readDataFromProjectFile(TStringList *file, TTreeNode *toNode)
{
    //save all the USE statments into a list    (USEUNIT, USEOBJ, USERC, USELIB, and USEFILE + more)

    //get all the .cpp/.h/.dfm/.res files that match the .cpp in the list
    for(int i=0; i<file->Count; i++)
    {
        String aline = file->Strings[i] ;

        String rest = NULL;

        if(aline.Pos("USEUNIT")>0)
            rest = aline.SubString(10, aline.Length()-10);
        else if(aline.Pos("USEOBJ")>0)
            rest = aline.SubString(9, aline.Length()-9);
        else if(aline.Pos("USELIB")>0)
            rest = aline.SubString(9, aline.Length()-9);
        else if(aline.Pos("USEFILE")>0)
            rest = aline.SubString(10, aline.Length()-10);
        else if(aline.Pos("USERES")>0)
            rest = aline.SubString(9, aline.Length()-9);
        else if(aline.Pos("USEFORM")>0)
            rest = aline.SubString(10, aline.Length()-10);

        if(rest != NULL)
        {
            //strip the string of any rubbish at the end we dont need
            // from the extension onwards
            int dot = rest.Pos(".");

            //if position of dot is small, then we can assume that the file is pathed
            // ie, "..\\..\\Best.cpp". so, ignore path, and get filename
            if(dot < 2)
            {
                //extern PACKAGE System::AnsiString __fastcall ExtractFileName(const System::AnsiString FileName);
                rest = ExtractFileName(rest);

                //redo find the dot test
                dot = rest.Pos(".");
            }

            rest = rest.Delete(dot, rest.Length() - dot+1);

            //safty, if its empty, dont add
            if(rest != "")
            {
                TTreeNode *selectNode = fileViewTL->Items->AddChild(toNode, rest);
                fileViewTL->Selected = selectNode;
            }
        }
    }

    Label2->Caption = toNode->Text;
    progressBar->StepIt();
    Refresh();
}
//---------------------------------------------------------------------------

void TProjectSorta::groupMatchingFiles()
{
    progressBar->Max = fileViewTL->Items->Count;

    TTreeNode *readNode = fileViewTL->Items->GetFirstNode();
    readNode = readNode->Item[2];

    TTreeNode *selectNode = NULL;

    //list adds all the file nodes into a string list for quick sorting
    // then add the project parent node to each stringList item as a Data object
    // so when sorted, we can match dup file names
    TTreeNode *testNode;
    TStringList* allItems = new TStringList;
    allItems->Sorted = true;
    allItems->Duplicates = dupError;

    for(int i=3; i < fileViewTL->Items->Count-3; i++)
    {
        testNode = fileViewTL->Items->Item[i];

        if(!testNode->HasChildren)
        {
            try
            {
                allItems->AddObject(testNode->Text, testNode->Parent);
            }
            catch(...)
            {
                memo->Lines->Add("Duplicate "+testNode->Parent->Text+"\\"+testNode->Text);//+" Against "+testNode->Parent->Text+"\\"+testNode->Text);
            }
        }

        Label2->Caption = testNode->Parent->Text+"\\"+testNode->Text;
        Label3->Caption = AnsiString(i) +"/"+ AnsiString(fileViewTL->Items->Count);
        fileViewTL->Selected = testNode;
        progressBar->StepIt();
        Refresh();
    }

    Label1->Caption = "";
    Label3->Caption = "";
    progressBar->Position = 0;

//    Label2->Caption = "Sorting StringList into Ascending order...";
//    allItems->Sort();

return;
    //---------------------------------------------------------------------------

    //read all nodes
    for(int i=3; i < fileViewTL->Items->Count-3; i++)
    {
        //+1 for the common node
        readNode = fileViewTL->Items->Item[i];//GetNext();

        //if theres no children then these are the project scr files
        if(!readNode->HasChildren)
            compareThisNodeWithOthers(readNode);

        Label3->Caption = AnsiString(i) +"/"+ AnsiString(fileViewTL->Items->Count);
        selectNode = readNode;
        fileViewTL->Selected = selectNode;
        progressBar->StepIt();
        Refresh();
    }

    Label1->Caption = "";
    Label3->Caption = "";
    progressBar->Position = 0;
}
//---------------------------------------------------------------------------

bool TProjectSorta::compareThisNodeWithOthers(TTreeNode*& readNode)
{
    //flag to test if we've moved a copy already
    bool moved = false;

    //this is the looper tester
    TTreeNode *testNode = fileViewTL->Items->GetFirstNode();
    for(int i=0; i < 2; i++)
        testNode = testNode->GetNext();

    for(int i=0; i < fileViewTL->Items->Count; i++)
    {
        testNode = testNode->GetNext();
        if(testNode == NULL)
            return true;

//memo gets to big!
//        memo->Lines->Add("Testing "+readNode->Parent->Text+"\\"+readNode->Text+" Against "+testNode->Parent->Text+"\\"+testNode->Text);

        //is theres no children then this is a file
        if(!readNode->HasChildren)
        //if the text matches the test text & there not the same nodes
        if( (readNode->Text == testNode->Text) && (readNode != testNode) )
        {
            //if we have moved the file already
            if(moved)
            {
                //add a dexcription of wots goin on to a memo list
                memo->Lines->Add("MarkedDuplicate :"+readNode->Text+" from "+readNode->Parent->Text);

                //then save it to delete the node later
                TTreeNode *delNode = readNode;
                deleteNodesList->Add(delNode);
            }
            else
            {
                moved = true;

                memo->Lines->Add("Marked2Moved "+readNode->Text+" from "+readNode->Parent->Text+" Matched in "+testNode->Parent->Text);

                //save it to move it later
                moveNodesList->Add(readNode);
            }
        }

        Label2->Caption = readNode->Parent->Text+"\\"+readNode->Text+"?="+testNode->Parent->Text + "\\" + testNode->Text;
//        Label3->Caption = AnsiString(i) +"\\"+ AnsiString(fileViewTL->Items->Count);
        Refresh();
    }

    return false;
}
//---------------------------------------------------------------------------

void TProjectSorta::updateTree()
{
    progressBar->Max = deleteNodesList->Count;

    TTreeNode *delNode = NULL;

    for(int i=0; i < deleteNodesList->Count; i++)
    {
        // then delete the node, cos we only want one copy
        //read the list of node to delete
        delNode = (TTreeNode*)deleteNodesList->Items[i];
        deleteNodesList->Delete(i);

        if(delNode == NULL || delNode->Text == "")
        {
        }
        else
        {
            //output the info
            memo->Lines->Add("Removed :"+delNode->Text+" from "+delNode->Parent->Text);
            //show something happening
            Label2->Caption = delNode->Text;
            Label3->Caption = AnsiString(i) + "/"+ AnsiString(deleteNodesList->Count);
            //delete the tree node
            delNode->Delete();
            //update the screen
        }
        progressBar->StepIt();
        Refresh();
    }

    progressBar->Position = 0;
    progressBar->Max = moveNodesList->Count;

    for(int i=0; i < moveNodesList->Count; i++)
    {
        // then move the node, cos we only want one copy
        //read the list of node to delete
        TTreeNode *moveNode = (TTreeNode*)moveNodesList->Items[i];
        moveNodesList->Delete(i);

        if(moveNode)
        if(moveNode == NULL || moveNode->Text == "")
        {
        }
        else
        {
            //output the info
            memo->Lines->Add("Moved "+moveNode->Text+" from "+moveNode->Parent->Text+" Matched in "+moveNode->Parent->Text);
            //move it to the common node
            moveNode->MoveTo(commonNode, naAddChild);

            //show something happening
            Label2->Caption = moveNode->Text;
            Label3->Caption = AnsiString(i) + "/"+ AnsiString(moveNodesList->Count);
        }
        //update the screen
        progressBar->StepIt();
        Refresh();
    }

    Label1->Caption = "";
    Label2->Caption = "";
    Label3->Caption = "";
    progressBar->Position = 0;
}
//---------------------------------------------------------------------------


