#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include"utlity.h"
#include<ctype.h>

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



void easyAi(GameState* GameState){
    int row,col;
    do{
        row=rand()%3;
        col=rand()%3;

    }
    while(GameState->board[row][col]!=0);
    GameState->board[row][col]=GameState->currentPlayer;
}


void mediumAI(GameState* GameState) {
    int bestRow = -1, bestCol = -1;
    float bestScore = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (GameState->board[i][j] == 0) {  // Empty cell
                float score = get_score(GameState, i, j);
                if (score > bestScore) {  // Find the best score
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    // Place AI move in the best position found
    if (bestRow != -1 && bestCol != -1) {
        GameState->board[bestRow][bestCol] = GameState->currentPlayer;
    }
}

//get a min heap of the scores

float get_score(GameState* GameState, int row, int col) {
    float scr = 0;
    int player = GameState->currentPlayer;

    // Check boundaries before accessing board elements
    if (row > 0 && GameState->board[row - 1][col] == player) scr++;  // Top
    if (row < 2 && GameState->board[row + 1][col] == player) scr++;  // Bottom
    if (col > 0 && GameState->board[row][col - 1] == player) scr++;  // Left
    if (col < 2 && GameState->board[row][col + 1] == player) scr++;  // Right

    if (row > 0 && col > 0 && GameState->board[row - 1][col - 1] == player) scr++;  // Top-left
    if (row > 0 && col < 2 && GameState->board[row - 1][col + 1] == player) scr++;  // Top-right
    if (row < 2 && col > 0 && GameState->board[row + 1][col - 1] == player) scr++;  // Bottom-left
    if (row < 2 && col < 2 && GameState->board[row + 1][col + 1] == player) scr++;  // Bottom-right

    return pow(scr, 0.5);  // Square root of score
}


void toLowerStr(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}


void call_ai(GameState* GameState) {
    switch (difficulty) {
        case EASY:
            easyAi(GameState);
            break;
        case MEDIUM:
            mediumAI(GameState);
            break;
        case HARD:
            bestMove(GameState);
            break;
    }
}



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

    if (moveRow != -1 && moveCol != -1) 
    {
        draw_X(moveRow,moveCol);
        gameState->board[moveRow][moveCol] = AI_PLAYER; // Make the best move
    }
}




