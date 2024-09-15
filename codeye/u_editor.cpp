//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "u_editor.h"
#include "u_seldest.h"
#include "main.h"
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
void __fastcall TfrmEdit::Explode1Click(TObject *Sender)
{
    if (frmSelDest->ShowModal() == mrOk) Explode(frmSelDest->selDir->Directory);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Explode(AnsiString dir)
{
    AnsiString curst, in_file;
    TStrings* cur = new TStringList();
    int f_cnt = 0, l_cnt = 0;

    // process all lines
    for (int i=0, j=0; i < TXT->Lines->Count; i++) {
        curst = TXT->Lines->Strings[i];
        if (in_file.IsEmpty()) {
            if (curst.IsEmpty()) continue;
            if (curst.Pos("File '") == 1) {
                curst.Delete(1,6);
                j = curst.Pos("'");
                if (j<2) continue;
                in_file = curst.SubString(1,j-1);
                i++; // skip next empty line
            }
        } else {
            if (curst == curst.StringOfChar('-',SPLITTER_LEN)) {
                // remove trailing newline
                j = cur->Count - 1;
                if (cur->Strings[j].IsEmpty()) cur->Delete(j);
                // count lines & files
                l_cnt += cur->Count;
                f_cnt++;
                // save
                cur->SaveToFile(dir + "\\" + in_file);
                cur->Clear();
                in_file = "";
            } else
                cur->Append(curst);
        }
    }

    // free memory and show some stats
    delete cur;
    ShowMessage("Statistics:\nLines: "+IntToStr(l_cnt)+"\nFiles: "+IntToStr(f_cnt));
}
//---------------------------------------------------------------------------
