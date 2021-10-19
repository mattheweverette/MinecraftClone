//
//  main.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/15/21.
//

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Object.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "MinecraftClone", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK)
        return -1;
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    float positions[] = {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
        1, 4, 7,
        7, 2, 1,
        4, 5, 6,
        6, 7, 4,
        5, 0, 3,
        3, 6, 5,
        3, 2, 7,
        7, 6, 3,
        5, 4, 1,
        1, 0, 5
    };
    
    VertexBufferLayout layout;
    layout.Push<float>(2);
    
    Object cube(positions, sizeof(positions), layout, indices, 36);
    
    Shader shader("res/shaders/shader.vs", "res/shaders/shader.fs");
    
    cube.Bind();
    shader.Bind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
