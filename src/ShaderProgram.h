#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ShaderProgram {
   public:
    // Constructor modified to take file paths
    ShaderProgram(const std::string& vertexFilePath, const std::string& fragmentFilePath) {
        std::string vertexCode = readFile(vertexFilePath);
        std::string fragmentCode = readFile(fragmentFilePath);
        const char* vertexShaderSource = vertexCode.c_str();
        const char* fragmentShaderSource = fragmentCode.c_str();

        compileShader(vertexShaderSource, GL_VERTEX_SHADER, vertexShader);
        compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER, fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        linkProgram(shaderProgram);

        // Shaders are linked into the program and no longer needed
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // Use the shader program
    void use() {
        glUseProgram(shaderProgram);
    }

    // Destructor
    ~ShaderProgram() {
        glDeleteProgram(shaderProgram);
    }

   private:
    unsigned int shaderProgram;
    unsigned int vertexShader, fragmentShader;

    // Function to read file content
    std::string readFile(const std::string& filePath) {
        std::ifstream fileStream(filePath, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
            return "";
        }
        std::stringstream sstr;
        sstr << fileStream.rdbuf();
        fileStream.close();
        return sstr.str();
    }

    void compileShader(const char* source, GLenum type, unsigned int& shader) {
        shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::string shaderType = (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
            std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
    }

    void linkProgram(unsigned int program) {
        int success;
        char infoLog[512];

        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        }
    }
};
