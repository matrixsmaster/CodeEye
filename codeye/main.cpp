//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "file_types.h"
#include "u_about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    once = false;
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
        dPath = ExtractFilePath(Application->ExeName);
        cb1->Items->Clear();
        AnsiString _str;
        for (char i='A'; i<='Z'; i++) {
                _str = "";
                _str += i;
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
                if (ptr) delete ptr;
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
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
        if (selFile->Items->Count<1) {
                ShowMessage("Nothing to mix!");
                return;
        }
        AnsiString projectName = Edit1->Text;
        if (projectName.IsEmpty()) return;
        AnsiString c_fn = dPath+"MixProj_"+projectName+".TXT";
        Generator(projectName,c_fn);
        ShowMessage("Project mixed to file:\n"+c_fn);
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
void __fastcall TForm1::Generator(AnsiString prjName, AnsiString flName)
{
        if (selFile->Items->Count<1) return;
        AnsiString cDir = selDir->Directory;
        cDir += "\\";
        AnsiString _vs,fext,vss;
        AnsiString descr0 = "";
        bool merge,formfile,apd2file;
        int j;
        int totline = 0;
        TStrings *temp = new TStringList();
        TStrings *_dat = new TStringList();
        TStrings *tmp2 = new TStringList();
        TStrings *tmp3 = new TStringList();
        TStrings *_cur = NULL;
        temp->Clear();
        temp->Append(DateToStr(Date())+'@'+TimeToStr(Time()));
        temp->Append("MSM's Code Eye Project Mix File");
        temp->Append("");
        temp->Append("Project = '"+prjName+"'");
        temp->Append("");
        AnsiString _razdel = "";
        _razdel = _razdel.StringOfChar('-',65);
        temp->Append("");
        tmp2->Clear();
        tmp3->Clear();
        _dat->Clear();
        for (int i=0; i<selFile->Items->Count; i++) {
                _vs = selFile->Items->Strings[i];
                if (_vs.IsEmpty()) continue;
                fext = ExtractFileExt(_vs);
                merge = false;
                formfile = false;
                apd2file = false;
                if (fext.UpperCase()==".CPP") {
                        descr0 = "C++ Source File";
                        merge = true;
                }
                if (fext.UpperCase()==".H") {
                        descr0 = "C/C++ Header";
                        merge = true;
                }
                if (fext.UpperCase()==".HPP") {
                        descr0 = "C++ Header (HPP)";
                        merge = true;
                }
                if (fext.UpperCase()==".ASM") {
                        descr0 = "Assembler Code";
                        merge = true;
                }
                if (fext.UpperCase()==".DFM") {
                        descr0 = "Delphi Form File";
                        formfile = true;
                        merge = true;
                }
                if (fext.UpperCase()==".XFM") {
                        descr0 = "CLX Form File";
                        formfile = true;
                        merge = true;
                }
                if (fext.UpperCase()==".BPR") {
                        descr0 = "BCB Project File";
                        apd2file = true;
                        merge = true;
                }
                if (fext.UpperCase()==".RC") {
                        descr0 = "Resource Script";
                        apd2file = true;
                        merge = true;
                }
                if (fext.UpperCase()==".CLW") {
                        descr0 = "MFC Class Wizard File";
                        apd2file = true;
                        merge = true;
                }
                if (fext.UpperCase()==".DSW") {
                        descr0 = "MS DevStudio Workspace";
                        apd2file = true;
                        merge = true;
                }
                if (fext.UpperCase()==".DSP") {
                        descr0 = "MS DevStudio Project File";
                        apd2file = true;
                        merge = true;
                }
                if (!merge) continue;
                _dat->LoadFromFile(cDir+_vs);
                _cur = temp; // by default
                // form?? then add to end!
                if (formfile) _cur = tmp2;
                // files for Appendix-2
                if (apd2file) _cur = tmp3;
                // adding
                _cur->Append("");
                _cur->Append(_razdel);
                _cur->Append("File '"+_vs+"'  "+descr0);
                _cur->Append("");
                for (j=0; j<_dat->Count; j++) {
                        vss = _dat->Strings[j];
                        _cur->Append(vss);
                        if (_cur==temp) {
                            //FIXME: wrong comment detection
                                if ( (!vss.IsEmpty())&&(vss.Length()>2)&&(vss[1]!='/')&&(vss[2]!='/')&&(vss[2]!='*') )
                                        totline++;
                        }
                }
//                _cur->Append("");
        }
        // sum infos (COMPILING) ---------
        temp->Append(_razdel);
        temp->Append("");
        temp->Append("Total code lines count: "+IntToStr(totline));
        temp->Append("");
        temp->Append(_razdel.StringOfChar('*',80));
        temp->Append("Appendix 1. Borland Form Files Data.");
        temp->Append(_razdel);
        for (j=0; j<tmp2->Count; j++)
                temp->Append(tmp2->Strings[j]);
        temp->Append(_razdel);
        temp->Append("");
        temp->Append(_razdel.StringOfChar('*',80));
        temp->Append("Appendix 2. Other Project Files.");
        temp->Append(_razdel);
        for (j=0; j<tmp3->Count; j++)
                temp->Append(tmp3->Strings[j]);
        temp->Append(_razdel);
        temp->Append("");
        temp->Append("This file is generated by MSM's Code Eye");
        temp->Append("REPO"); //FIXME: add github/lab URL
        temp->Append("");
        // -------------------END COMPILE
        // save
        temp->SaveToFile(flName);
        // free memory
        temp->Clear();
        _dat->Clear();
        tmp2->Clear();
        tmp3->Clear();
        delete _dat;
        delete temp;
        delete tmp2;
        delete tmp3;
        _cur = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
        if (!once) {
                once = true;
                AnsiString s;
                // params parsing
                if (ParamCount()>=1) /*set dir*/ {
                        s = ParamStr(1);
                        char drv = UpCase(s[1]);
                        if ((drv<'A')||(drv>'Z')) return;
                        selDir->Drive = drv;
                        cb1->Text = drv;
                        selDir->Directory = s;
                        Application->ProcessMessages();
                }
                if (ParamCount()>=2) /*autocompile*/ {
                        s = ParamStr(2);
                        if (s.Length()<2) return;
                        Generator(s,dPath+"MixProj_"+s+".TXT");
                        Application->ProcessMessages();
                }
                if (ParamCount()>=3) /*autoclose*/ {
                        if (ParamStr(3)=="close") this->Close();
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Launchparams1Click(TObject *Sender)
{
    //ShowMessage(
}
//---------------------------------------------------------------------------

