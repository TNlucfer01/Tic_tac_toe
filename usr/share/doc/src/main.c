    /*
    Tic-Tac-Toe Game - A simple graphical Tic-Tac-Toe game using SDL.

    Copyright (C) 2024  Aathi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

   #include <stdbool.h>
   
    #include <stdio.h>
    #include<SDL2/SDL.h>
    #include<SDL2/SDL_mixer.h>
    #include<string.h>
    #define SCREEN_WIDTH 640
    #define SCREEN_HEIGHT 640
    #define LINE_THICKNESS 5
    #define CELL_SIZE (SCREEN_WIDTH/3)

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture=NULL;
    SDL_Rect imager={0,0,SCREEN_HEIGHT,SCREEN_WIDTH};
    SDL_Surface* surface=NULL;
    Mix_Music* music=NULL;

    typedef struct {
        int board[3][3];  // 0 = empty, 1 = player1 (X), 2 = player2 (O)
        int currentPlayer;
        bool isRunning;
    } GameState;

    void playSong();
    /* Function Prototypes */
    void stopsong();
    bool initSDL();
    void closeSDL();
    void handleMouseClick(GameState* gameState, int x, int y);
    void renderGame(GameState* gameState);
    void drawGrid();
    void drawSymbols(GameState* gameState);
    void draw_X(int row, int col);
    void draw_O(int row, int col);
    void draw_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius); 
    void draw_thick_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius, int thickness); 
    int checkWin(GameState* gameState);
    void resetGame(GameState* gameState);
    int isfull(GameState* game);

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
        surface =SDL_LoadBMP("TIC_TAC_TOE/usr/share/doc/assets/image/t.bmp");
        SDL_SetWindowIcon(window,surface);
         // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("SDL_mixer could not initialize! Mix Error: %s\n", Mix_GetError());
            return 1;
        }

        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        surface=SDL_LoadBMP("/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/assets/image/welcome_message.bmp");
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
        playSong("../assets/music/monster.mp3");
        
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

            if(checkWin(gameState)) {
                surface=SDL_LoadBMP("/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/assets/image/tic_win.bmp");
                texture=SDL_CreateTextureFromSurface(renderer,surface);
                SDL_FreeSurface(surface);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,texture,NULL,&imager);
                SDL_RenderPresent(renderer);
                SDL_Delay(2000);
                printf("Player %d wins!\n", gameState->currentPlayer);
                gameState->isRunning = false;  // Stop the game
            }  
            else if (isfull(gameState)==1)
        {      SDL_Delay(1000);
            surface=SDL_LoadBMP("/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/assets/image/tic_tac_toe_draw.bmp");
            texture=SDL_CreateTextureFromSurface(renderer,surface);
            SDL_FreeSurface(surface);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
                SDL_Delay(4000);
            gameState->isRunning=false;
        }else {
                gameState->currentPlayer = (gameState->currentPlayer == 1) ? 2 : 1;  // Switch players
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
void playSong(const char *songName) {

    music = Mix_LoadMUS(songName);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    // Play the music in an infinite loop (-1 means loop forever)
    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Failed to play music: %s\n", Mix_GetError());
    }

    // Wait for user to press 'q' to stop music

    // Clean up
   
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
    int checkWin(GameState* gameState) {
        int (*b)[3] = gameState->board;
        
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
    int isfull(GameState* game){
        int (*a)[3]=game->board;
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
        Mix_PauseMusic(); 
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
                    Mix_ResumeMusic();
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

    #ifdef _WIN32
    #include <windows.h>

    int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
        return main(__argc, __argv);
    }
    #endif
