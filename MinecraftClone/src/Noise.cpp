//
//  Noise.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 1/18/22.
//

#include "Noise.hpp"

#include <cstdlib>
#include <cmath>

#include "vendor/glm/glm.hpp"

glm::vec2 randomVector() {
    float theta = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / M_PI);
    float x = std::cos(theta);
    float y = std::sin(theta);
    return glm::vec2(x, y);
}

float lerp(float v0, float v1, float t) {
    return v0 + t * (v1 - v0);
}

Noise::Noise(int gs) : gridSize(gs), grid(gridSize) {
    srand(static_cast<unsigned int>(time(NULL)));
    for (auto& row : grid)
        for (int i = 0; i < gridSize; i++)
            row.push_back(randomVector());
}

float Noise::GetValue(float x, float y) const {
    float tl = glm::dot(grid[std::floor(x)][std::floor(y)], glm::vec2(x - std::floor(x), y - std::floor(y)));
    float bl = glm::dot(grid[std::floor(x)][std::floor(y) + 1], glm::vec2(x - std::floor(x), y - std::floor(y) + 1));
    float br = glm::dot(grid[std::floor(x) + 1][std::floor(y) + 1], glm::vec2(x - std::floor(x) + 1, y - std::floor(y)+ 1));
    float tr = glm::dot(grid[std::floor(x) + 1][std::floor(y)], glm::vec2(x - std::floor(x) + 1, y - std::floor(y)));
    
    float left = lerp(tl, bl, x - std::floor(x));
    float right = lerp(tr, br, x - std::floor(x));
    
    return lerp(left, right, y - std::floor(y));
}

void Noise::Reseed() {
    grid = std::vector<std::vector<glm::vec2>>(gridSize);
    for (auto& row : grid)
        row.push_back(randomVector());
}

