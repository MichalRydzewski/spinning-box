#include "helpers.h"

#include <iostream>

int main()
{
    initAndSetupWindow();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (windowError(window)) return 1;
    glfwMakeContextCurrent(window);

    if (gladError(window)) return 1;

    manageViewport(window);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
