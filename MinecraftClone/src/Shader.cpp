//
//  Shader.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 10/19/21.
//

#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.hpp"

static std::string parseShader(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string source;
    
    if (!file.fail()) {
        std::stringstream ss;
        ss << file.rdbuf();
        source = ss.str();
    } else {
        std::cout << "ERROR::SHADER::FAILED_TO_PARSE_SHADER" << std::endl;
    }
    file.close();
        
    return source;
}

static unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        char message[512];
        glGetShaderInfoLog(id, 512, nullptr, message);
        std::cout << "ERROR::SHADER::FAILED_TO_COMPILE_" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "_SHADER" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        
        return 0;
    }
    
    return id;
}

static unsigned int createShader(const std::string& vertexSource, const std::string& fragmentSource) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        char message[512];
        glGetProgramInfoLog(program, 512, nullptr, message);
        std::cout << "ERROR::SHADER::FAILED_TO_LINK_PROGRAM" << std::endl;
        std::cout << message << std::endl;
        glDeleteProgram(program);
        
        return 0;
    }
    
    glDeleteShader(vs);
    glDeleteShader(fs);
        
    return program;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = parseShader(vertexPath);
    std::string fragmentSource = parseShader(fragmentPath);
    
    id = createShader(vertexSource, fragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::Bind() const {
    glUseProgram(id);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string &name, glm::mat4 matrix) {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1iv(const std::string &name, int count, int* array) {
    glUniform1iv(glGetUniformLocation(id, name.c_str()), count, array);
}


