//
//  Noise.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 1/18/22.
//

#ifndef Noise_hpp
#define Noise_hpp

#include <random>
#include <vector>

#include "vendor/glm/vec2.hpp"

class Noise {
public:
    Noise(int gridSize);
    
    float GetValue(float x, float y) const;
    void Reseed();
private:
    int gridSize;
    std::vector<std::vector<glm::vec2>> grid;
};

#endif /* Noise_hpp */
