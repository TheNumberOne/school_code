#define GLM_SWIZZLE

#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : _position(0, 1.8, 9),
                   _up(0, 1, 0),
                   _lineOfSight(glm::vec3(0, 0, -1)),
                   _aspectRatio(16.f / 9) { }

glm::mat4 Camera::getPerspectiveMatrix()
{
    return glm::perspective(_fov, _aspectRatio, _near, _far) * glm::lookAt(_position, _position + _lineOfSight, _up);
}

void Camera::tick(float seconds)
{
    _position += _lineOfSight * _forwardRate * seconds;
    _lineOfSight = glm::vec3(glm::rotate(glm::mat4(1), _rotationRate * seconds, _up) * glm::vec4(_lineOfSight, 0));
}

void Camera::setAspectRatio(float aspectRatio)
{
    _aspectRatio = aspectRatio;
}

void Camera::rotateRight()
{
    _rotationRate = _rotationSpeed;
}

void Camera::rotateLeft()
{
    _rotationRate = -_rotationSpeed;
}

void Camera::stopRotating()
{
    _rotationRate = 0;
}

void Camera::moveForward()
{
    _forwardRate = _movementSpeed;
}

void Camera::stopMoving()
{
    _forwardRate = 0;
}

void Camera::moveBackwards()
{
    _forwardRate = -_movementSpeed;
}
