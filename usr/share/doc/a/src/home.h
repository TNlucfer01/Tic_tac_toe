#include"utlity.h"
#include"ai.h"


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