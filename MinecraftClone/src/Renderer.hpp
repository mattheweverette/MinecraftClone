//
//  Renderer.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/19/21.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

struct Vertex {
    float position[3];
    float texCoord[2];
    float texIndex;
};

class Renderer {
public:
    Renderer(int mcc = 100);
    ~Renderer();
    
    void AddCube(float position[3]);
    void BeginBatch();
    void EndBatch();
    void Flush();
private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    int maxCubeCount;
    int cubeCount;
    std::vector<Vertex> buffer;
};

#endif /* Renderer_hpp */
