#include "SDL.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* hiddenWindow = SDL_CreateWindow(
        "Hidden SDL2 Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        100,
        100,
        SDL_WINDOW_HIDDEN); // This window remains hidden

    if (hiddenWindow == NULL) {
        SDL_Log("Could not create hidden window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* visibleWindow = SDL_CreateWindow(
        "Visible SDL2 Window", // Title for the second window
        SDL_WINDOWPOS_CENTERED, // Center the window
        SDL_WINDOWPOS_CENTERED, // Center the window
        640, // Width of the window
        480, // Height of the window
        SDL_WINDOW_SHOWN); // Make this window visible

    if (visibleWindow == NULL) {
        SDL_Log("Could not create visible window: %s\n", SDL_GetError());
        SDL_DestroyWindow(hiddenWindow); // Cleanup hidden window
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                // Check which key was pressed
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        SDL_Log("Up arrow key pressed\n");
                        break;
                    case SDLK_DOWN:
                        SDL_Log("Down arrow key pressed\n");
                        break;
                    case SDLK_LEFT:
                        SDL_Log("Left arrow key pressed\n");
                        break;
                    case SDLK_RIGHT:
                        SDL_Log("Right arrow key pressed\n");
                        break;
                    default:
                        // Other key pressed; do nothing
                        break;
                }
            }
        }
    }

    SDL_DestroyWindow(hiddenWindow); // Cleanup hidden window
    SDL_DestroyWindow(visibleWindow); // Cleanup visible window
    SDL_Quit();

    return 0;
}
