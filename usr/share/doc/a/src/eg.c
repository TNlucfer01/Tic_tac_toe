#include <stdbool.h>
#include <stdio.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include<SDL2/SDL_mixer.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>

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
#define AI_PLAYER  2 
#define HUMAN_PLAYER 1



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


/* Function Prototypes */
bool initSDL();
void closeSDL();
void handleMouseClick(GameState* gameState, int x, int y);
void renderGame(GameState* gameState);
void drawGrid();
float get_score(GameState* GameState, int row, int col);
void easyAi(GameState* GameState);
void mediumAI(GameState* GameState);
int aiChose(char choice[10],GameState* GameState);
void toLowerStr(char *str);


void handleMenuClick(int x, int y);
void renderFrontPage(SDL_Renderer *renderer);

void bestMove(GameState* gameState);
int miniMax(GameState *gamestate, int depth, int isMax);
int evaluate(GameState game);
void drawSymbols(GameState* gameState);
void draw_X(int row, int col);
void draw_O(int row, int col);
int playagain();
void draw_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius); 
void draw_thick_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius, int thickness); 
int WinorNot(GameState* gameState);
void resetGame(GameState* gameState);
int isfull(GameState game);

/**
 *   SDL Initialization 
 * it creates the window and the renderer for the game 
 * @return:true if the creation is sucess else false */
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    surface =SDL_LoadBMP("/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/assets/image/t.bmp");
    SDL_SetWindowIcon(window,surface);


    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    surface=SDL_LoadBMP("IC_TAC_TOE/usr/share/doc/assets/image/welcome_message.bmp");
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,&imager);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    return true;
}

/**
 *   Close SDL and cleanup 
 * cleaning all the file and closing the program */
void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


    int playagain(GameState* game) {   
        SDL_Window* newwin = SDL_CreateWindow(
            "Would you like to restart the game?",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            340,
            340,
            0
        );

        if (!newwin) {
            printf("Could not create window: %s\n", SDL_GetError());
            return 0;
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(newwin, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            printf("Could not create renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(newwin);
            return 0;
        }

        SDL_Surface* image = SDL_LoadBMP("/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/assets/image/yes.bmp");
        if (!image) {
            printf("Could not load image: %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(newwin);
            return 0;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);  // Free the surface after creating the texture
        if (!texture) {
            printf("Could not create texture: %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(newwin);
            return 0;
        }
        SDL_Rect rect = {0, 0, 340, 340};
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);

        SDL_Event event;
        int restart = 0;
        SDL_Rect yes={90,200,70,40};
        SDL_Rect no={180,200,70,40};

        // Event loop to wait for the user's input
        while (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
              
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_y) {
                    yes:
                    resetGame(game);
                    restart = 1;
                    break;
                } else if (event.key.keysym.sym == SDLK_n) {
                    
                    no:
                    break;
                }
            }
                else if(event.type== SDL_MOUSEBUTTONDOWN){
                    int x=event.button.x;
                    int y=event.button.y;
                    // Check if the click is inside the "Yes" button
                if (x >= yes.x && x <= yes.x + yes.w &&
                    y >= yes.y && y <= yes.y + yes.h) {
                        goto yes;
                }

                // Check if the click is inside the "No" button
                if (x >= no.x && x <= no.x + no.w &&
                    y >= no.y && y <= no.y + no.h) {
                        goto no;
                }
            }
        }

        // Clean up resources
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(newwin);

        return restart;
    }


void toLowerStr(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}


/** 
 *  Handle Mouse Click Events
 * it handeles the mouse click based on the box it have
 * clicked and print draw the X or O 
 *  then it also checks for the wins and the draw print the winner 
 * @param gameState: determine the game results 
 * @param x: the x axis of the click 
 * @param y: the y axis of the click  
 * @return : none */
void handleMouseClick(GameState* gameState, int x, int y) {
    int row = y / CELL_SIZE;
    int col = x / CELL_SIZE;

    if (gameState->board[row][col] == 0) {  // Only allow moves in empty cells
        gameState->board[row][col] = gameState->currentPlayer;

        renderGame(gameState); // Immediately update the board so the human move is visible.

        if (WinorNot(gameState)) {
            surface = SDL_LoadBMP("/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/assets/image/tic_win.bmp");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &imager);
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);
            printf("Player %d wins!\n", gameState->currentPlayer);
            gameState->isRunning = false;  // Stop the game
        }  
        else if (isfull((*gameState)) == 1) {
            SDL_Delay(1000);
            surface = SDL_LoadBMP("/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/assets/image/tic_tac_toe_draw.bmp");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(4000);
            gameState->isRunning = false;
        }
        else {
            // Switch to AI turn before calling bestMove()
            if (gameState->currentPlayer == HUMAN_PLAYER) {
                gameState->currentPlayer = AI_PLAYER;
                SDL_Delay(500);  // Add a delay so the human move is visible
                bestMove(gameState);  // AI makes a move
                renderGame(gameState); // Update the board again after AI move
                gameState->currentPlayer = HUMAN_PLAYER; // Switch back to human after AI move
            }
        }
    }
}

/** 
 *  Render the entire game (grid and symbols) 
 * @param gameState: the current game state */
void renderGame(GameState* gameState) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    drawGrid();
    drawSymbols(gameState);

    SDL_RenderPresent(renderer);
}

/**  Draw the Tic-Tac-Toe Grid 
 * with 9 cells inn it 
*/
void drawGrid() {
    SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
    
    // Vertical lines
    for (int i = 1; i < 3; ++i) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT);
    }
    
    // Horizontal lines
    for (int i = 1; i < 3; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE);
    }
}

/**  Draw X and O Symbols 
 * it draws the x or O in the window based the game state 
 * @param game state:current game state 
*/
void drawSymbols(GameState* gameState) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (gameState->board[row][col] == 1) {
                draw_X(row, col);
            } else if (gameState->board[row][col] == 2) {
                draw_O(row, col);
            }
        }
    }
}

/**  Draw X Symbol
 * in the grid
 * it  draws the x in the window based the game state 
 * @param row: the row the grid 
 * @param col: the colum of the grid to draw 
 */
void draw_X(int row, int col ) {
    int cell_size = SCREEN_HEIGHT/ 3;  // Size of each cell
    int padding = 15;                  // Padding from the edges of the cell
    int startX = col * cell_size + padding;
    int startY = row * cell_size + padding;
    int endX = (col + 1) * cell_size - padding;
    int endY = (row + 1) * cell_size - padding;

    // Set the color for the "X"
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);  // Red color for "X"

    // Thickness of the lines
    int thickness = 5;  // Change this value to increase or decrease thickness

    // Draw diagonal lines to form an "X" with thickness
    for (int i = -thickness / 2; i <= thickness / 2; i++) {
        // Top-left to bottom-right diagonal
        SDL_RenderDrawLine(renderer, startX + i, startY, endX + i, endY);
        // Bottom-left to top-right diagonal
        SDL_RenderDrawLine(renderer, startX + i, endY, endX + i, startY);
    }
}

/**  Draw O Symbol
 * in the grid
 * it  draws the O in the window based the game state 
 * @param row: the row the grid 
 * @param col: the colum of the grid to draw 
 */

void draw_O( int row, int col) {
    int cell_size = SCREEN_HEIGHT / 3;  // Calculate the size of each cell
    int centerX = (col * cell_size) + (cell_size / 2);
    int centerY = (row * cell_size) + (cell_size / 2);
    int radius = cell_size / 4;  // Adjust the circle's radius to fit in the cell

    draw_thick_circle(renderer, centerX, centerY, radius,5);
}

/** to draw a thick O
 * it is called by draw_O
 */
void draw_thick_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius, int thickness) {
    for (int i = 0; i < thickness; ++i) {
        
        draw_circle(renderer, centerX, centerY, radius + i);
        draw_circle(renderer, centerX, centerY, radius - i);
    }

}
/** to draw the circle 
 * it is to  draw a circle in the window
 * it is called by @func:draw_thick_circle
 */
void draw_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int p = 1 - radius;

    // Draw initial points on the circle
    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
    SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

    while (x > y) {
        y++;
        if (p <= 0) {
            p = p + 2 * y + 1;
        } else {
            x--;
            p = p + 2 * y - 2 * x + 1;
        }


        // Draw the circle's octants
        
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
    }
}


/** it is check wheter the game is finsihed or not 
 * @returns 1 if win else  0 draw
 */ 
int WinorNot(GameState* gameState) {
    int b[3][3];
memcpy(b, gameState->board, sizeof(b));

    
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((b[i][0] == b[i][1] && b[i][1] == b[i][2] && b[i][0] != 0) ||
            (b[0][i] == b[1][i] && b[1][i] == b[2][i] && b[0][i] != 0)) {
            return gameState->currentPlayer;
        }
    }
    
    // Check diagonals
    if ((b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] != 0) ||
        (b[0][2] == b[1][1] && b[1][1] == b[2][0] && b[0][2] != 0)) {
        return gameState->currentPlayer;
    }

    
    return 0;  // No winner yet
}
/**
 * this function is used to ckeck for draw 
 * @return:1 if the board is full 
 * @param gameState :  the current state of the game
 * 
 */
int isfull(GameState game){
    int (*a)[3]=game.board;
    int c = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (a[i][j] == 1||a[i][j]==2) {
                c++;
            }
        }
    }
    return (c == 9);  // Returns 1 if board is full
}


/**  Reset the game state 
 * it resets the board ans the game  state
*/
void resetGame(GameState* gameState) {
    gameState->currentPlayer = 1;
    gameState->isRunning = true;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            gameState->board[row][col] = 0;
        }
    }
}
void renderHomePage(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);

    SDL_Rect continueButton = {100, 50, 200, 50};
    SDL_Rect newGameButton = {100, 120, 200, 50};
    SDL_Rect optionsButton = {100, 190, 200, 50};
    SDL_Rect exitButton = {100, 260, 200, 50};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green for Continue
    SDL_RenderFillRect(renderer, &continueButton);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Blue for New Game
    SDL_RenderFillRect(renderer, &newGameButton);

    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);  // Orange for Options
    SDL_RenderFillRect(renderer, &optionsButton);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red for Exit
    SDL_RenderFillRect(renderer, &exitButton);

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
}
void handleHomeClick(int x, int y) {
    if (x >= 100 && x <= 300) {
        if (y >= 50 && y <= 100) {
            homeScreen = 0;  // Continue the last game
        } else if (y >= 120 && y <= 170) {
            homeScreen = 0;
            gameMode = -1;  // Go to mode selection
        } else if (y >= 190 && y <= 240) {
            printf("Options selected: Change AI difficulty.\n");
            // Implement difficulty selection here
        } else if (y >= 260 && y <= 310) {
            exit(0);  // Exit game
        }
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




    /* Main Function */
    int main(int argc, char* argv[]) {
        
        if (!initSDL()) {
            printf("Failed to initialize!\n");
            return -1;
        }
        start:
        GameState gameState;
        resetGame(&gameState);
        
        while (gameState.isRunning) {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    gameState.isRunning = false;
                } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    handleMouseClick(&gameState, x, y);
                }
            }
            
            renderGame(&gameState);

            SDL_Delay(100);
        }
        int restart=playagain(&gameState);
        if (restart==1)
        {
        goto start; /* code */
        }
        closeSDL();
        return 0;
    }

/* Main Function 
int main(int argc, char* args[]) {
    if (!initSDL()) {
        printf("Failed to initialize!\n");
        return -1;
    }
    
    GameState gameState;
    resetGame(&gameState);
    
    while (gameState.isRunning) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                gameState.isRunning = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN ) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(gameMode==-1) {
                    handleMenuClick(x, y);
                } else {
                handleMouseClick(&gameState, x, y);
                }
            }
        }
        if(gameMode==-1) {
            renderFrontPage(renderer);
        } else {
        renderGame(&gameState);
        }
        SDL_Delay(100);
    }

    closeSDL();
    return 0;
}
*/

void bestMove(GameState* gameState) {
    int bestScore = INT_MIN;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameState->board[i][j] == 0) { // Check empty spot
                gameState->board[i][j] = AI_PLAYER; // Simulate AI move
                int score = miniMax(gameState, 0, 0); // Call minimax
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
        gameState->board[moveRow][moveCol] = AI_PLAYER; // Make the best move
    }
    SDL_Delay(700);
}




int miniMax(GameState *gamestate, int depth, int isMax) {
    int score = evaluate(*gamestate);
    
    // Base cases (terminal states)
    if (score == 10) return score - depth; // Favor quick wins
    if (score == -10) return score + depth; // Delay opponent win
    if (isfull(*gamestate)) return 0; // Draw
    
    // Maximizing player (AI)
    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (gamestate->board[i][j] == 0) {  // Check empty space
                    gamestate->board[i][j] = AI_PLAYER;
                    best = fmax(best, miniMax(gamestate, depth + 1, 0));
                    gamestate->board[i][j] = 0; // Undo move
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
                if (gamestate->board[i][j] == 0) {  // Check empty space
                    gamestate->board[i][j] = HUMAN_PLAYER;
                    best = fmin(best, miniMax(gamestate, depth + 1, 1));
                    gamestate->board[i][j] = 0; // Undo move
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

    }while(GameState->board[row][col]!=0);
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


int aiChose(char choice[10],GameState* GameState){
 toLowerStr(choice);
    if(strcmp("easy",choice)==0){
        easyAi(GameState);     
    }
    else if (strcmp("medium",choice)==0){
        mediumAI(GameState);
    }  
else if(strcmp("hard",choice)){
    bestMove(GameState);
    return 3;
}
else{
    printf("enter a valid choice");
    return 0;
} 
}


#ifdef _WIN32
#include <windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return main(__argc, __argv);
}
#endif
