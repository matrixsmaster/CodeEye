//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "u_editor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmEdit *frmEdit;
//---------------------------------------------------------------------------
__fastcall TfrmEdit::TfrmEdit(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Font1Click(TObject *Sender)
{
        fd0->Font = TXT->Font;
        if (fd0->Execute()) TXT->Font = fd0->Font;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Background1Click(TObject *Sender)
{
        cd0->Color = TXT->Color;
        if (cd0->Execute()) TXT->Color = cd0->Color;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::FormShow(TObject *Sender)
{
        if (!FileExists(this->fileForOpen)) {
                TXT->Clear();
                TXT->Enabled = False;
                return;
        }
        TXT->Lines->LoadFromFile(this->fileForOpen);
        this->Caption = ExtractFileName(this->fileForOpen);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Close1Click(TObject *Sender)
{
        this->Close();        
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::SelectAll1Click(TObject *Sender)
{
        TXT->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Copy1Click(TObject *Sender)
{
        TXT->CopyToClipboard();
}
//---------------------------------------------------------------------------
