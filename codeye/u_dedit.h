//---------------------------------------------------------------------------

#ifndef u_deditH
#define u_deditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmDEdit : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    TPanel *Panel1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmDEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDEdit *frmDEdit;
//---------------------------------------------------------------------------
#endif
