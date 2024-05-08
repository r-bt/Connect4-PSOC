#ifndef Connect4_H
#define Connect4_H

#define INF 10000

struct Move {
    int column;
    int score;
    int depth;
};

void Connect4_Init();

struct Move Connect4_NegaMax(int depth, int alpha, int beta);

void Connect4_PrintBoard();

int Connect4_Move(int column);

int Connect4_IsWon(int player);

void Connect4_RawMove(int column);

void Connect4_RawUndoMove();

int Connect4_GetCurrentPlayer();

#endif