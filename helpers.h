#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

inline constexpr const char* TITLE = "Just a spinning box";
inline constexpr int WIDTH = 800;
inline constexpr int HEIGHT = 600;

// setup
void initAndSetupWindow();
void checkForWindowError(GLFWwindow* window);
void checkForGladError(GLFWwindow* window);
void manageViewport(GLFWwindow* window);

// callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// buffers
void initVertexBuffer(unsigned* VBO, unsigned long size, float vertices[],
                      GLenum method);
void initElementBuffer(unsigned* EBO, unsigned long size, unsigned indices[],
                       GLenum method);

// input
void processInput(GLFWwindow* window);
