//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:
    TLabel *Label1;
    TLabel *Label2;
    TEdit *EditUsername;
    TEdit *EditPassword;
    TButton *ButtonRegister;
    TButton *ButtonLogin;

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ButtonRegisterClick(TObject *Sender);
    void __fastcall ButtonLoginClick(TObject *Sender);

public:
    __fastcall TForm1(TComponent* Owner);

private:
    struct sqlite3* db; // SQLite connection
};
//---------------------------------------------------------------------------

extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------

#endif

