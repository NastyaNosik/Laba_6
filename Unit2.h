//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "Game2048.h"

//---------------------------------------------------------------------------

class TGameForm : public TForm
{
__published:
    TPanel *PanelTop;
    TLabel *LabelScore;
    TButton *ButtonMenu;
    TStringGrid *Grid;

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall ButtonMenuClick(TObject *Sender);

public:
    __fastcall TGameForm(TComponent* Owner);

    void StartGame(int userId);

private:
    Game2048 game;
    int currentUserId = -1;

    void Draw();
    void SaveScoreAndReturnToMenu(const String& reason);
};

//---------------------------------------------------------------------------

extern PACKAGE TGameForm *GameForm;
//---------------------------------------------------------------------------

#endif

