//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MusicListSrc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMusicList *MusicList;
//---------------------------------------------------------------------------
__fastcall TMusicList::TMusicList(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMusicList::FormShow(TObject *Sender)
{
    ///
    if(FileExists("music list.ini"))
    {
    }
    else
    {
        int ans = Application->MessageBox("The Music List ini file was not found in the current directory.\nI will now recreate it for you, but you will have to go through the setup again.", "No ini file found", MB_YESNOCANCEL|MB_ICONQUESTION);

        for(int dir=0; dir< dlb->Items; diri++)
        {
            for(int file=0; file< flb->Items; file++)
            {
                String fileName = flb->Items->Strings[file];
            }
        }
    }


    FILE *F = fopen(FileListBox1->Items->Strings[i].c_str(),"r");
    struct stat statbuf;
    fstat(fileno(F), &statbuf);
    ListBox1->Items->Add(IntToStr(statbuf.st_size));
    fclose(F);

}
//---------------------------------------------------------------------------
