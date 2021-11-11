//
//  Texture.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 11/10/21.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <string>

class Texture {
public:
    Texture(const std::string& fp);
    ~Texture();
    
    void Bind() const;
    void Unbind() const;
private:
    unsigned int id;
    std::string filePath;
};
#endif /* Texture_hpp */
