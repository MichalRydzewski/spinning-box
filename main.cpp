#include "helpers.h"
#include "shader_class.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  //
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  //
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f,  //
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  //
    };

    unsigned indices[] = {
        0, 1, 3,  //
        3, 1, 2   //
    };

    unsigned VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    initVertexBuffer(&VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
    initElementBuffer(&EBO, sizeof(indices), indices, GL_STATIC_DRAW);

    // paths are relative to build directory
    Shader myProgram = Shader("./../shaders/standard_vert.glsl",
                              "./../shaders/standard_frag.glsl");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::mat4 transMat;
    myProgram.use();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        transMat =
            glm::rotate(glm::mat4(1.0f),
                        glm::radians(static_cast<float>(glfwGetTime() * 30)),
                        glm::vec3(0.0f, 0.0f, 1.0f));
        myProgram.setMat4("rotation", transMat);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    myProgram.cleanup();
    glfwTerminate();
    return 0;
}
