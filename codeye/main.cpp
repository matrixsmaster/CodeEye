//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "file_types.h"
#include "u_about.h"
#include "u_progress.h"
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
void __fastcall TForm1::OpenWindow(AnsiString fn)
{
    PEditor ptr;
	ptr = new TfrmEdit(Form1);
	windows->Add(ptr);

    // add random unique name
	AnsiString newName = "Editor_";
	newName += IntToHex(random(65536),4);
	newName += IntToHex(random(65536),4);

    // point to the file to load, and open the new editor window
	ptr->Name = newName;
	ptr->fileToOpen = fn;
	ptr->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::selFileChange(TObject *Sender)
{
	curFile = selFile->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::selFileDblClick(TObject *Sender)
{
    OpenWindow(curFile);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Randomize();
    ObfuscatePrepare();

	windows = new TList();
	windows->Clear();

	dPath = ExtractFilePath(Application->ExeName);
    rng = new CLCRNG();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	DestroyWindows();
	delete windows;
    delete rng;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DestroyWindows()
{
	PEditor ptr;
	for (int i=0; i<windows->Count; i++) {
		ptr = (PEditor)(windows->Items[i]);
		if (ptr) delete ptr;
	}
	windows->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Closeall1Click(TObject *Sender)
{
	DestroyWindows();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DriveComboBox1Change(TObject *Sender)
{
	selDir->Drive = DriveComboBox1->Drive;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
	if (selFile->Items->Count<1) {
		ShowMessage("Nothing to mix!");
		return;
	}

    // check the project's name
    AnsiString projectName = Edit1->Text;
    if (projectName.IsEmpty()) return;

    // generate resulting file name and confirm it with the user
    AnsiString c_fn = dPath + MIXPROJ_PREFIX + projectName + MIXPROJ_SUFFIX;
    sd1->FileName = c_fn;
    if (!sd1->Execute()) return;
    if (sd1->FileName.IsEmpty()) return;
    c_fn = sd1->FileName;

    // mix it up
    Generator(selDir->Directory,projectName,c_fn);
    ShowMessage("Project mixed to file:\n" + c_fn);

    // show the resulting file
    OpenWindow(c_fn);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Generator(AnsiString prjDir, AnsiString prjName, AnsiString flName)
{
	if (selFile->Items->Count<1) return;

	int totline = 0;
	TStrings* main = new TStringList();
	TStrings* forms = new TStringList();
	TStrings* projf = new TStringList();
	TStrings* tmp = new TStringList();
	AnsiString splitter;
	splitter = splitter.StringOfChar('-',SPLITTER_LEN);

    // add global header
	main->Append(DateToStr(Date())+'@'+TimeToStr(Time()));
	main->Append(MIXPROJ_HEADER);
	main->Append("");
	main->Append("Project = '"+prjName+"'");
	main->Append("");
    main->Append("");

    // prepare obfuscation
    if (CheckBox1->Checked) {
        // add disclaimer text
        //TODO
    }

    // process all files
	for (int i=0; i<selFile->Items->Count; i++) {
		AnsiString fn = selFile->Items->Strings[i];
		if (fn.IsEmpty()) continue;

        // extract and format file's extension
		AnsiString ext = ExtractFileExt(fn).UpperCase();
        if (ext.IsEmpty()) continue;
        if (ext[1] == '.') ext.Delete(1,1);

        // find appropriate file type record
        TStrings* targ = NULL;
        int typeno = -1;
        for (int j = 0; j < NUMITEMS(reg_types); j++) {
            if (AnsiString(reg_types[j].ext) != ext) continue;

            // record found
            switch (reg_types[j].appendix) {
            case 0: targ = main; break;
            case 1: targ = forms; break;
            case 2: targ = projf; break;
            default:
                ShowMessage("Unknown appendix index "+IntToStr(reg_types[j].appendix));
                // it's a fatal-type error, we don't care about memory leaks
                Application->Terminate();
            }

            typeno = j;
            break;
        }
		if (!targ || typeno < 0) continue;

        // add appropriate file header
		targ->Append("");
		targ->Append(splitter);
		targ->Append("File '" + fn + "'  " + reg_types[typeno].desc);
		targ->Append("");

        // load the file and count the lines
        tmp->LoadFromFile(prjDir + "\\" + fn);
        if (reg_types[typeno].appendix == 0)
            totline += LineCounter(tmp);

        // if requested, obfuscate the contents
        if (CheckBox1->Checked) {
            rng->setSeed(fn.c_str());
            Obfuscate(tmp,typeno);
        }
        targ->AddStrings(tmp);
	}

	// add summary information
	main->Append(splitter);
	main->Append("");
	main->Append("Total code lines count: "+IntToStr(totline));
	main->Append("");

    // add Appendix 1 (form data)
	main->Append(splitter.StringOfChar('*',CHAPTERSPLIT_LEN));
	main->Append("Appendix 1. Borland Form Files Data");
	main->Append(splitter);
    main->AddStrings(forms);
	main->Append(splitter);
	main->Append("");

    // add Appendix 2 (project files)
	main->Append(splitter.StringOfChar('*',CHAPTERSPLIT_LEN));
	main->Append("Appendix 2. Other Project Files");
	main->Append(splitter);
	main->AddStrings(projf);
	main->Append(splitter);
	main->Append("");

    // add final section
    main->Append("");
	main->Append("This file is generated by MSM's Code Eye");
	main->Append("REPO"); //FIXME: add github/lab URL
	main->Append("");

	// save the end result
	main->SaveToFile(flName);

	// free memory
	delete projf;
	delete forms;
	delete main;
	delete tmp;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
	if (once) return;
	once = true;
    
	AnsiString s;
	// params parsing
	if (ParamCount()>=1) /*set dir*/ {
		s = ParamStr(1);
		char drv = UpCase(s[1]);
		if ((drv<'A')||(drv>'Z')) return;
		selDir->Drive = drv;
		DriveComboBox1->Drive = drv;
		selDir->Directory = s;
		Application->ProcessMessages();
	}
	if (ParamCount()>=2) /*autocompile*/ {
		s = ParamStr(2);
		if (s.Length()<2) return;
		Generator(selDir->Directory,s,dPath+MIXPROJ_PREFIX+s+MIXPROJ_SUFFIX);
		Application->ProcessMessages();
	}
	if (ParamCount()>=3) /*autoclose*/ {
		if (ParamStr(3)=="close") this->Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Launchparams1Click(TObject *Sender)
{
    ShowMessage(ParamStr(0)+" [work_dir] [result_fn] [\"close\"]");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ObfuscatePrepare()
{
    size_t glen = NUMITEMS(cont_filters) * sizeof(CEOCacheLine);
    cache = (CEOCacheLine*)malloc(glen);
    memset(cache,0,glen);
    
    for (int i = 0; i < NUMITEMS(cont_filters); i++) {
        for (int j = 0; j < MAXFILTERS; j++) {
            if (!cont_filters[i].f[j]) continue;
            int len = strlen(cont_filters[i].f[j]);
            for (int k = 1; k < 256; k++) {
                const char* fnd = strchr(cont_filters[i].f[j],(char)k);
                if (fnd) {
                    cache[i].tab[k].len = len;
                    cache[i].tab[k].line = cont_filters[i].f[j];
                    cache[i].tab[k].idx = fnd - cont_filters[i].f[j];
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Obfuscate(TStrings* body, int tid)
{
    // check args and select appropriate filter
    if (!body || tid < 0) return;
    int fid = reg_types[tid].filter_id;
    if (fid < 0) return; // no filter, nothing to do

    for (int i = 0; i < body->Count; i++) {
        AnsiString str = body->Strings[i];
        for (int j = 1; j <= str.Length(); j++) {
            int l = cache[fid].tab[str[j]].len;
            if (!l) continue;

            int r = (rng->getPosInt() % l) + cache[fid].tab[str[j]].idx;
            if (r >= l) r -= l;
            str[j] = cache[fid].tab[str[j]].line[r];
        }
        body->Strings[i] = str;
    }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::Deobfuscate(CLCRNG* lrng, AnsiString str, int tid)
{
    // check args and select appropriate filter
    if (!lrng || str.IsEmpty() || tid < 0) return str;
    int fid = reg_types[tid].filter_id;
    if (fid < 0) return str; // no filter, return verbatim

    AnsiString res;
    for (int j = 1; j <= str.Length(); j++) {
        int l = cache[fid].tab[str[j]].len;
        if (!l) {
            res += str[j];
            continue;
        }

        int r = lrng->getPosInt() % l;
        int d = cache[fid].tab[str[j]].idx - r;
        if (d < 0) d += l;
        res += cache[fid].tab[str[j]].line[d];
    }
    return res;
}
//---------------------------------------------------------------------------
int __fastcall TForm1::LineCounter(TStrings* body)
{
    if (!body) return 0;
    //FIXME: do line counting based on file type (incl. short and long comments)
    return body->Count;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Openmixfile1Click(TObject *Sender)
{
    if (!od1->Execute() || od1->FileName.IsEmpty()) return;
    OpenWindow(od1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Disclaimer1Click(TObject *Sender)
{
    //TODO: edit or load disclaimer message
}
//---------------------------------------------------------------------------
