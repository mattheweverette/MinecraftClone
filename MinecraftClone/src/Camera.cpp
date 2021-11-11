//
//  Camera.cpp
//  MinecraftClone
//
//  Created by Matthew Everette on 11/5/21.
//

#include "Camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(glm::vec3 p, glm::vec3 f, glm::vec3 u, int w, int h) : position(p), front(f), up(u), right(glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)))), width(w), height(h), viewProj(glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f) * glm::lookAt(position, glm::normalize(position + front), up)), prevXPos(width / 2), prevYPos(height / 2) {
    yaw = -90.0f; // glm::atan(front.z / front.x);
    pitch = glm::atan(front.y / glm::sqrt(front.x * front.x + front.z * front.z));
}

void Camera::SetPosition(glm::vec3 p) {
    position = p;
    UpdateViewProj();
}

void Camera::Move(CameraMovement m, float deltaTime) {
    switch (m) {
        case FORWARD :
            
            position += glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), right)) * speed * deltaTime;
            break;
        case BACKWARD :
            position -= glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), right)) * speed * deltaTime;
            break;
        case LEFT :
            position -= right * speed * deltaTime;
            break;
        case RIGHT :
            position += right * speed * deltaTime;
            break;
        case UP :
            position += glm::vec3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
            break;
        case DOWN :
            position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
            break;
    }
        
    UpdateViewProj();
}

void Camera::ProcessMouseMovement(float xPos, float yPos) {
    yaw += (xPos - prevXPos) * sensitivity;
    pitch += (prevYPos - yPos) * sensitivity;
    
    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;
    
    prevXPos = xPos;
    prevYPos = yPos;
        
    UpdateVectors();
    UpdateViewProj();
}

void Camera::ProcessMouseScroll(float yOffset) {
    fov -= yOffset;
    if (fov < 1.0f)
        fov = 1.0f;
    else if (fov > 45.0f)
        fov = 45.0f;
        
    UpdateViewProj();
}

void Camera::UpdateVectors() {
    front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front = glm::normalize(front);
    
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::UpdateViewProj() {
    viewProj = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f) * glm::lookAt(position, position + front, up);
}

