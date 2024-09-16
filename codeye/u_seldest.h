//---------------------------------------------------------------------------

#ifndef u_seldestH
#define u_seldestH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cdiroutl.h"
#include <FileCtrl.hpp>
#include <Grids.hpp>
#include <Outline.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmSelDest : public TForm
{
__published:    // IDE-managed Components
    TDriveComboBox *selDrv;
    TFileListBox *fileList;
    TPanel *Panel1;
    TSplitter *Splitter1;
    TPanel *Panel2;
    TDirectoryListBox *selDir;
    TPanel *Panel3;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TBitBtn *BitBtn3;
    TEdit *nDirName;
    void __fastcall Panel2Resize(TObject *Sender);
    void __fastcall selDrvChange(TObject *Sender);
    void __fastcall selDirChange(TObject *Sender);
    void __fastcall BitBtn3Click(TObject *Sender);
private:    // User declarations
public:        // User declarations
    __fastcall TfrmSelDest(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelDest *frmSelDest;
//---------------------------------------------------------------------------
#endif
