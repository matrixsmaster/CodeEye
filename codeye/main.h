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
#include "u_editor.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
typedef TfrmEdit *PEditor;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
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
	TComboBox *cb1;
	TMenuItem *Launchparams1;
    TLabel *Label4;
    TEdit *Edit1;
    TBitBtn *BitBtn1;
    TCheckBox *CheckBox1;
    TMenuItem *Openmixfile1;
    TMenuItem *N1;
    TSaveDialog *sd1;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall selFileChange(TObject *Sender);
	void __fastcall selFileDblClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Closeall1Click(TObject *Sender);
	void __fastcall cb1Change(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall Launchparams1Click(TObject *Sender);
private:	// User declarations
	AnsiString curFile;
	AnsiString dPath;
	TList *frms;
	bool once;
	void __fastcall Generator(AnsiString prjName, AnsiString flName);
	void __fastcall DestroyWindows();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
