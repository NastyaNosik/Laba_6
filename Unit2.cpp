//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit3.h"   // Form3 (menu)

#pragma package(smart_init)
#pragma resource "*.dfm"

TGameForm *GameForm;

// SQLite
extern "C" {
#include "sqlite3.h"
}

//---------------------------------------------------------------------------

__fastcall TGameForm::TGameForm(TComponent* Owner)
    : TForm(Owner)
{
    KeyPreview = true;
}

static bool SaveScoreToDb(int userId, int score, String& err)
{
    err = "";

    sqlite3* db = nullptr;
    int rc = sqlite3_open("game2048.db", &db);
    if (rc != SQLITE_OK || !db)
    {
        err = "Cannot open DB";
        if (db) sqlite3_close(db);
        return false;
    }

    const char* sql = "INSERT INTO scores(user_id, score) VALUES(?, ?);";
    sqlite3_stmt* stmt = nullptr;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        err = sqlite3_errmsg(db);
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_int(stmt, 2, score);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE)
    {
        err = sqlite3_errmsg(db);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

void TGameForm::Draw()
{
    LabelScore->Caption = "Score: " + String(game.Score());

    for (int r = 0; r < Game2048::N; ++r)
    {
        for (int c = 0; c < Game2048::N; ++c)
        {
            int v = game.Cell(r, c);
            Grid->Cells[c][r] = (v == 0) ? "" : String(v);
        }
    }
}

void __fastcall TGameForm::FormCreate(TObject *Sender)
{
    // Ничего не стартуем тут принудительно: StartGame() делает Reset.
    Draw();
}

void TGameForm::StartGame(int userId)
{
    currentUserId = userId;
    game.Reset();
    Draw();
    Show();
}

void TGameForm::SaveScoreAndReturnToMenu(const String& reason)
{
    if (currentUserId >= 0)
    {
        String err;
        SaveScoreToDb(currentUserId, game.Score(), err);
        // Если err не пустой — можно ShowMessage(err), но не обязателен.
    }

    // показать меню и обновить рекорд
    if (Form3)
    {
        Form3->RefreshBest();
        Form3->Show();
    }
    Hide();
}

void __fastcall TGameForm::ButtonMenuClick(TObject *Sender)
{
    if (MessageDlg("Return to menu? Current score will be saved.",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
    {
        SaveScoreAndReturnToMenu("menu");
    }
}

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

    if (!moved) return;

    Draw();

    if (!game.HasMoves())
    {
        ShowMessage("Game Over! Score saved.");
        SaveScoreAndReturnToMenu("gameover");
        return;
    }

    if (game.Has2048())
    {
        // не останавливаем игру, просто уведомляем
        // (можно убрать, если мешает)
        ShowMessage("2048 reached!");
    }
}

//---------------------------------------------------------------------------

