//---------------------------------------------------------------------------

#ifndef u_editorH
#define u_editorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmEdit : public TForm
{
__published:	// IDE-managed Components
        TMemo *TXT;
        TMainMenu *mMenu0;
        TFontDialog *fd0;
        TColorDialog *cd0;
        TMenuItem *File1;
        TMenuItem *View1;
        TMenuItem *Close1;
        TMenuItem *Font1;
        TMenuItem *Background1;
        TMenuItem *Edit1;
        TMenuItem *SelectAll1;
        TMenuItem *Copy1;
        void __fastcall Font1Click(TObject *Sender);
        void __fastcall Background1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Close1Click(TObject *Sender);
        void __fastcall SelectAll1Click(TObject *Sender);
        void __fastcall Copy1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        AnsiString fileForOpen;
        __fastcall TfrmEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEdit *frmEdit;
//---------------------------------------------------------------------------
#endif
