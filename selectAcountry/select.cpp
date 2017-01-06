//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "select.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  TListItem *pItem;
  TListColumn *pColumn;
  // Create a ListView item for each image in the ImageList
  ListView1->LargeImages = ImageList1;
  ListView1->SmallImages = ListView1->LargeImages; //;= ImageList1;
  for (int i = 0; i < ImageList1->Count; i++)
  {
    pItem = ListView1->Items->Add();
    pItem->Caption = "Image" + IntToStr(i);
    pItem->ImageIndex = i;
  }
  // Create two columns to show during viewing as vsReport

  pColumn = ListView1->Columns->Add();
  pColumn->Caption = "Column 1";
  pColumn = ListView1->Columns->Add();
  pColumn->Caption = "Column 2";
  // Add View styles and constants to the Combo Box
  ComboBox1->Items->AddObject("vsIcon", (TObject *)vsIcon);
  ComboBox1->Items->AddObject("vsList", (TObject *)vsList);
  ComboBox1->Items->AddObject("vsReport", (TObject *)vsReport);
  ComboBox1->Items->AddObject("vsSmallIcon", (TObject *)vsSmallIcon);

  // Display first item in the Combo Box
  ComboBox1->ItemIndex = 0;
    
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1Click(TObject *Sender)
{
ListView1->ViewStyle = (TViewStyle) ComboBox1->Items->Objects[ComboBox1->ItemIndex];
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ListBox1DrawItem(TWinControl *Control, int Index,
      TRect &Rect, TOwnerDrawState State)
{
  Graphics::TBitmap *pBitmap; // temporary variable for item’s bitmap
  int     Offset = 2;   // default text offset width
  // note that we draw on the listbox’s canvas, not on the form
  TCanvas *pCanvas = ((TListBox *)Control)->Canvas;
  pCanvas->FillRect(Rect); // clear the rectangle
  pBitmap = (Graphics::TBitmap *)((TListBox *)Control)->Items->Objects[Index];

  if (pBitmap)
  {
    pCanvas->BrushCopy(Bounds(Rect.Left + Offset, Rect.Top, pBitmap->Width, pBitmap->Height), pBitmap, Bounds(0, 0, pBitmap->Width, pBitmap->Height), clRed); // render bitmap
    Offset += pBitmap->Width + 4;   // add four pixels between bitmap and text}
  }
  // display the text
  pCanvas->TextOut(Rect.Left + Offset+10, Rect.Top, ((TListBox *)Control)->Items->Strings[Index]);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1DrawItem(TWinControl *Control, int Index,
      TRect &Rect, TOwnerDrawState State)
{
  Graphics::TBitmap *pBitmap; // temporary variable for item’s bitmap
  int     Offset = 2;   // default text offset width
  // note that we draw on the listbox’s canvas, not on the form
  TCanvas *pCanvas = ((TListBox *)Control)->Canvas;
  pCanvas->FillRect(Rect); // clear the rectangle
  pBitmap = (Graphics::TBitmap *)((TListBox *)Control)->Items->Objects[Index];

  if (pBitmap)
  {
    pCanvas->BrushCopy(Bounds(Rect.Left + Offset, Rect.Top, pBitmap->Width, pBitmap->Height), pBitmap, Bounds(0, 0, pBitmap->Width, pBitmap->Height), clRed); // render bitmap
    Offset += pBitmap->Width + 4;   // add four pixels between bitmap and text}
  }
  // display the text
  pCanvas->TextOut(Rect.Left + Offset+10, Rect.Top, ((TListBox *)Control)->Items->Strings[Index]);
}
//---------------------------------------------------------------------------

