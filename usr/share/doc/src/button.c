#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Clickable Buttons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 340, 340, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Define button rectangles
    SDL_Rect yes_button = {90, 200, 70, 40}; // Yes button
    SDL_Rect no_button = {180, 200, 70, 40}; // No button

    int running = 1;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Get mouse click coordinates
                int x = event.button.x;
                int y = event.button.y;

                // Check if the click is inside the "Yes" button
                if (x >= yes_button.x && x <= yes_button.x + yes_button.w &&
                    y >= yes_button.y && y <= yes_button.y + yes_button.h) {
                    printf("Yes button clicked!\n");
                }

                // Check if the click is inside the "No" button
                if (x >= no_button.x && x <= no_button.x + no_button.w &&
                    y >= no_button.y && y <= no_button.y + no_button.h) {
                    printf("No button clicked!\n");
                }
            }
        }

        // Draw the buttons
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Background color
        SDL_RenderClear(renderer);

        // Draw "Yes" button
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
        SDL_RenderFillRect(renderer, &yes_button);

        // Draw "No" button
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
        SDL_RenderFillRect(renderer, &no_button);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}





