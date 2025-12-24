//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h"   // GameForm
#include "Unit4.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm3 *Form3;

// SQLite
extern "C" {
#include "sqlite3.h"
}

//---------------------------------------------------------------------------

__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner), currentUserId(-1)
{
}

static int GetBestScoreFromDb(int userId)
{
    sqlite3* db = nullptr;
    int rc = sqlite3_open("game2048.db", &db);
    if (rc != SQLITE_OK || !db)
    {
        if (db) sqlite3_close(db);
        return 0;
    }

    const char* sql = "SELECT COALESCE(MAX(score),0) FROM scores WHERE user_id=?;";
    sqlite3_stmt* stmt = nullptr;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_int(stmt, 1, userId);

    int best = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW)
        best = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return best;
}

void TForm3::Init(int userId, const String& login, int bestScore)
{
    currentUserId = userId;
    currentLogin = login;

    LabelHello->Caption = "Hello, " + login;
    LabelBest->Caption  = "Best score: " + String(bestScore);

    // сразу обновим реально из БД
    RefreshBest();
}

void TForm3::RefreshBest()
{
    if (currentUserId < 0) return;
    int best = GetBestScoreFromDb(currentUserId);
    LabelBest->Caption = "Best score: " + String(best);
}

void __fastcall TForm3::ButtonPlayClick(TObject *Sender)
{
    if (!GameForm)
        Application->CreateForm(__classid(TGameForm), &GameForm);

    GameForm->StartGame(currentUserId);
    Hide();
}

void __fastcall TForm3::ButtonTop10Click(TObject *Sender)
{
    if (!Form4)
        Application->CreateForm(__classid(TForm4), &Form4);

    Form4->RefreshTop10();
    Form4->ShowModal();
}



void __fastcall TForm3::ButtonExitClick(TObject *Sender)
{
    if (MessageDlg("Are you sure you want to exit?",
        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
    {
        Application->Terminate();
    }
}

//---------------------------------------------------------------------------

