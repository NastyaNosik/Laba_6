//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Grids.hpp>

// логика игры 2048
#include "Game2048.h"

//---------------------------------------------------------------------------

class TGameForm : public TForm
{
__published:
    TLabel *LabelScore;
    TStringGrid *Grid;

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

public:
    __fastcall TGameForm(TComponent* Owner);

    // запуск игры для конкретного пользователя
    void StartGame(int userId);

private:
    Game2048 game;
    int currentUserId = -1;

    void Draw();
};

//---------------------------------------------------------------------------

extern PACKAGE TGameForm *GameForm;
//---------------------------------------------------------------------------

#endif

