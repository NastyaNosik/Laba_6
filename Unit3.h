//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

//---------------------------------------------------------------------------

class TForm3 : public TForm
{
__published:
    TLabel *LabelHello;
    TLabel *LabelBest;
    TButton *ButtonPlay;
    TButton *ButtonTop10;
    TButton *ButtonExit;

    void __fastcall ButtonPlayClick(TObject *Sender);
    void __fastcall ButtonTop10Click(TObject *Sender);
    void __fastcall ButtonExitClick(TObject *Sender);

public:
    __fastcall TForm3(TComponent* Owner);

    void Init(int userId, const String& login, int bestScore);
    void RefreshBest(); // подтянуть лучший рекорд из БД

private:
    int currentUserId;
    String currentLogin;
};

//---------------------------------------------------------------------------

extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------

#endif

