#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm4 *Form4;

extern "C" {
#include "sqlite3.h"
}

__fastcall TForm4::TForm4(TComponent* Owner)
    : TForm(Owner)
{
}

void __fastcall TForm4::FormCreate(TObject *Sender)
{
    GridTop->Cells[0][0] = "Player";
    GridTop->Cells[1][0] = "Best";
    RefreshTop10();
}

static void ClearRows(TStringGrid* g)
{
    for (int r = 1; r <= 10; ++r)
    {
        g->Cells[0][r] = "";
        g->Cells[1][r] = "";
    }
}

void TForm4::RefreshTop10()
{
    ClearRows(GridTop);

    sqlite3* db = nullptr;
    int rc = sqlite3_open("game2048.db", &db);
    if (rc != SQLITE_OK || !db)
    {
        if (db) sqlite3_close(db);
        ShowMessage("Cannot open DB");
        return;
    }

    const char* sql =
        "SELECT users.login, MAX(scores.score) "
        "FROM scores JOIN users ON users.id = scores.user_id "
        "GROUP BY users.id "
        "ORDER BY MAX(scores.score) DESC "
        "LIMIT 10;";

    sqlite3_stmt* stmt = nullptr;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        ShowMessage(sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    int row = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW && row <= 10)
    {
        GridTop->Cells[0][row] = String((const char*)sqlite3_column_text(stmt, 0));
        GridTop->Cells[1][row] = String(sqlite3_column_int(stmt, 1));
        ++row;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void __fastcall TForm4::ButtonCloseClick(TObject *Sender)
{
    Close();
}

