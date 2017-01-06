//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include <vcl\bde.hpp>
#include "MAINFORM.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  // make sure something was typed into the edit box, if nothing typed,
  // return without doing anything.
  if(Edit1->Text.Length() ==0)
  {
    Application->MessageBox("Type an alias name first",
                            "Error",MB_ICONINFORMATION | MB_OK);
    return;
  }

  // creating the alias could take a while, change the cursor
  // to an hourglass.
  Screen->Cursor = crHourGlass;

  hDBISes Session;                     // declare a bde session handle
  DbiInit(NULL);                       // initialize BDE.
  DbiStartSession(NULL,Session,"");    // start a temporaray bde session
  AnsiString Path = "PATH:" +          // formulate a path string
                     DirectoryListBox1->Directory;
  // add the alias using the BDE function.
  DbiAddAlias(0,Edit1->Text.c_str(),"PARADOX",Path.c_str(),true);
  DbiCloseSession(Session);            // close the session
  DbiExit();                           // shut down the BDE.
  Screen->Cursor = crDefault;          // reset cursor.
}
//---------------------------------------------------------------------------

/*
	// Creating The Alias Could Take A While, Change The Cursor
	// To An Hourglass.
	Screen->cursor = Crhourglass;

	// Declare A Bde Session Handle
	Hdbises Session;

	// Initialize Bde.
	Dbiinit(null);
	
	// Start A Temporaray Bde Session
	Dbistartsession(null,session,"");

	// Formulate A Path String
	Ansistring Path = "path:" +  "c:\projects\best\source\data";

	// Add The Alias Using The Bde Function.
	Dbiaddalias(0, "BestDrv", "paradox", path.c_str(), true);
	
	// Close The Session
	Dbiclosesession(session);
	
	// Shut Down The Bde.
	Dbiexit();

	// Reset Cursor.
	Screen->cursor = Crdefault;
*/