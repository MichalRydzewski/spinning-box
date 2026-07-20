#include "helpers.h"
#include "shader_class.h"

#include <iostream>

int main()
{
    initAndSetupWindow();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    checkForWindowError(window);
    glfwMakeContextCurrent(window);
    checkForGladError(window);
    manageViewport(window);

    float vertices[] = {
        0.5f,  -0.5f, 0.0f,  //
        0.5f,  0.5f,  0.0f,  //
        -0.5f, 0.5f,  0.0f,  //
        -0.5f, -0.5f, 0.0f,  //
    };

    unsigned indices[] = {
        0, 1, 3,  //
        3, 1, 2   //
    };

    unsigned VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // paths are relative to build directory
    Shader myProgram = Shader("./../shaders/standard_vert.glsl",
                              "./../shaders/standard_frag.glsl");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        myProgram.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    myProgram.cleanup();
    glfwTerminate();
    return 0;
}
