//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main.cpp", Form1);
USEFORM("u_editor.cpp", frmEdit);
USEFORM("u_about.cpp", AboutBox);
USEFORM("u_seldest.cpp", frmSelDest);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "Code Eye";
		Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TAboutBox), &AboutBox);
         Application->CreateForm(__classid(TfrmSelDest), &frmSelDest);
         Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
