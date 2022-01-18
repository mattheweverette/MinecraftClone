//
//  Window.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 11/8/21.
//

#include "Window.hpp"

#include <iostream>


Window::Window(const std::string& n, int w, int h) : name(n), width(w), height(h) {
    if (!glfwInit()) {
        std::cout << "ERROR::WINDOW::GLFW_INIT_FAILED" << std::endl;
        __builtin_trap();
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "ERROR::WINDOW::WINDOW_CREATION_FAILED" << std::endl;
        __builtin_trap();
    }
    
    glfwSetWindowUserPointer(window, static_cast<void*>(this));

    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
        Window* handler = static_cast<Window*>(glfwGetWindowUserPointer(win));
        handler->width = w;
        handler->height = h;
        glViewport(0, 0, w, h);
    });
}

Window::~Window() {
    delete camera;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::AddCamera(glm::vec3 p, glm::vec3 f, glm::vec3 u) {
    delete camera;
    camera = new Camera(p, f, u, width, height);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xPos, double yPos) {
        Window* handler = static_cast<Window*>(glfwGetWindowUserPointer(win));
        handler->camera->ProcessMouseMovement(xPos, yPos);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* win, double xOffset, double yOffset) {
        Window* handler = static_cast<Window*>(glfwGetWindowUserPointer(win));
        handler->camera->ProcessMouseScroll(yOffset);
    });
};

void Window::OnUpdate(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->Move(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->Move(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->Move(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->Move(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->Move(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->Move(DOWN, deltaTime);
}
