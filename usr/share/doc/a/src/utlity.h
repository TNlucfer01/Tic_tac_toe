

#include <stdbool.h>
#include <stdio.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>
#include<strings.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

#define MODE_PVP 0
#define MODE_AI 1
#define LINE_THICKNESS 5
#define CELL_SIZE (SCREEN_WIDTH/3)
#define EASY 0
#define MEDIUM 1
#define HARD 2

int homeScreen = 1;  // 1 = Show home page, 0 = Start game
   // -1 = Not selected, 0 = PvP, 1 = AI
int difficulty = EASY;  // Default difficulty
#define AI_PLAYER 1
#define HUMAN_PLAYER 2

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture=NULL;
SDL_Rect imager={0,0,SCREEN_HEIGHT,SCREEN_WIDTH};
SDL_Surface* surface=NULL;
int gameMode = -1; 

typedef struct {
  int board[3][3];  // 0 = empty, 1 = player1 (X), 2 = player2 (O)
    unsigned int currentPlayer;
    bool isRunning;
} GameState;


void drawSymbols(GameState* gameState);
void draw_X(int row, int col);
void draw_O(int row, int col);
void draw_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius); 
void draw_thick_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius, int thickness); 
int WinorNot(GameState* gameState);
void resetGame(GameState* gameState);
int isfull(GameState game);

bool initSDL();
void closeSDL();
void handleMouseClick(GameState* gameState, int x, int y);
void renderGame(GameState* gameState);
void drawGrid();