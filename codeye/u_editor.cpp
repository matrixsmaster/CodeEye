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
#include "zipper.h"
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
            if (curst == curst.StringOfChar(SPLITTER_CHAR,SPLITTER_LEN)) {
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
            if (curst == curst.StringOfChar(SPLITTER_CHAR,SPLITTER_LEN)) {
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
void __fastcall TfrmEdit::Savecompressed1Click(TObject *Sender)
{
    if (!sd1->Execute() || sd1->FileName.IsEmpty()) return;

    // prepare buffers
    AnsiString txt = TXT->Text;
    size_t mem = zipr_bound(txt.Length());
    uint8_t* buf = (uint8_t*)malloc(mem);
    if (!buf) {
        ShowMessage("Out of memory (buf)!");
        return;
    }

    // prepare compressor state (it's too big to fit onto stack)
    zipr* state = (zipr*)malloc(sizeof(zipr));
    if (!state) {
        ShowMessage("Out of memory (state)!");
        return;
    }
    memset(state,0,sizeof(zipr));

    // run Deflate algorithm
    int r = zipr_deflate(state,buf,txt.c_str(),txt.Length(),ZIPR_LVL_MAX);
    free(state);

    if (!r) {
        ShowMessage("Error while compressing data");
        free(buf);
        return;
    }

    // save result into the output file
    FILE* f = fopen(sd1->FileName.c_str(),"wb");
    if (f) {
        uint32_t l = txt.Length();
        fwrite(&l,4,1,f);   // first 4 bytes - original length
        fwrite(buf,r,1,f);  // the rest - compressed bitstream
        fclose(f);
        ShowMessage("Done!");
    } else
        ShowMessage("Error: unable to save file");

    free(buf);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Loadcompressed1Click(TObject *Sender)
{
    if (!od1->Execute() || od1->FileName.IsEmpty()) return;

    // open file and calculate its size
    FILE* f = fopen(od1->FileName.c_str(),"rb");
    if (!f) {
        ShowMessage("Error: unable to open file");
        return;
    }

    fseek(f,0,SEEK_END);
    size_t sz = ftell(f);
    fseek(f,0,SEEK_SET);

    if (!sz || sz > MAX_FILE_SIZE) {
        ShowMessage("Error: File is too large!");
        fclose(f);
        return;
    }

    // prepare and read in the buffer
    uint8_t* buf = (uint8_t*)malloc(sz);
    if (!buf) {
        ShowMessage("Out of memory (buf)!");
        fclose(f);
        return;
    }

    int r = fread(buf,sz,1,f);
    fclose(f);

    if (!r) {
        ShowMessage("Error: Unable to read all bytes");
        free(buf);
        return;
    }

    // take the length field and prepare the result buffer
    uint32_t outl = *(uint32_t*)buf;
    if (!outl || outl > MAX_FILE_SIZE) {
        ShowMessage("Error: Uncompressed size is too large");
        free(buf);
        return;
    }
    AnsiString txt;
    txt.SetLength(outl);

    // run Inflate
    unzipr s;
    memset(&s,0,sizeof(s));
    zipr_inflate(txt.c_str(),buf+4,sz-4);

    // update the text view
    TXT->Clear();
    TXT->Text = txt;
    Caption = ExtractFileName(od1->FileName);
}
//---------------------------------------------------------------------------
static bool __fastcall valid_char(int c)
{
    if (isspace(c)) return false;
    if (c <= 32) return false;
    if (c == 127) return false;
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::ApplyROFL1Click(TObject *Sender)
{
    // Rotary ObFuscation Layer
    AnsiString pass = InputBox("Rotary ObFuscation Layer","Enter passphrase",last_pass);
    if (pass.IsEmpty()) return;
    last_pass = pass;

    CLCRNG rng;
    rng.setSeed(pass.c_str());

    // copy text to avoid updating the widget
    TStrings* res = new TStringList();
    res->AddStrings(TXT->Lines);

    // process all lines
    AnsiString cpas = pass;
    for (int i = 0, k = pass.Length()+1; i < res->Count; i++) {
        AnsiString ln = res->Strings[i];
        for (int j = 1; j <= ln.Length(); j++) {
            if (!valid_char(ln[j])) continue;
            if (k > pass.Length()) {
                k = 1;
                for (int q = 1; q <= pass.Length(); q++)
                    cpas[q] += (rng.getDWord() & 0xFF);
            }
            char n = ln[j] ^ cpas[k++];
            if (valid_char(n)) ln[j] = n;
        }
        res->Strings[i] = ln;
    }

    // update the text
    TXT->Clear();
    TXT->Lines->AddStrings(res);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Reload1Click(TObject *Sender)
{
    if (FileExists(fileToOpen))
        TXT->Lines->LoadFromFile(fileToOpen);
}
//---------------------------------------------------------------------------
