//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CreateList.h"
#include "addItem.h"
#include <vcl\Clipbrd.hpp>
#include <Printers.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TListProg *ListProg;
String filename = NULL;
//---------------------------------------------------------------------------
__fastcall TListProg::TListProg(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TListProg::TreeKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    TTreeNode *current = Tree->Selected ;
    if(Key == VK_INSERT) {
        if(addItemForm->ShowModal()==mrOk)
            current = Tree->Items->AddChild(current, addItemForm->itemName->Text) ;
            NodeData *nd = new NodeData ;
            if(addItemForm->cat->Checked) nd->type = 1;
            else nd->type = 2 ;
            current->Data = (NodeData*)nd ;
    }
    if(Key == VK_DELETE) Tree->Items->Delete(current) ;
    if(Key == VK_RETURN) current->EditText() ;
}
//---------------------------------------------------------------------------

void __fastcall TListProg::SaveAs3Click(TObject *Sender)
{
    if(SaveDialog1->Execute()) {
        filename = SaveDialog1->FileName ;
        Tree->SaveToFile(filename);
        ListProg->Caption = "Create A List - " +filename ;
    }
}
//---------------------------------------------------------------------------

void __fastcall TListProg::Save3Click(TObject *Sender)
{
    if(filename == NULL){
        if(SaveDialog1->Execute()) {
            filename = SaveDialog1->FileName;
            Tree->SaveToFile(filename);
        }
    }
    else
        Tree->SaveToFile(filename);

   ListProg->Caption = "Create A List - " +filename ;
}
//---------------------------------------------------------------------------

void __fastcall TListProg::PrintSetup3Click(TObject *Sender)
{
    PrinterSetupDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TListProg::Print3Click(TObject *Sender)
{
    if (PrintDialog1->Execute())
        SpeedButton4Click(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TListProg::Exit2Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TListProg::Open2Click(TObject *Sender)
{
    if(OpenDialog1->Execute()){
        filename = OpenDialog1->FileName ;
        Tree->LoadFromFile(filename);
        ListProg->Caption = "Create A List - " + filename ;
    }
}
//---------------------------------------------------------------------------

void __fastcall TListProg::New2Click(TObject *Sender)
{
    filename = NULL ;
    Tree->Items->Clear();
    ListProg->Caption = "Create A List" ;
}
//---------------------------------------------------------------------------

void __fastcall TListProg::SpeedButton1Click(TObject *Sender)
{
    Open2Click(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TListProg::TreeGetImageIndex(TObject *Sender, TTreeNode *Node)
{
   if(Node->HasChildren) Node->ImageIndex = 1;
    else Node->ImageIndex = 2 ;//ImageIndex = 2;
//    if(Node->Data == NULL) return ;
//    if(((NodeData*)Node->Data)->type == 1) Node->ImageIndex = 1;
//    else Node->ImageIndex = 2 ;//ImageIndex = 2;
}
//---------------------------------------------------------------------------

void __fastcall TListProg::TreeDragDrop(TObject *Sender, TObject *Source, int X, int Y)
{
    TTreeNode* source = Tree->Selected;
    TTreeNode* target = Tree->GetNodeAt(X, Y);

    source->MoveTo(target, naAddChild);
}
//---------------------------------------------------------------------------

void __fastcall TListProg::TreeDragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
    Accept = true ;    
}
//---------------------------------------------------------------------------

void __fastcall TListProg::FormClose(TObject *Sender, TCloseAction &Action)
{
//  if (MessageDlg("Close application ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,0) == mrYes)
//    Action = caFree;
//  else
//    Action = caNone;
}
//---------------------------------------------------------------------------

void __fastcall TListProg::Cut2Click(TObject *Sender)
{
    TTreeNode *current = Tree->Selected ;
    current->Cut = true ;
    TStringList *tsl = new TStringList ;
    for(int i=0; i<current->Count; i++){
        tsl->Add(current->Item[i]->Text) ;
    }
//    Clipboard()->Assign(tsl) ;
//    abel1->Caption = Clipboard()->AsText;
}
//---------------------------------------------------------------------------

void __fastcall TListProg::Cut1Click(TObject *Sender)
{
   Cut2Click(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TListProg::SpeedButton2Click(TObject *Sender)
{
    New2Click(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TListProg::SpeedButton4Click(TObject *Sender)
{
        Printer()->BeginDoc();
        Printer()->Title = "Create Lists - " +filename;
        Printer()->Canvas->TextOut(0, 0, "Create Lists - " +filename);
//        Tree->PaintTo(Printer()->Handle, 10,10);
        for(int i=0; i<Tree->Items->Count; i++)
            Printer()->Canvas->TextOut(20, i*30 ,
//                    Font.Height = -Font.Size * Font.PixelsPerInch/ 72
                        //Font->Height,
//                      Font->Size * Font->PixelsPerInch/72,
//                    Tree->Items->Item[i]->Text.Height,
                    Tree->Items->Item[i]->Text);
        Printer()->EndDoc();
}
//---------------------------------------------------------------------------

void __fastcall TListProg::SpeedButton9Click(TObject *Sender)
{
    TTreeNode *current = Tree->Selected ;
      if(addItemForm->ShowModal()==mrOk)
         current = Tree->Items->AddChild(current, addItemForm->itemName->Text) ;
//    TreeKeyDown(NULL,VK_INSERT,NULL)
}
//---------------------------------------------------------------------------

void __fastcall TListProg::SpeedButton10Click(TObject *Sender)
{
    TTreeNode *current = Tree->Selected ;
    Tree->Items->Delete(current) ;    
}
//---------------------------------------------------------------------------

void __fastcall TListProg::SpeedButton5Click(TObject *Sender)
{
    Cut2Click(NULL);
}
//---------------------------------------------------------------------------

