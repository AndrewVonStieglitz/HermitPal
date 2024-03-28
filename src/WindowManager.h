#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class WindowManager {
   public:
    GLFWwindow* window;

    WindowManager(unsigned int width, unsigned int height, const char* title) : window(nullptr) {
        if (!initializeGLFW()) return;
        createWindow(width, height, title);
        if (window == nullptr) return;

        glfwSetFramebufferSizeCallback(window, WindowManager::framebuffer_size_callback);

        if (!initializeOpenGL()) return;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    ~WindowManager() {
        glfwTerminate();
    }

    bool isRunning() {
        return !glfwWindowShouldClose(window);
    }

    void pollEvents() {
        glfwPollEvents();
    }

    void swapBuffers() {
        glfwSwapBuffers(window);
    }

   private:
    bool initializeGLFW() {
        if (!glfwInit()) {
            return false;
        }
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        return true;
    }

    void createWindow(unsigned int width, unsigned int height, const char* title) {
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL) {
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
    }

    bool initializeOpenGL() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            return false;
        }
        return true;
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        constexpr float desiredAspectRatio = 16.0f / 9.0f;
        float windowAspectRatio = width / (float)height;
        int viewportWidth, viewportHeight;

        if (windowAspectRatio > desiredAspectRatio) {
            viewportHeight = height;
            viewportWidth = static_cast<int>(height * desiredAspectRatio);
        } else {
            viewportWidth = width;
            viewportHeight = static_cast<int>(width / desiredAspectRatio);
        }

        int viewportX = (width - viewportWidth) / 2;
        int viewportY = (height - viewportHeight) / 2;

        glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    }
};