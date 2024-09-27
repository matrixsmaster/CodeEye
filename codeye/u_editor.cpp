//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <map>
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
    if (!FileExists(fileToOpen)) {
        TXT->Clear();
        TXT->Enabled = False;
        return;
    }
    TXT->Lines->LoadFromFile(fileToOpen);
    Caption = ExtractFileName(fileToOpen);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Close1Click(TObject *Sender)
{
    Close();
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

                // determine the type (text/bin)
                int td = Form1->GetFileTypeId(in_file);
                if (td >= 0 && reg_types[td].binary) {
                    // save binary file
                    SaveBinary(dir + "\\" + in_file,cur);
                } else {
                    // save text file
                    cur->SaveToFile(dir + "\\" + in_file);
                }

                cur->Clear();
                in_file = "";

            } else
                cur->Append(curst);
        }
    }

    // free memory and show some stats
    delete cur;
    ShowMessage("Done!\n\nStatistics:\nLines: "+IntToStr(l_cnt)+"\nFiles: "+IntToStr(f_cnt));
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Deobfuscate1Click(TObject *Sender)
{
    // prepare the generator
    CLCRNG* rng = new CLCRNG;
    int fsm = 0, tid = -1;

    // copy text to avoid updating the widget
    TStrings* res = new TStringList();
    res->AddStrings(TXT->Lines);

    // process all lines
    for (int i = 0, j = 0; i < res->Count; i++) {
        AnsiString curst = res->Strings[i];
        if (!fsm) {
            if (curst.IsEmpty()) continue;
            if (curst.Pos("File '") == 1) {
                // get the file name
                curst.Delete(1,6);
                j = curst.Pos("'");
                if (j < 2) continue;
                AnsiString fn = curst.SubString(1,j-1);

                // get file type
                tid = Form1->GetFileTypeId(fn);
                if (tid < 0) continue;

                // ready to process
                rng->setSeed(fn.c_str());
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
void __fastcall TfrmEdit::Resave1Click(TObject *Sender)
{
    if (!fileToOpen.IsEmpty()) TXT->Lines->SaveToFile(fileToOpen);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::SaveBinary(AnsiString fn, TStrings* from)
{
    if (!from || fn.IsEmpty()) return;

    FILE* f = fopen(fn.c_str(),"wb");
    if (!f) return;

    for (int i = 0; i < from->Count; i++) {
        AnsiString s = from->Strings[i];
        while (s.Length() > 0) {
            uint8_t b = StrToInt("0x"+s.SubString(1,2));
            fwrite(&b,1,1,f);
            s.Delete(1,2);
        }
    }

    fclose(f);
}
//---------------------------------------------------------------------------
bool __fastcall ishex(int c)
{
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Savecompressed1Click(TObject *Sender)
{
    std::map<AnsiString,int> dict;

    for (int i = 0; i < TXT->Lines->Count; i++) {
        AnsiString s = TXT->Lines->Strings[i];
        int fsm = 0, hex = 0;
        AnsiString acc;
        for (int j = 1; j <= s.Length(); j++) {
            switch (fsm) {
            case 0:
                if (isalnum(s[j])) fsm = 1;
                break;
            case 1:
                if (!isalnum(s[j])) {
                    if (acc.Length() > 2 && acc.Length() > hex)
                        dict[acc]++;
                    fsm = 0;
                    hex = 0;
                    acc = "";
                }
                break;
            }
            if (fsm) {
                acc += s[j];
                if (ishex(s[j])) hex++;
            }
        }
    }

    std::multimap<int,AnsiString> revmap;
    for (std::map<AnsiString,int>::iterator it = dict.begin(); it != dict.end(); ++it) {
        int len = it->first.Length();
        int score = ((len - 1) * it->second) - len;
        revmap.insert(std::pair<int,AnsiString>(score,it->first));
    }

    ShowMessage(IntToStr(revmap.size()));
    std::multimap<int,AnsiString>::iterator rit = revmap.end();
    for (int i = 0; i < 10 && i < revmap.size(); i++) {
        --rit;
        ShowMessage(rit->second+" : "+IntToStr(rit->first));
    }
}
//---------------------------------------------------------------------------
