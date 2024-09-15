//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "u_editor.h"
#include "u_seldest.h"
#include "file_types.h"
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
    for (int i = 0, j = 0; i < TXT->Lines->Count; i++) {
        curst = TXT->Lines->Strings[i];
        if (in_file.IsEmpty()) {
            if (curst.IsEmpty()) continue;
            if (curst.Pos("File '") == 1) {
                // get the file name
                curst.Delete(1,6);
                j = curst.Pos("'");
                if (j < 2) continue;
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
void __fastcall TfrmEdit::Deobfuscate1Click(TObject *Sender)
{
    // find the project name
    AnsiString prjname,curst;
    for (int i = 0; i < TXT->Lines->Count; i++) {
        curst = TXT->Lines->Strings[i];
        if (curst.IsEmpty()) continue;
        if (curst.Pos("Project = '") == 1) {
            curst.Delete(1,11);
            int j = curst.Pos("'");
            if (j < 2) continue;
            prjname = curst.SubString(1,j-1);
            break;
        }
    }
    if (prjname.IsEmpty()) {
        ShowMessage("Unable to find project name!");
        return;
    }

    // prepare the generator
    CLCRNG* rng = new CLCRNG;
    rng->setSeed(prjname.c_str());

    // copy text to avoid updating the widget
    TStrings* res = new TStringList();
    res->AddStrings(TXT->Lines);

    // process all lines
    int fsm = 0, tid = -1;
    for (int i = 0, j = 0; i < res->Count; i++) {
        curst = res->Strings[i];
        if (!fsm) {
            if (curst.IsEmpty()) continue;
            if (curst.Pos("File '") == 1) {
                // get the file name
                curst.Delete(1,6);
                j = curst.Pos("'");
                if (j < 2) continue;
                AnsiString fn = curst.SubString(1,j-1);

                // get file extension
                AnsiString ext = ExtractFileExt(fn).UpperCase();
                if (ext.IsEmpty()) continue;
                if (ext[1] == '.') ext.Delete(1,1);

                // find appropriate file type record
                tid = -1;
                for (j = 0; j < NUMITEMS(reg_types) && tid < 0; j++) {
                    if (AnsiString(reg_types[j].ext) == ext)
                        tid = j;
                }
                if (tid < 0) continue;
                fsm = 1;
            }
        } else {
            if (curst == curst.StringOfChar('-',SPLITTER_LEN)) {
                fsm = 0;
                continue;
            }
            res->Strings[i] = Form1->Deobfuscate(rng,curst,tid);
        }
    }

    // update the text
    TXT->Clear();
    TXT->Lines->AddStrings(res);

    // free memory
    delete res;
    delete rng;
}
//---------------------------------------------------------------------------

