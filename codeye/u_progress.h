//---------------------------------------------------------------------------

#ifndef u_progressH
#define u_progressH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmProgress : public TForm
{
__published:	// IDE-managed Components
    TProgressBar *pbar;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmProgress(TComponent* Owner);
    void __fastcall SetProgress(int p);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmProgress *frmProgress;
//---------------------------------------------------------------------------
#endif
