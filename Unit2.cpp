//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

TGameForm *GameForm;

//---------------------------------------------------------------------------

__fastcall TGameForm::TGameForm(TComponent* Owner)
    : TForm(Owner)
{
    KeyPreview = true;
}

//---------------------------------------------------------------------------

void TGameForm::Draw()
{
    if (LabelScore)
        LabelScore->Caption = "Score: " + String(game.Score());

    if (!Grid) return;

    for (int r = 0; r < Game2048::N; ++r)
    {
        for (int c = 0; c < Game2048::N; ++c)
        {
            int v = game.Cell(r, c);
            Grid->Cells[c][r] = (v == 0) ? "" : String(v);
        }
    }
}

//---------------------------------------------------------------------------

void __fastcall TGameForm::FormCreate(TObject *Sender)
{
    game.Reset();
    Draw();
}

//---------------------------------------------------------------------------

void __fastcall TGameForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    bool moved = false;

    switch (Key)
    {
        case VK_LEFT:  moved = game.MoveLeft();  break;
        case VK_RIGHT: moved = game.MoveRight(); break;
        case VK_UP:    moved = game.MoveUp();    break;
        case VK_DOWN:  moved = game.MoveDown();  break;
        default: break;
    }

    if (moved)
    {
        Draw();

        if (!game.HasMoves())
            ShowMessage("Game Over");
        else if (game.Has2048())
            ShowMessage("2048!");
    }
}

//---------------------------------------------------------------------------

void TGameForm::StartGame(int userId)
{
    currentUserId = userId;
    game.Reset();
    Draw();
    Show();
}
//---------------------------------------------------------------------------

