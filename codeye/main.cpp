//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "u_about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
static const AnsiString meinDataSubPath = "Data\\";
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
        Application->Terminate();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::About1Click(TObject *Sender)
{
        AboutBox->ShowModal();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::selFileChange(TObject *Sender)
{
        curFile = selFile->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::selFileDblClick(TObject *Sender)
{
        PEditor ptr;
        ptr = new TfrmEdit(Form1);
        frms->Add(ptr);
        AnsiString newName = "UniqFrmEditN_";
        newName += IntToHex(random(65536),4);
        newName += IntToHex(random(65536),4);
        ptr->Name = newName;
        ptr->fileForOpen = curFile;
        ptr->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        frms = new TList();
        frms->Clear();
        Randomize();
        dPath = ExtractFilePath(Application->ExeName) + meinDataSubPath;
        cb1->Items->Clear();
        AnsiString _str;
        for (int i=65; i<=90; i++) {
                _str = "";
                _str += static_cast<char> (i);
                _str += ": ";
                cb1->Items->Add(_str);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
        DestroyWindows();
        delete frms;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DestroyWindows()
{
        PEditor ptr;
        for (int i=0; i<frms->Count; i++) {
                ptr = (PEditor) frms->Items[i];
                if (ptr!=NULL) delete ptr;
        }
        frms->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Closeall1Click(TObject *Sender)
{
        DestroyWindows();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::cb1Change(TObject *Sender)
{
        if (cb1->ItemIndex<0) return;
        char ch = cb1->Text[1];
        selDir->Drive = ch;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if (selFile->Items->Count<1) {
                ShowMessage("Nothing to mix!");
                return;
        }
        AnsiString projectName = "";
        if (!InputQuery("Mixer","Enter project name:",projectName)) return;
        if (projectName.IsEmpty()) return;
        AnsiString cDir = selDir->Directory;
        cDir += "\\";
        AnsiString _vs,fext,vss;
        AnsiString descr0 = "";
        bool merge,formfile;
        int j;
        int totline = 0;
        TStrings *temp = new TStringList();
        TStrings *_dat = new TStringList();
        TStrings *tmp2 = new TStringList();
        temp->Clear();
        temp->Append(DateToStr(Date())+'@'+TimeToStr(Time()));
        temp->Append("MSM's Code Eye Project Mix File");
        temp->Append("");
        temp->Append("Project = '"+projectName+"'");
        temp->Append("");
        AnsiString _razdel = "";
        _razdel = _razdel.StringOfChar('-',65);
        temp->Append("");
        tmp2->Clear();
        _dat->Clear();
        for (int i=0; i<selFile->Items->Count; i++) {
                _vs = selFile->Items->Strings[i];
                if (_vs.IsEmpty()) continue;
                fext = ExtractFileExt(_vs);
                merge = false;
                formfile = false;
                if (fext.UpperCase()==".CPP") {
                        descr0 = "C++ Source File";
                        merge = true;
                }
                if (fext.UpperCase()==".H") {
                        descr0 = "C++ Header";
                        merge = true;
                }
                if (fext.UpperCase()==".HPP") {
                        descr0 = "HPP Header";
                        merge = true;
                }
                if (fext.UpperCase()==".DFM") {
                        descr0 = "Form File (DFM)";
                        formfile = true;
                        merge = true;
                }
                if (fext.UpperCase()==".XFM") {
                        descr0 = "Form File (XFM)";
                        formfile = true;
                        merge = true;
                }
                if (!merge) continue;
                _dat->LoadFromFile(cDir+_vs);
                // form?? then add to end!
                if (formfile) {
                        tmp2->Append("");
                        tmp2->Append(_razdel);
                        tmp2->Append("File '"+_vs+"'  "+descr0);
                        tmp2->Append("");
                        for (j=0; j<_dat->Count; j++)
                                tmp2->Append(_dat->Strings[j]);
                        continue; // now!
                }
                // adding
                temp->Append("");
                temp->Append(_razdel);
                temp->Append("File '"+_vs+"'  "+descr0);
                temp->Append("");
                for (j=0; j<_dat->Count; j++) {
                        vss = _dat->Strings[j];
                        temp->Append(vss);
                        if ( (!vss.IsEmpty())&&(vss.Length()>2)&&(vss[1]!='/')&&(vss[2]!='/')&&(vss[2]!='*') )
                                totline++;
                }
                temp->Append("");
        }
        // sum infos
        temp->Append(_razdel);
        temp->Append("");
        temp->Append("Total code lines count: "+IntToStr(totline));
        temp->Append("");
        temp->Append(_razdel.StringOfChar('*',80));
        temp->Append("Appendix. Form Files Data.");
        temp->Append(_razdel);
        for (j=0; j<tmp2->Count; j++)
                temp->Append(tmp2->Strings[j]);
        temp->Append(_razdel);
        temp->Append("");
        temp->Append("This report created with MSM's Code Eye");
        temp->Append("C++ Edition");
        temp->Append("");
        // save
        AnsiString c_fn = dPath+"MixProj_"+projectName+".TXT";
        temp->SaveToFile(c_fn);
        ShowMessage("Project mixed to file:\n"+c_fn);
        // free memory
        temp->Clear();
        _dat->Clear();
        tmp2->Clear();
        delete _dat;
        delete temp;
        delete tmp2;
        // show file
        PEditor ptr;
        ptr = new TfrmEdit(Form1);
        frms->Add(ptr);
        AnsiString newName = "UniqProjMixView_";
        newName += IntToHex(random(65536),4);
        newName += IntToHex(random(65536),4);
        ptr->Name = newName;
        ptr->fileForOpen = c_fn;
        ptr->Show();
}
//---------------------------------------------------------------------------
