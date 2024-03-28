#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SDL.h>

int main(int argc, char* argv[]) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window with SDL Input", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Initialize SDL for event handling
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window close, etc.)
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) {
                    std::cout << "Left arrow key was pressed." << std::endl;
                }
            }
            // Handle other SDL events here
        }

        // OpenGL rendering commands
        glClear(GL_COLOR_BUFFER_BIT);
        // ...render with OpenGL...

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    SDL_Quit();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
