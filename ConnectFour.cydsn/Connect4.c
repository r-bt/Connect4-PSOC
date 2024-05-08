#include "Connect4.h"
#include "math.h"
#include <limits.h>
#include <stdio.h>
#include <project.h>

long long LL1 = 1;

/**
 * Bitboard Connect 4 Implementation allows for efficent move generation and evaluation
 *
 * Bitboard Layout:
6 13 20 27 34 41 48   55 62     Additional row
+---------------------+
| 5 12 19 26 33 40 47 | 54 61     top row
| 4 11 18 25 32 39 46 | 53 60
| 3 10 17 24 31 38 45 | 52 59
| 2  9 16 23 30 37 44 | 51 58
| 1  8 15 22 29 36 43 | 50 57
| 0  7 14 21 28 35 42 | 49 56 63  bottom row
+---------------------+
 *
 * See https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md
 */
long long bitboards[2] = { 0, 0 };

// Keeps track of the next available position in each column
int column_heights[7];

// Track the amount of moves made
int counter = 0;

int history[42];

int width = 7;
int height = 6;

// This map is used for valuation function - each field is assigned a value
// just like in https://web.stonehill.edu/compsci/CS211/Assignments/c43.gif
// Later boards are masked, which makes valuating given position a lot faster.
// long long MASKS[14]
//     = {
//           0, 0, 0, // 0, 1, 2
//           145135534866465, // 3
//           80298708570258, // 4
//           52785417043980, // 5
//           618475292928, // 6
//           69206016, // 7
//           4297359360, // 8 - Wrong should change
//           0, // 9
//           37748736, // 10
//           3221422080, // 11
//           0, // 12
//           25165824 // 13
//       };

long long MASKS[14]
    = {
          0, 0, 0, // 0, 1, 2
          145135534866465, // 3
          80298708570258, // 4
          52785417043980, // 5
          618475292928, // 6
          69206016, // 7
          4297359360, // 8
          0, // 9
          37748736, // 10
          3221422080, // 11
          0, // 12
          25165824 // 13
      };

// Representation of "present" masks, makes iterating over them a little easier
long long IS_VALUE_USED[14]
    = {
          0, 0, 0,
          1, 1, 1, 1, 1, 1,
          0,
          1, 1,
          0,
          1
      };

void Connect4_Init()
{
    // Reset the bitboards
    bitboards[0] = 0;
    bitboards[1] = 0;

    // Reset the column heights
    for (int i = 0; i < 7; ++i) {
        column_heights[i] = i * 7;
    }

    // Reset the amount of moves made
    counter = 0;
}

/**
 * Returns current player
 */
int Connect4_GetCurrentPlayer()
{
    return counter & 1;
}

/**
 * Returns opponent of current player
 */
int Connect4_GetOpponent()
{
    return (counter + 1) & 1;
}

/**
 * Wrapper for making a move
 */
int Connect4_Move(int column)
{
    int opponent = Connect4_GetOpponent();
    if (Connect4_IsWon(opponent)) {
        return 2; // Game is already won
    }

    if (column < 0 || column > 6) {
        return 1; // Invalid move
    }

    if (column_heights[column] > (column * 7) + 5) {
        return 1; // Invalid move
    }

    Connect4_RawMove(column);
    return 0;
}

/**
 * Make a move in the Connect 4 game
 *
 * @param column The column to make the move in
 */
void Connect4_RawMove(int column)
{
    // Get the current player
    int player = Connect4_GetCurrentPlayer();

    // Shift by the height of the column
    long long move = LL1 << column_heights[column];

    // Update the height of the column
    column_heights[column]++;

    // Update the bitboard
    bitboards[player] |= move;

    // Store the move
    history[counter] = column;

    // Increment the amount of moves made
    counter++;
}

/**
 * Wrapper for undoing a move
 */
int Connect4_UndoMove()
{
    if (counter == 0) {
        return 1; // No moves to undo
    }

    Connect4_RawUndoMove();
    return 0;
}

/**
 * Undo a move in the Connect 4 game
 *
 * @param column The column to undo the move in
 */
void Connect4_RawUndoMove()
{
    counter--;

    // Get the column the last token was placed into
    int column = history[counter];

    // Update the height of the column
    column_heights[column]--;

    // Get the last move
    long long move = LL1 << column_heights[column];

    // Get the current player
    int player = Connect4_GetCurrentPlayer();

    // Remove the move
    bitboards[player] ^= move;
}

/**
 * Check if game is won by player
 *
 * @player - player to check if won
 *
 * @return 1 if won, 0 otherwise
 */
int Connect4_IsWon(int player)
{
    long long bitboard = bitboards[player];

    int differences[] = { 1, 6, 7, 8 };
    for (int i = 0; i < 4; i++) {
        int difference = differences[i];
        long long temp = bitboard & (bitboard >> difference);
        if ((temp & (temp >> (2 * difference))) != 0) {
            return 1;
        }
    }

    return 0;
}

/**
 * Generate all possible valid moves
 */
int Connect4_GetMoves(int* moves)
{
    // TOP helps us check if column is full by marking the extra top row
    long long TOP = 0b1000000100000010000001000000100000010000001000000;

    int count = 0;
    for (int col = 0; col <= 6; col++) {
        if ((TOP & (LL1 << column_heights[col])) == 0) {
            moves[count] = col;
            count++;
        }
    }

    return count;
}

/**
 * Get the value of the current board evalualted from the perspective of the current player
 */
int Connect4_GetValue(int player)
{
    int directions[] = { 1, 6, 7, 8 }; // vert, diag, diag, horizon
    long long board = bitboards[player];

    int score = 0;

    // Count number of threes
    for (int i = 0; i < 4; i++) {
        int direction = directions[i];
        long long temp = board >> direction;
        score += __builtin_popcountl(board & temp & (temp >> direction));
    }

    // Check how favourable the position is
    for (int i = 0; i < 14; i++) {
        if (IS_VALUE_USED[i]) {
            long long mask = MASKS[i];
            score += __builtin_popcountl(board & mask) * i;
        }
    }

    return score;
}

/**
 * Negamax implementation of the Connect 4 game
 *
 * Tries to maximize the score of the board for the current player
 *
 * @param board The current board state
 * @param depth The depth to search to
 * @return The best move to make
 *
 */
struct Move Connect4_NegaMax(int depth, int alpha, int beta)
{
    int player = Connect4_GetCurrentPlayer();
    int opponent = Connect4_GetOpponent();

    if (Connect4_IsWon(opponent)) {
        // Opponent has won
        return (struct Move) { -1, -INF, 0 };
    } else if (depth == 0) {
        int score_a = Connect4_GetValue(player);
        int score_b = Connect4_GetValue(opponent);
        return (struct Move) { -1, score_a - score_b, 0 };
    }

    int moves[7];
    int count = Connect4_GetMoves(moves);

    if (count == 0) {
        // No moves left
        return (struct Move) { -1, 0, 0 };
    }

    struct Move best_result = { -1, -INF, INF };

    for (int i = 0; i < count; i++) {
        int move = moves[i];

        Connect4_RawMove(move);

        struct Move result = Connect4_NegaMax(depth - 1, -beta, -alpha);
        result.depth += 1;
        result.column = move;
        result.score = -result.score;

        Connect4_RawUndoMove();

        if (result.score > best_result.score || (result.score == best_result.score && result.depth < best_result.depth)) {
            best_result = result;
        }

        if (result.score > beta) {
            return best_result; // Prune
        }

        if (result.score > alpha) {
            alpha = result.score; // Keep track of the minimum score the player is assured of
        }
    }

    return best_result;
}

void Connect4_PrintBoard()
{
    for (int i = 5; i >= 0; i--) {
        for (int j = 0; j < 7; j++) {
            int index = i + j * 7;

            if (bitboards[0] & (LL1 << index)) {
                USBUART_PutString("X ");
                CyDelay(100);
            } else if (bitboards[1] & (LL1 << (index))) {
                USBUART_PutString("O ");
                CyDelay(100);
            } else {
                USBUART_PutString(". ");
                CyDelay(100);
            }
        }
        USBUART_PutString("\r\n");
        CyDelay(100);
    }
    USBUART_PutString("\r\n");
    CyDelay(100);
}