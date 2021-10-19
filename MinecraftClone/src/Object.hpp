//
//  Object.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/19/21.
//

#ifndef Object_hpp
#define Object_hpp

#include "VertexBufferLayout.hpp"

class Object {
private:
    unsigned int vaID, vbID, ebID;
public:
    Object(const void* vertices, unsigned int vSize, const VertexBufferLayout& layout, const unsigned int* indices, unsigned int iSize);
    ~Object();
    
    void Bind() const;
    void Unbind() const;
};

#endif /* Object_hpp */
