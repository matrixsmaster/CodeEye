//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "u_seldest.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cdiroutl"
#pragma resource "*.dfm"
TfrmSelDest *frmSelDest;
//---------------------------------------------------------------------------
__fastcall TfrmSelDest::TfrmSelDest(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSelDest::Panel2Resize(TObject *Sender)
{
    selDrv->Width = Panel2->Width - 16;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSelDest::selDrvChange(TObject *Sender)
{
    selDir->Drive = selDrv->Drive;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSelDest::selDirChange(TObject *Sender)
{
    fileList->Directory = selDir->Directory;
}
//---------------------------------------------------------------------------
