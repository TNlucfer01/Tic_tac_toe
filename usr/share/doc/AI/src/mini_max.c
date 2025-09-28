#include<stdio.h>
#include"eg.h"
#include<math.h>
#include<limits.h>
#define AI_PLAYER 1
#define HUMAN_PLAYER 2

void bestMove(GameState* gameState) {
    int bestScore = INT_MIN;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameState->board[i][j] == 0) { // Check empty spot
                gameState->board[i][j] = AI_PLAYER; // Simulate AI move
                int score = miniMax(*gameState, 0, 0); // Call minimax
                gameState->board[i][j] = 0; // Undo move

                if (score > bestScore) { // Find max score
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    if (moveRow != -1 && moveCol != -1) {
        gameState->board[moveRow][moveCol] = AI_PLAYER; // Make the best move
    }
}

int miniMax(GameState gamestate, int depth, int isMax) {
    int score = evaluate(gamestate);
    
    // Base cases (terminal states)
    if (score == 10) return score - depth; // Favor quick wins
    if (score == -10) return score + depth; // Delay opponent win
    if (isfull(gamestate)) return 0; // Draw
    
    // Maximizing player (AI)
    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (gamestate.board[i][j] == 0) {  // Check empty space
                    gamestate.board[i][j] = AI_PLAYER;
                    best = fmax(best, miniMax(gamestate, depth + 1, 0));
                    gamestate.board[i][j] = 0; // Undo move
                }
            }
        }
        return best;
    } 
    // Minimizing player (Human)
    else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (gamestate.board[i][j] == 0) {  // Check empty space
                    gamestate.board[i][j] = HUMAN_PLAYER;
                    best = fmin(best, miniMax(gamestate, depth + 1, 1));
                    gamestate.board[i][j] = 0; // Undo move
                }
            }
        }
        return best;
    }
}

int evaluate(GameState game) {
    // Check rows for victory

    for (int row = 0; row < 3; row++) {
        if (game.board[row][0] == game.board[row][1] &&
            game.board[row][1] == game.board[row][2]) {
            if (game.board[row][0] == AI_PLAYER) return +10;
            else if (game.board[row][0] == HUMAN_PLAYER) return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (game.board[0][col] == game.board[1][col] &&
            game.board[1][col] == game.board[2][col]) {
            if (game.board[0][col] == AI_PLAYER) return +10;
            else if (game.board[0][col] == HUMAN_PLAYER) return -10;
        }
    }

    // Check diagonals for victory
    if (game.board[0][0] == game.board[1][1] &&
        game.board[1][1] == game.board[2][2]) {
        if (game.board[0][0] == AI_PLAYER) return +10;
        else if (game.board[0][0] == HUMAN_PLAYER) return -10;
    }
    if (game.board[0][2] == game.board[1][1] &&
        game.board[1][1] == game.board[2][0]) {
        if (game.board[0][2] == AI_PLAYER) return +10;
        else if (game.board[0][2] == HUMAN_PLAYER) return -10;
    }

    return 0; // No winner
}



void bestmove(){

}



int main(){

}