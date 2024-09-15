//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        AnsiString _str;
        cbox1->Clear();
        for (int i=65; i<=90; i++) {
                _str = "";
                _str += static_cast<char> (i);
                _str += ": ";
                cbox1->Items->Append(_str);
        }
        _str = "";
        _str += dirList->Drive;
        _str += ": ";
        cbox1->Text = _str;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::cbox1Change(TObject *Sender)
{
        if (cbox1->ItemIndex<0) return;
        char ch = cbox1->Text[1];
        dirList->Drive = ch;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if ( (od1->Execute())&&(!od1->FileName.IsEmpty()) )
                Edit1->Text = od1->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        CGauge1->Progress = 0;
        if (!FileExists(Edit1->Text)) {
                MessageBox(Form1->Handle,"File not found!","File Error",MB_ICONERROR);
                return;
        }
        TStrings *all = new TStringList();
        all->LoadFromFile(Edit1->Text);
        AnsiString curst = "";
        AnsiString in_file = "";
        AnsiString path = dirList->Directory + "\\";
        TStrings *cur = new TStringList();
        cur->Clear();
        bool wait = false;
        int j,f_cnt,l_cnt;
        f_cnt = l_cnt = 0;
        // processing
        for (int i=0; i<all->Count; i++) {
                CGauge1->Progress++;
                if (CGauge1->Progress>=100) CGauge1->Progress = 3;
                if (wait) {
                        wait = false;
                        continue;
                }
                curst = all->Strings[i];
                if (!in_file.IsEmpty()) {
                        if ( (!curst.IsEmpty())&&(curst[1]=='-') ) {
                                // nice view
                                j = cur->Count - 1;
                                if (cur->Strings[j].IsEmpty())
                                        cur->Delete(j);
                                l_cnt += cur->Count; // count lines
                                // save
                                cur->SaveToFile(path+in_file);
                                cur->Clear();
                                in_file = "";
                                continue;
                        } else
                                cur->Append(curst);
                } else {
                        if (curst.IsEmpty()) continue;
                        if (curst.Pos("File '")==1) {
                                curst.Delete(1,6);
                                j = curst.Pos("'");
                                if (j<2) continue;
                                in_file = curst.SubString(1,j-1);
                                wait = true;
                                f_cnt++;
                        }
                }
        }
        // free memory
        all->Clear();
        cur->Clear();
        delete all;
        delete cur;
        // Message
        ShowMessage("Statistics:\nLines: "+IntToStr(l_cnt)+"\nFiles: "+IntToStr(f_cnt));
        // The End
        CGauge1->Progress = 0;
}
//---------------------------------------------------------------------------
