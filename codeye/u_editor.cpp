//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>
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
int __fastcall chrconv(int c)
{
    if (c >= 32 && c <= 126)
        return c - 32;
    else if (c == '\t')
        return 96;
    return 95;
}
bool __fastcall ishexmod(int c)
{
    if (c > 94) return false;
    return (ishex(c + 32));
}
uint8_t __fastcall hexton(int n)
{
    if (n <= '9'-32) return n - ('0'-32);
    else return n - ('A'-32);
}
uint8_t __fastcall hextob(int h, int l)
{
    uint8_t r = hexton(h) << 4;
    return r | hexton(l);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Savecompressed1Click(TObject *Sender)
{
    // create base dictionary
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

    // calculate scores and sort by highest score
    std::multimap<int,AnsiString> revmap;
    for (std::map<AnsiString,int>::iterator it = dict.begin(); it != dict.end(); ++it) {
        int len = it->first.Length();
        int score = ((len - 1) * it->second) - len;
        if (score > 1)
            revmap.insert(std::pair<int,AnsiString>(score,it->first));
    }
    dict.clear();

    // take highest scores and populate final word map
    std::map<AnsiString,int> wmap;
    std::multimap<int,AnsiString>::iterator rit = revmap.end();
    for (unsigned i = 0; i < 286 && i < revmap.size(); i++) {
        --rit;
        //ShowMessage(rit->second+" : "+IntToStr(rit->first));
        wmap[rit->second] = i;
    }
    revmap.clear();

    std::vector<uint8_t> nowd;
    for (int i = 0; i < TXT->Lines->Count; i++) {
        AnsiString s = TXT->Lines->Strings[i] + "\n";
        int fsm = 0, hex = 0;
        AnsiString acc;
        for (int j = 1; j <= s.Length(); j++) {
            switch (fsm) {
            case 0:
                if (isalnum(s[j])) fsm = 1;
                break;
            case 1:
                if (!isalnum(s[j])) {
                    if (acc.Length() > 2 && acc.Length() > hex && wmap.count(acc)) {
                        int p = wmap[acc];
                        if (p < 30) { // tier 1
                            nowd.push_back(p + 97);
                        } else { // tier 2
                            nowd.push_back(127);
                            nowd.push_back(p - 30);
                        }
                    } else {
                        for (int k = 1; k <= acc.Length(); k++)
                            nowd.push_back(chrconv(acc[k]));
                    }
                    fsm = 0;
                    hex = 0;
                    acc = "";
                }
                break;
            }
            if (fsm) {
                acc += s[j];
                if (ishex(s[j])) hex++;
            } else
                nowd.push_back(chrconv(s[j]));
        }
        //nowd.push_back(95);
    }
    wmap.clear();

    FILE* tst = fopen("test-nowd.bin","wb");
    if (tst) {
        fwrite(&(nowd[0]),nowd.size(),1,tst);
        fclose(tst);
    }

    std::vector<uint8_t> rle;
    uint8_t prev = 0xFF;
    int rlecnt = 0;
    for (unsigned i = 0; i < nowd.size(); i++) {
        if (nowd[i] < 127 && nowd[i] == prev && rlecnt < 64) rlecnt++;
        else {
            if (rlecnt > 2) {
                rle.push_back(0x80 | rlecnt);
                rlecnt = 1;
            }
            for (int k = 0; k < rlecnt; k++)
                rle.push_back(prev);

            rlecnt = 1;
            prev = nowd[i];
        }
    }

    tst = fopen("test-rle.bin","wb");
    if (tst) {
        fwrite(&(rle[0]),rle.size(),1,tst);
        fclose(tst);
    }

    std::vector<uint8_t> out;
    int hex = 0;
    unsigned hpos = 0;
    for (unsigned i = 0; i < rle.size(); i++) {
        if (ishexmod(rle[i]) && hex < 64*2) hex++;
        else {
            if (hex > 4 && hex % 2 == 0) {
                hex /= 2;
                out.push_back(0xC0 | hex);
                for (int j = 0; j < hex; j++)
                    out.push_back(hextob(rle[hpos+j*2],rle[hpos+j*2+1]));
            } else {
                for (unsigned j = hpos; j < i; j++)
                    out.push_back(rle[j]);
            }
            hex = 0;
            hpos = i;
        }
    }

    tst = fopen("test-out.bin","wb");
    if (tst) {
        fwrite(&(out[0]),out.size(),1,tst);
        fclose(tst);
    }
    ShowMessage("Done");
}
//---------------------------------------------------------------------------
