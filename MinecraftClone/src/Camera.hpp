//
//  Camera.hpp
//  MinecraftClone
//
//  Created by Matthew Everette on 11/5/21.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "glm/glm.hpp"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:
    Camera(glm::vec3 p, glm::vec3 f, glm::vec3 u, int w, int h);
    
    void SetPosition(glm::vec3 p);
    void Move(CameraMovement m, float deltaTime);
    
    void ProcessMouseMovement(float xPos, float yPos);
    void ProcessMouseScroll(float yOffset);
    
    inline const glm::mat4& GetViewProj() const { return viewProj; }
private:
    glm::vec3 position, front, up, right;
    float yaw, pitch;
    float fov = 45.0f;
    float width, height;
    glm::mat4 viewProj;
    float speed = 5.0f, sensitivity = 0.1f;
    
    float prevXPos, prevYPos;
    
    void UpdateVectors();
    void UpdateViewProj();
};

#endif /* Camera_hpp */
