//
//  VertexBufferLayout.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/19/21.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <vector>

#include "Renderer.hpp"

struct VertexBufferElement {
    unsigned int count;
    unsigned int type;
    unsigned int normalized;
    
    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT :
                return sizeof(float);
        }
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride = 0;
public:
    template<typename T>
    void Push(unsigned int count) = delete;
    
    template<>
    void Push<float>(unsigned int count) {
        elements.push_back({count, GL_FLOAT, GL_FALSE});
        stride += count * sizeof(float);
    }
    
    inline const std::vector<VertexBufferElement>& GetElements() const { return elements; }
    inline unsigned int GetStride() const { return stride; }
};

#endif /* VertexBufferLayout_hpp */
