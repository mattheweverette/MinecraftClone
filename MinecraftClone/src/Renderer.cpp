//
//  Renderer.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/19/21.
//

#include "Renderer.hpp"

#include <iostream>

Renderer::Renderer(int mcc) : maxCubeCount(mcc), cubeCount(0) {
    buffer.reserve(maxCubeCount * 24 * sizeof(Vertex));
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, maxCubeCount * 24 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, position));
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, texCoord));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, texIndex));
    
    unsigned int indices[maxCubeCount * 36];
    for (int i = 0; i < maxCubeCount * 6; i++) {
        indices[6 * i] = 4 * i;
        indices[6 * i + 1] = 4 * i + 1;
        indices[6 * i + 2] = 4 * i + 2;
        indices[6 * i + 3] = 4 * i + 2;
        indices[6 * i + 4] = 4 * i + 3;
        indices[6 * i + 5] = 4 * i;
    }
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Renderer::AddCube(float position[3]) {
    if (cubeCount == maxCubeCount)
        Flush();
        
    buffer.push_back({ { position[0] - 0.5f, position[1] - 0.5f, position[2] + 0.5f }, { 0.0f, 0.0f }, 0.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] - 0.5f, position[2] + 0.5f }, { 1.0f, 0.0f }, 0.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] + 0.5f, position[2] + 0.5f }, { 1.0f, 1.0f }, 0.0f });
    buffer.push_back({ { position[0] - 0.5f, position[1] + 0.5f, position[2] + 0.5f }, { 0.0f, 1.0f }, 0.0f });
    
    buffer.push_back({ { position[0] + 0.5f, position[1] - 0.5f, position[2] + 0.5f }, { 0.0f, 0.0f }, 0.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] - 0.5f, position[2] - 0.5f }, { 1.0f, 0.0f }, 0.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] + 0.5f, position[2] - 0.5f }, { 1.0f, 1.0f }, 0.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] + 0.5f, position[2] + 0.5f }, { 0.0f, 1.0f }, 0.0f });
    
    buffer.push_back({ { position[0] + 0.5f, position[1] - 0.5f, position[2] - 0.5f }, { 0.0f, 0.0f }, 0.0f });
    buffer.push_back({ { position[0] - 0.5f, position[1] - 0.5f, position[2] - 0.5f }, { 1.0f, 0.0f }, 0.0f });
    buffer.push_back({ { position[0] - 0.5f, position[1] + 0.5f, position[2] - 0.5f }, { 1.0f, 1.0f }, 0.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] + 0.5f, position[2] - 0.5f }, { 0.0f, 1.0f }, 0.0f });
    
    buffer.push_back({ { position[0] - 0.5f, position[1] - 0.5f, position[2] - 0.5f }, { 0.0f, 0.0f }, 0.0f });
    buffer.push_back({ { position[0] - 0.5f, position[1] - 0.5f, position[2] + 0.5f }, { 1.0f, 0.0f }, 0.0f });
    buffer.push_back({ { position[0] - 0.5f, position[1] + 0.5f, position[2] + 0.5f }, { 1.0f, 1.0f }, 0.0f });
    buffer.push_back({ { position[0] - 0.5f, position[1] + 0.5f, position[2] - 0.5f }, { 0.0f, 1.0f }, 0.0f });
    
    buffer.push_back({ { position[0] - 0.5f, position[1] + 0.5f, position[2] + 0.5f }, { 0.0f, 0.0f }, 1.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] + 0.5f, position[2] + 0.5f }, { 1.0f, 0.0f }, 1.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] + 0.5f, position[2] - 0.5f }, { 1.0f, 1.0f }, 1.0f });
    buffer.push_back({ { position[0] - 0.5f, position[1] + 0.5f, position[2] - 0.5f }, { 0.0f, 1.0f }, 1.0f });
    
    buffer.push_back({ { position[0] - 0.5f, position[1] - 0.5f, position[2] - 0.5f }, { 0.0f, 0.0f }, 2.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] - 0.5f, position[2] - 0.5f }, { 1.0f, 0.0f }, 2.0f });
    buffer.push_back({ { position[0] + 0.5f, position[1] - 0.5f, position[2] + 0.5f }, { 1.0f, 1.0f }, 2.0f });
    buffer.push_back({ { position[0] - 0.5f, position[1] - 0.5f, position[2] + 0.5f }, { 0.0f, 1.0f }, 2.0f });
    
    cubeCount++;
}

void Renderer::BeginBatch() {
    
}

void Renderer::Flush() {
    glBindVertexArray(vao);
    glBufferSubData(GL_ARRAY_BUFFER, 0, cubeCount * 36 * sizeof(Vertex), buffer.data());
    glDrawElements(GL_TRIANGLES, cubeCount * 36, GL_UNSIGNED_INT, nullptr);
    cubeCount = 0;
}

void Renderer::EndBatch() {
    Flush();
}
