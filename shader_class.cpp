#include <glad/glad.h>

#include "shader_class.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace
{
void checkCompileErrors(unsigned shader, const std::string& type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR: (" << type << ")\n"
                      << infoLog << "\n --- --- --- --- --- --- --- --- --- ---"
                      << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR: (" << type << ")\n"
                      << infoLog << "\n --- --- --- --- --- --- --- --- --- ---"
                      << std::endl;
        }
    }
}
}  // namespace

Shader::Shader(const char* vertPath, const char* fragPath)
{
    std::string vertexCode, fragmentCode;
    std::ifstream vertexFile, fragmentFile;
    // ensure those can throw exceptions
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vertexFile.open(vertPath), fragmentFile.open(fragPath);

        // read files' buffer into streams
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        // close files
        vertexFile.close(), fragmentFile.close();

        // convert streams into strings
        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();

    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what()
                  << std::endl;
    }
    const char* cVertexCode = vertexCode.c_str();
    const char* cFragmentCode = fragmentCode.c_str();

    // compile shaders
    unsigned vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &cVertexCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    unsigned fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &cFragmentCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // shaders are linked into our program - they're no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::cleanup() {
    if (ID != 0) {
        glDeleteProgram(ID);
        ID = 0;
    }
}

Shader::~Shader()
{
    cleanup();
}

void Shader::use()
{
    glUseProgram(ID);
}

// uniform setters
void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()),
                static_cast<int>(value));
}
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
