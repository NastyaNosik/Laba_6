#pragma once
#include <array>
#include <random>

class Game2048
{
public:
    static constexpr int N = 4;

    Game2048();

    void Reset();
    bool MoveLeft();
    bool MoveRight();
    bool MoveUp();
    bool MoveDown();

    int Score() const { return score; }
    bool HasMoves() const;
    bool Has2048() const;
    int  Cell(int r, int c) const { return board[r][c]; }

private:
    std::array<std::array<int, N>, N> board{};
    int score = 0;

    std::mt19937 rng;

    bool SpawnTile();
    bool SlideAndMergeRow(std::array<int, N>& row);
};

