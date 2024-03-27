#include "SDL.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO); 

    SDL_Window* window = SDL_CreateWindow(
        "An SDL2 window",          
        SDL_WINDOWPOS_UNDEFINED,   
        SDL_WINDOWPOS_UNDEFINED,   
        640,                       
        480,                      
        SDL_WINDOW_OPENGL          
    );

    if (window == NULL) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
