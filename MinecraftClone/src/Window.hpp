//
//  Window.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 11/8/21.
//

#ifndef Window_hpp
#define Window_hpp

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.hpp"

class Window {
public:
    Window(const std::string& n, int w, int h);
    ~Window();
    
    void AddCamera(glm::vec3 p, glm::vec3 f, glm::vec3 u);
    
    void OnUpdate(float deltaTime);
    
    inline bool ShouldClose() const { return glfwWindowShouldClose(window); }
    inline void SwapBuffers() const { glfwSwapBuffers(window); }
    inline float GetTime() const { return glfwGetTime(); }
    
    inline const Camera* GetCamera() const { return camera; }
private:
    std::string name;
    int width, height;
    GLFWwindow* window;
    Camera* camera = nullptr;
};

#endif /* Window_hpp */
