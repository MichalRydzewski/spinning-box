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
        // Position           // Index
        -0.5f, -0.5f, -0.5f,  // 0: Inward-Bottom-Left
        0.5f,  -0.5f, -0.5f,  // 1: Inward-Bottom-Right
        0.5f,  0.5f,  -0.5f,  // 2: Inward-Up-Right
        -0.5f, 0.5f,  -0.5f,  // 3: Inward-Up-Left
        -0.5f, -0.5f, 0.5f,   // 4: Outward-Bottom-Left
        0.5f,  -0.5f, 0.5f,   // 5: Outward-Bottom-Right
        0.5f,  0.5f,  0.5f,   // 6: Outward-Up-Right
        -0.5f, 0.5f,  0.5f    // 7: Outward-Up-Left
    };

    uint8_t indices[] = {
        // Inside side (Z = -0.5)
        0, 1, 2,  //
        2, 3, 0,  //
        // Outside side (Z = 0.5)
        4, 5, 6,  //
        6, 7, 4,  //
        // Left side (X = -0.5)
        7, 3, 0,  //
        0, 4, 7,  //
        // Right side (X = 0.5)
        1, 2, 6,  //
        6, 5, 1,  //
        // Bottom side (Y = -0.5)
        0, 1, 5,  //
        5, 4, 0,  //
        // Up side (Y = 0.5)
        3, 2, 6,  //
        6, 7, 3   //
    };

    unsigned VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    initVertexBuffer(&VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
    initElementBuffer(&EBO, sizeof(indices), indices, GL_STATIC_DRAW);

    // paths are relative to build directory
    Shader myProgram = Shader("./../shaders/standard_vert.glsl",
                              "./../shaders/standard_frag.glsl");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    int modelLoc = glGetUniformLocation(myProgram.ID, "model");
    int viewLoc = glGetUniformLocation(myProgram.ID, "view");
    int projectionLoc = glGetUniformLocation(myProgram.ID, "projection");

    myProgram.use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                        glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    
    glBindVertexArray(VAO);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        model =
            glm::rotate(model, glm::radians(static_cast<float>(glfwGetTime() * 30)),
                        glm::vec3(0.5f, 0.5f, 0.2f));        

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);

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
