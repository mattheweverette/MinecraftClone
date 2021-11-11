//
//  Texture.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 11/10/21.
//

#include "Texture.hpp"

#include <GL/glew.h>
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& fp) : filePath(fp) {
    int width, height, BPP;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &BPP, 0);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
