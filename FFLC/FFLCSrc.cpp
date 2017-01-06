//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FFLCSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFFLC *FFLC;
//---------------------------------------------------------------------------

typedef struct
{
    TSpeedButton* first;
    TSpeedButton* second;
    String lineData;
}APair;
APair *pair;

TList *thePairs = NULL;
int clickCount = 0;
// -----------------------------------------------------------------------------

__fastcall TFFLC::TFFLC(TComponent* Owner): TForm(Owner)
{
    thePairs = new TList;
    pair = new APair;

    add->Enabled = false;

    ReplacePos = -1;
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::FormShow(TObject *Sender)
{
    Picker->ActivePage = TabSheet1;
    Panel1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::FormDestroy(TObject *Sender)
{
    for(int i=0; i< thePairs->Count-1; i++)
        delete thePairs->Items[i];
    delete thePairs;
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::AClick(TObject *Sender)
{
    TSpeedButton* hit = ((TSpeedButton*)Sender);
    hit->Down = true;

    //if(hit->Down == true || (hit == pair->first && hit != pair->second ))
    if(hit != /*pair->first)// && hit !=*/ pair->second)
    {
        switch(clickCount)
        {
            case 0 :
            {
                pair->first = hit;
                ShowLettersLeft(hit);
                Label1->Caption = hit->Caption;
                break;
            }
            case 1 :
            {
                pair->second = hit;

                add->Enabled = true;
                clickCount = -1;
                DisableAllButtons();
                Label1->Caption = Label1->Caption + hit->Caption;
                break;
            }
        }

        clickCount++;
    }
    //else hit->Down = true;
    else
    {
        hit->Down = false;
        clickCount = 1;
        EnableAllButtons();
        Label1->Caption = ((TSpeedButton*)pair->first)->Caption;
        pair->second = NULL;

        if(hit == pair->first)
        {
            clickCount = 0;
            Label1->Caption = "";
            pair->first = NULL;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::addClick(TObject *Sender)
{
    add->Enabled = false;
    pair->lineData = Edit1->Text;
    Edit1->Text = "";
    Label1->Caption = "";

    if(add->Caption == "Register")
    {
        thePairs->Add(pair);
        pair = new APair;
    }
    else
    {
        thePairs->Items[ReplacePos] = pair;
        Picker->ActivePage = TabSheet2;
        PickerChange(this);
    }

    TSpeedButton* hit = (TSpeedButton*)((APair*)thePairs->Items[thePairs->Count-1])->first;
    hit->Down = false;
    hit = (TSpeedButton*)((APair*)thePairs->Items[thePairs->Count-1])->second;
    hit->Down = false;
    EnableAllButtons();

}
//---------------------------------------------------------------------------

void TFFLC::ShowLettersLeft(TSpeedButton *firstLetter)
{
    for(int i=0; i< thePairs->Count; i++)
    {
        TSpeedButton *testFirstLetter = (TSpeedButton*)((APair*)thePairs->Items[i])->first;
        if(firstLetter == testFirstLetter)
        {
            TSpeedButton *second = (TSpeedButton*)((APair*)thePairs->Items[i])->second;
            second->Enabled = false;
        }
    }
}
// -----------------------------------------------------------------------------

void TFFLC::EnableAllButtons()
{
    A->Enabled = true;
    B->Enabled = true;
    C->Enabled = true;
    D->Enabled = true;
    E->Enabled = true;
    F->Enabled = true;
    G->Enabled = true;
    H->Enabled = true;
    I->Enabled = true;
    J->Enabled = true;
    K->Enabled = true;
    L->Enabled = true;
    M->Enabled = true;
    N->Enabled = true;
    O->Enabled = true;
    P->Enabled = true;
    Q->Enabled = true;
    R->Enabled = true;
    S->Enabled = true;
    T->Enabled = true;
    U->Enabled = true;
    V->Enabled = true;
    W->Enabled = true;
    X->Enabled = true;
    Y->Enabled = true;
    Z->Enabled = true;
    _1->Enabled = true;
    _2->Enabled = true;
    _3->Enabled = true;
    _4->Enabled = true;
    _5->Enabled = true;
    _6->Enabled = true;
    _7->Enabled = true;
    _8->Enabled = true;
    _9->Enabled = true;
    _0->Enabled = true;
}
// -----------------------------------------------------------------------------

void TFFLC::DisableAllButtons()
{
    A->Enabled = false;
    B->Enabled = false;
    C->Enabled = false;
    D->Enabled = false;
    E->Enabled = false;
    F->Enabled = false;
    G->Enabled = false;
    H->Enabled = false;
    I->Enabled = false;
    J->Enabled = false;
    K->Enabled = false;
    L->Enabled = false;
    M->Enabled = false;
    N->Enabled = false;
    O->Enabled = false;
    P->Enabled = false;
    Q->Enabled = false;
    R->Enabled = false;
    S->Enabled = false;
    T->Enabled = false;
    U->Enabled = false;
    V->Enabled = false;
    W->Enabled = false;
    X->Enabled = false;
    Y->Enabled = false;
    Z->Enabled = false;
    _1->Enabled = false;
    _2->Enabled = false;
    _3->Enabled = false;
    _4->Enabled = false;
    _5->Enabled = false;
    _6->Enabled = false;
    _7->Enabled = false;
    _8->Enabled = false;
    _9->Enabled = false;
    _0->Enabled = false;


    ((TSpeedButton*)(pair->first))->Enabled = true;
    ((TSpeedButton*)(pair->second))->Enabled = true;

    ///*TSpeedButton *first = */((TSpeedButton*)((APair*)thePairs->Items[thePairs->Count-1])->first)->Enabled = true;
    ///*TSpeedButton *second = */((TSpeedButton*)((APair*)thePairs->Items[thePairs->Count-1])->second)->Enabled = true;
}
// -----------------------------------------------------------------------------

void __fastcall TFFLC::PickerChange(TObject *Sender)
{
    ListBox1->Items->Clear();

    if(Picker->ActivePage == TabSheet2)
    {
        for(int i=0; i< thePairs->Count; i++)
        {
            TSpeedButton *first = (TSpeedButton*)((APair*)thePairs->Items[i])->first;
            TSpeedButton *second = (TSpeedButton*)((APair*)thePairs->Items[i])->second;
            String firstS = first->Caption.SubString(2,1);
            String secondS = second->Caption.SubString(2,1);
            String line = ((APair*)thePairs->Items[i])->lineData;
            ListBox1->Items->Add(firstS + secondS + " " +line);
        }
    }
    else
    {
        add->Caption = "Register";
        EnableAllButtons();
        Edit1->Text = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::SortedClick(TObject *Sender)
{
    ListBox1->Sorted = Sorted->Checked;

    if(Sorted->Checked)
    {
        MoveUp->Enabled = false;
        MoveDown->Enabled = false;
    }
    else
    {
        MoveUp->Enabled = true;
        MoveDown->Enabled = true;

        PickerChange(this);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::MoveUpClick(TObject *Sender)
{
    int place;
    //loop all the items in the list box
    for(int i=0; i< ListBox1->Items->Count; i++)
    {
        //if one is selected
        if(ListBox1->Selected[i] == true)
        {
            if(i-1 <0)
                place = ListBox1->Items->Count-1;
            else
                place = i-1;

            APair *save = (APair*)thePairs->Items[i];
            thePairs->Items[i] = thePairs->Items[place];
            thePairs->Items[place] = save;
        }
    }

    PickerChange(this);
    ListBox1->ItemIndex = place;
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::MoveDownClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::LoadClick(TObject *Sender)
{
    if(OpenDialog1->Execute())
    {
        ListBox1->Items->LoadFromFile(OpenDialog1->FileName);

        //clear old list
        for(int i=0; i< thePairs->Count-1; i++)
            delete thePairs->Items[i];
        delete thePairs;

        //create a new one
        thePairs = new TList;

        //now read in each line that was the file into our pairs list
        for(int i=0; i<ListBox1->Items->Count; i++)
        {
            //read each line
            String line = ListBox1->Items->Strings[i];

            //create new pair group to add to the TList
            APair *p = new APair;
            //find the button that matches the letter
            p->first = GetButton(line.SubString(1,1),i);
            p->second = GetButton(line.SubString(2,1),i);
            p->lineData = line.SubString(4, line.Length());
            thePairs->Add(p);
        }
    }
    Picker->ActivePage = TabSheet2;
    PickerChange(this);
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::SaveClick(TObject *Sender)
{
    if(SaveDialog1->Execute())
    {
        ListBox1->Items->SaveToFile(SaveDialog1->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFFLC::RemoveClick(TObject *Sender)
{
    //loop all the items in the list box
    for(int i=0; i< ListBox1->Items->Count; i++)
    {
        //if one is selected
        if(ListBox1->Selected[i] == true)
        {
            String pair = ListBox1->Items->Strings[i];
            String First = pair.SubString(1,1);
            String Second = pair.SubString(2,1);

            int i=0;
            //then find the selected item in our list and remove it
            while(i<thePairs->Count)
            //(int i=0; i< thePairs->Count; i++)
            {
                TSpeedButton *first = (TSpeedButton*)((APair*)thePairs->Items[i])->first;
                TSpeedButton *second = (TSpeedButton*)((APair*)thePairs->Items[i])->second;
                String firstS = first->Caption.SubString(2,1);
                String secondS = second->Caption.SubString(2,1);

                if(First == firstS && Second == secondS)
                {
                    delete thePairs->Items[i];
                    thePairs->Delete(i);
                }
                i++;
            }

        }
    }
    Picker->ActivePage = TabSheet2;
    PickerChange(this);
}
//---------------------------------------------------------------------------

TSpeedButton *TFFLC::GetButton(String chr, int lineNum)
{
    char *c_chr = chr.c_str();

    switch(*c_chr)
    {
        case 'A' : return A;
        case 'B' : return B;
        case 'C' : return C;
        case 'D' : return D;
        case 'E' : return E;
        case 'F' : return F;
        case 'G' : return G;
        case 'H' : return H;
        case 'I' : return I;
        case 'J' : return J;
        case 'K' : return K;
        case 'L' : return L;
        case 'M' : return M;
        case 'N' : return N;
        case 'O' : return O;
        case 'P' : return P;
        case 'Q' : return Q;
        case 'R' : return R;
        case 'S' : return S;
        case 'T' : return T;
        case 'U' : return U;
        case 'V' : return V;
        case 'W' : return W;
        case 'X' : return X;
        case 'Y' : return Y;
        case 'Z' : return Z;
        case '1' : return _1;
        case '2' : return _2;
        case '3' : return _3;
        case '4' : return _4;
        case '5' : return _5;
        case '6' : return _6;
        case '7' : return _7;
        case '8' : return _8;
        case '9' : return _9;
        case '0' : return _0;
        case ' ' : NULL;
        default :
        {
            String outText = "The file format could not be read at line number "+String(lineNum)+".\n";
            outText += "The char '"+ chr + "' was not reconized. Please check the file.";
            outText += "The unread char has been set as a letter 'A'.";
            Application->MessageBox(outText.c_str(), "File Format Error", MB_OK|MB_ICONERROR);
            return NULL;
        }
    }
}
// -----------------------------------------------------------------------------

void __fastcall TFFLC::ListBox1DblClick(TObject *Sender)
{
    //now read in each line that was the file into our pairs list
    for(int i=0; i<ListBox1->Items->Count; i++)
    {
        if(ListBox1->Selected[i] == true)
        {
            TSpeedButton *first = (TSpeedButton*)((APair*)thePairs->Items[i])->first;
            TSpeedButton *second = (TSpeedButton*)((APair*)thePairs->Items[i])->second;

            pair->first = first;
            pair->second = second;

            String firstS = first->Caption.SubString(2,1);
            String secondS = second->Caption.SubString(2,1);
            Label1->Caption = firstS + secondS;
            first->Down = true;
            second->Down = true;
            Edit1->Text = ((APair*)thePairs->Items[i])->lineData;

            ReplacePos = i;
        }
    }

    DisableAllButtons();
    add->Caption = "Update";
    add->Enabled = true;
    Picker->ActivePage = TabSheet1;
    Edit1->SetFocus();
}
//---------------------------------------------------------------------------

