#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

inline constexpr const char* TITLE = "Just a spinning box";
inline constexpr int WIDTH = 800;
inline constexpr int HEIGHT = 600;

// setup
void initAndSetupWindow();
void checkForWindowError(GLFWwindow *window);
void checkForGladError(GLFWwindow *window);
void manageViewport(GLFWwindow *window);

// callbacks 
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// input
void processInput(GLFWwindow *window);
