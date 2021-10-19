//
//  Object.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/19/21.
//

#include "Object.hpp"

Object::Object(const void* vertices, unsigned int vSize, const VertexBufferLayout& layout, const unsigned int* indices, unsigned int iCount) {
    glGenVertexArrays(1, &vaID);
    glBindVertexArray(vaID);
    
    glGenBuffers(1, &vbID);
    glBindBuffer(GL_ARRAY_BUFFER, vbID);
    
    glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_STATIC_DRAW);
    
    const auto& elements = layout.GetElements();
    size_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.GetStride(), (const void*) offset);
        offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
    }
    
    glGenBuffers(1, &ebID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebID);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

Object::~Object() {
    glDeleteVertexArrays(1, &vaID);
    glDeleteBuffers(1, &vbID);
    glDeleteBuffers(1, &ebID);
}

void Object::Bind() const {
    glBindVertexArray(vaID);
}

void Object::Unbind() const {
    glBindVertexArray(0);
}
