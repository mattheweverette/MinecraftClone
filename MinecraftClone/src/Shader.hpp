//
//  Shader.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/19/21.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>

#include "glm/glm.hpp"

class Shader {
private:
    unsigned int id;
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
    
    void SetUniform1i(const std::string& name, int value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, glm::mat4 matrix);
};

#endif /* Shader_hpp */
