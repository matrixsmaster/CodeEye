//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <IniFiles.hpp>
#include "u_editor.h"
#include "lcrng.h"
//---------------------------------------------------------------------------
#define MIXPROJ_PREFIX "MixProj_"
#define MIXPROJ_SUFFIX ".txt"
#define MIXPROJ_HEADER "MSM's Code Eye Project Mix File"
#define SPLITTER_LEN 65
#define CHAPTERSPLIT_LEN 80
#define HEXDUMP_LEN 16
//---------------------------------------------------------------------------
typedef TfrmEdit *PEditor;
struct CEOCacheEntry {
    const char* line;
    int len, idx;
};
struct CEOCacheLine {
    //int id;
    CEOCacheEntry tab[256];
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:    // IDE-managed Components
    TDirectoryListBox *selDir;
    TFileListBox *selFile;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Exit1;
    TMenuItem *Help1;
    TMenuItem *About1;
    TMenuItem *Window1;
    TMenuItem *Closeall1;
    TLabel *Label1;
    TMenuItem *Launchparams1;
    TLabel *Label4;
    TEdit *Edit1;
    TBitBtn *BitBtn1;
    TCheckBox *CheckBox1;
    TMenuItem *Openmixfile1;
    TMenuItem *N1;
    TSaveDialog *sd1;
    TDriveComboBox *DriveComboBox1;
    TMenuItem *Edit2;
    TMenuItem *Disclaimer1;
    TOpenDialog *od1;
    TMenuItem *N2;
    TMenuItem *Mixit1;
    TMenuItem *Changelog1;
    TMenuItem *Arrange1;
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall selFileChange(TObject *Sender);
    void __fastcall selFileDblClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Closeall1Click(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall Launchparams1Click(TObject *Sender);
    void __fastcall DriveComboBox1Change(TObject *Sender);
    void __fastcall Openmixfile1Click(TObject *Sender);
    void __fastcall Disclaimer1Click(TObject *Sender);
private:    // User declarations
    AnsiString curFile;
    AnsiString dPath;
    TList* windows;
    CEOCacheLine* cache;
    bool once;
    CLCRNG* rng;
    TIniFile* config;
    void __fastcall Generator(AnsiString prjDir, AnsiString prjName, AnsiString flName);
    void __fastcall OpenWindow(AnsiString fn);
    void __fastcall DestroyWindows();
    void __fastcall ObfuscatePrepare();
    int __fastcall LineCounter(TStrings* body);
    void __fastcall LoadBinary(AnsiString fn, TStrings* to);
public:        // User declarations
    __fastcall TForm1(TComponent* Owner);
    int __fastcall GetFileTypeId(AnsiString fn);
    void __fastcall Obfuscate(TStrings* body, int tid);
    AnsiString __fastcall Deobfuscate(CLCRNG* lrng, AnsiString str, int tid);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
