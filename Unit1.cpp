//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

extern "C" {
#include "sqlite3.h"
}

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner), db(nullptr)
{
    // Гарантируем, что инициализация/закрытие вызовутся даже если Events не назначены в DFM
    this->OnCreate = FormCreate;
    this->OnDestroy = FormDestroy;
}

static void ExecSQL(sqlite3* db, const char* sql)
{
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        String msg = String("SQLite error: ") + (errMsg ? errMsg : "unknown");
        sqlite3_free(errMsg);
        throw Exception(msg);
    }
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    // Открываем/создаём БД рядом с exe
    int rc = sqlite3_open("game2048.db", &db);
    if (rc != SQLITE_OK || db == nullptr)
    {
        throw Exception("Cannot open game2048.db");
    }

    // Создаём таблицы
    ExecSQL(db,
        "CREATE TABLE IF NOT EXISTS users ("
        " id INTEGER PRIMARY KEY AUTOINCREMENT,"
        " login TEXT UNIQUE NOT NULL,"
        " password TEXT NOT NULL"
        ");");

    ExecSQL(db,
        "CREATE TABLE IF NOT EXISTS scores ("
        " id INTEGER PRIMARY KEY AUTOINCREMENT,"
        " user_id INTEGER NOT NULL,"
        " score INTEGER NOT NULL,"
        " FOREIGN KEY (user_id) REFERENCES users(id)"
        ");");
}

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

static bool RegisterUser(sqlite3* db, const String& login, const String& password)
{
    const char* sql = "INSERT INTO users(login, password) VALUES(?, ?);";
    sqlite3_stmt* stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        ShowMessage(String("SQLite prepare error: ") + sqlite3_errmsg(db));
        return false;
    }

    AnsiString l = AnsiString(login);
    AnsiString p = AnsiString(password);

    sqlite3_bind_text(stmt, 1, l.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, p.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE)
    {
        ShowMessage(String("SQLite insert error: ") + sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}


static int LoginUser(sqlite3* db, const String& login, const String& password)
{
    const char* sql = "SELECT id FROM users WHERE login = ? AND password = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return -1;

    AnsiString l = AnsiString(login);
    AnsiString p = AnsiString(password);

    sqlite3_bind_text(stmt, 1, l.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, p.c_str(), -1, SQLITE_TRANSIENT);

    int userId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW)
        userId = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    return userId;
}

void __fastcall TForm1::ButtonRegisterClick(TObject *Sender)
{
    if (!db)
{
    ShowMessage("База не открыта. Проверьте FormCreate/OnCreate. Пытаюсь открыть...");
    int rc = sqlite3_open("game2048.db", &db);
    if (rc != SQLITE_OK || !db)
    {
        ShowMessage(String("Cannot open DB: ") + (db ? sqlite3_errmsg(db) : "db=null"));
        return;
    }
}
    String login = EditUsername->Text.Trim();
	String pass  = EditPassword->Text;

    if (login.IsEmpty() || pass.IsEmpty())
    {
        ShowMessage("Введите логин и пароль.");
        return;
    }

    if (RegisterUser(db, login, pass))
        ShowMessage("Регистрация успешна.");
    else
        ShowMessage("Не удалось зарегистрировать (логин может быть занят).");
}

void __fastcall TForm1::ButtonLoginClick(TObject *Sender)
{
    if (!db)
{
    ShowMessage("База не открыта. Проверьте FormCreate/OnCreate. Пытаюсь открыть...");
    int rc = sqlite3_open("game2048.db", &db);
    if (rc != SQLITE_OK || !db)
    {
        ShowMessage(String("Cannot open DB: ") + (db ? sqlite3_errmsg(db) : "db=null"));
        return;
    }
}

    String login = EditUsername->Text.Trim();
    String pass  = EditPassword->Text;

    if (login.IsEmpty() || pass.IsEmpty())
    {
        ShowMessage("Введите логин и пароль.");
        return;
    }

    int userId = LoginUser(db, login, pass);
    if (userId >= 0)
        ShowMessage("Вход успешен. user_id = " + String(userId));
    else
        ShowMessage("Неверный логин или пароль.");
}

//---------------------------------------------------------------------------

