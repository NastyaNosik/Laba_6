#include "Game2048.h"
#include <algorithm>
#include <chrono>

Game2048::Game2048()
{
    auto seed = (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(seed);
    Reset();
}

void Game2048::Reset()
{
    for (auto& r : board) r.fill(0);
    score = 0;
    SpawnTile();
    SpawnTile();
}

bool Game2048::SpawnTile()
{
    std::array<std::pair<int,int>, 16> empty{};
    int k = 0;
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            if (board[r][c] == 0) empty[k++] = {r,c};

    if (k == 0) return false;

    std::uniform_int_distribution<int> pick(0, k - 1);
    auto [r,c] = empty[pick(rng)];

    std::uniform_int_distribution<int> chance(1, 10);
    board[r][c] = (chance(rng) == 10) ? 4 : 2;
    return true;
}

bool Game2048::SlideAndMergeRow(std::array<int, N>& row)
{
    std::array<int, N> original = row;

    std::array<int, N> tmp{};
    int t = 0;
    for (int i = 0; i < N; ++i)
        if (row[i] != 0) tmp[t++] = row[i];

    for (int i = 0; i < N - 1; ++i)
    {
        if (tmp[i] != 0 && tmp[i] == tmp[i+1])
        {
            tmp[i] *= 2;
            score += tmp[i];
            tmp[i+1] = 0;
            ++i;
        }
    }

    std::array<int, N> res{};
    t = 0;
    for (int i = 0; i < N; ++i)
        if (tmp[i] != 0) res[t++] = tmp[i];

    row = res;
    return row != original;
}

bool Game2048::MoveLeft()
{
    bool moved = false;
    for (int r = 0; r < N; ++r)
        moved |= SlideAndMergeRow(board[r]);
    if (moved) SpawnTile();
    return moved;
}

bool Game2048::MoveRight()
{
    bool moved = false;
    for (int r = 0; r < N; ++r)
    {
        auto row = board[r];
        std::reverse(row.begin(), row.end());
        bool m = SlideAndMergeRow(row);
        std::reverse(row.begin(), row.end());
        if (m) board[r] = row;
        moved |= m;
    }
    if (moved) SpawnTile();
    return moved;
}

bool Game2048::MoveUp()
{
    bool moved = false;
    for (int c = 0; c < N; ++c)
    {
        std::array<int, N> col{};
        for (int r = 0; r < N; ++r) col[r] = board[r][c];

        bool m = SlideAndMergeRow(col);
        if (m)
            for (int r = 0; r < N; ++r) board[r][c] = col[r];

        moved |= m;
    }
    if (moved) SpawnTile();
    return moved;
}

bool Game2048::MoveDown()
{
    bool moved = false;
    for (int c = 0; c < N; ++c)
    {
        std::array<int, N> col{};
        for (int r = 0; r < N; ++r) col[r] = board[r][c];

        std::reverse(col.begin(), col.end());
        bool m = SlideAndMergeRow(col);
        std::reverse(col.begin(), col.end());

        if (m)
            for (int r = 0; r < N; ++r) board[r][c] = col[r];

        moved |= m;
    }
    if (moved) SpawnTile();
    return moved;
}

bool Game2048::Has2048() const
{
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            if (board[r][c] >= 2048) return true;
    return false;
}

bool Game2048::HasMoves() const
{
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            if (board[r][c] == 0) return true;

    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
        {
            int v = board[r][c];
            if (r + 1 < N && board[r+1][c] == v) return true;
            if (c + 1 < N && board[r][c+1] == v) return true;
        }
    return false;
}

