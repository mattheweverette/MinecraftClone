//
//  Shader.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/19/21.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>

class Shader {
private:
    unsigned int id;
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
};

#endif /* Shader_hpp */
