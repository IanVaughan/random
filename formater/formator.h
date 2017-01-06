//---------------------------------------------------------------------------
#ifndef formatorH
#define formatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include "cgauges.h"
#include <ComCtrls.hpp>
#include "cspin.h"
#include <Buttons.hpp>
#include <FileCtrl.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TstartForm : public TForm
{
__published:
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TCSpinEdit *numtabs;
    TCSpinEdit *lineLen;
    TLabel *Label1;
    TLabel *Label2;
    TCheckBox *backup;
    TCheckBox *noMaxLen;
    TTabSheet *TabSheet4;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TPanel *Panel1;
    TPanel *Panel2;
    TCheckBox *subdirs;
    TCheckBox *allDir;
    TPanel *Panel4;
    TDirectoryListBox *DirectoryListBox1;
    TFileListBox *FileListBox1;
    TSplitter *Splitter1;
    TPanel *Panel5;
    TBitBtn *go;
    TBitBtn *BitBtn2;
    TPanel *Panel6;
    TCheckBox *defaultopt;
    TPanel *Panel7;
    TEdit *Edit1;
    TImage *Image1;
    TLabel *dirL;
    TPanel *driveP;
    TDriveComboBox *DriveComboBox1;
    TPanel *Panel3;
    TFilterComboBox *FilterComboBox1;
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall goClick(TObject *Sender);
    void __fastcall FileListBox1DblClick(TObject *Sender);

private:

public:
       __fastcall TstartForm(TComponent* Owner);
};
extern PACKAGE TstartForm *startForm;
#endif
