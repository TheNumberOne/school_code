#pragma once


#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

class Camera
{
    Camera() : _position(0, 2, 0),
               _up(0, 1, 0),
               _lineOfSight(glm::normalize(glm::vec3(0, 1, -1))),
               _aspectRatio(16.f / 9) { }
    
    glm::mat4 getPerpsectiveMatrix()
    {
        return glm::perspective(_fov, _aspectRatio, _near, _far) * glm::lookAt(_position, _lineOfSight, _up);
    }
    
    void tick(float seconds)
    {
        _position += _lineOfSight * seconds;
        _lineOfSight = glm::rotate(glm::mat4(1), _rotationRate * seconds, _up) * glm::vec4(_lineOfSight, 0);
    }
    
    void setAspectRatio(float aspectRatio)
    {
        _aspectRatio = aspectRatio;
    }
    
    void rotateRight()
    {
        _rotationRate = _rotationSpeed;
    }
    
    void rotateLeft()
    {
        _rotationRate = -_rotationSpeed;
    }
    
    void stopRotating()
    {
        _rotationRate = 0;
    }
    
    void moveForward()
    {
        _forwardRate = _movementSpeed;
    }
    
    void stopMovingForward()
    {
        _forwardRate = 0;
    }

private:
    glm::vec3 _position;
    glm::vec3 _up;
    glm::vec3 _lineOfSight;
    float _aspectRatio;
    float _rotationRate = 0;
    float _forwardRate = 0;
    float _near = .5;
    float _far = 1000;
    float _fov = glm::pi<float>() / 2;
    float _movementSpeed = 1.6;
    float _rotationSpeed = 2 * glm::pi<float>() / 3;
};


