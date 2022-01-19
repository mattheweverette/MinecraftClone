//
//  main.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/15/21.
//

#include <iostream>

#include <GL/glew.h>

#include "Shader.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Noise.hpp"

#include "stb_image/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main() {
    Window window("Minecraft Clone", 960, 540);
    window.AddCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    if (glewInit() != GLEW_OK)
        return -1;
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    glEnable(GL_DEPTH_TEST);
    
    const int cubeCount = 10 * 10;
    float positions[cubeCount][3];
    
    Noise noise(4);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            positions[10 * i + j][0] = (float) i;
            positions[10 * i + j][1] = std::floor(noise.GetValue((float)3 * i / 10, (float)3 * j / 10));
            positions[10 * i + j][2] = (float) -j;
        }
    }
    
    Texture textures[3] {
        { "res/textures/grass_side.png" },
        { "res/textures/grass_top.png" },
        { "res/textures/dirt.png" }
    };
    for (int i = 0; i < 3; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i].Bind();
    }
        
    Shader shader("res/shaders/shader.vs", "res/shaders/shader.fs");

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", window.GetCamera()->GetViewProj());
    int samplers[3] = { 0, 1, 2 };
    shader.SetUniform1iv("u_Textures", 3, samplers);
    
    Renderer renderer;
    
    glClearColor(0.47f, 0.72f, 1.0f, 1.0f);
    
//    glEnable(GL_CULL_FACE);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glCullFace(GL_FRONT);

    float lastTime, currentTime = window.GetTime(), deltaTime;
    while (!window.ShouldClose())
    {
        lastTime = currentTime;
        currentTime = window.GetTime();
        deltaTime = currentTime - lastTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", window.GetCamera()->GetViewProj());

        renderer.BeginBatch();
        for (int i = 0; i < cubeCount; i++)
            renderer.AddCube(positions[i]);
        renderer.EndBatch();
                
        window.SwapBuffers();

        glfwPollEvents();
        window.OnUpdate(deltaTime);
    }
    
    return 0;
}
