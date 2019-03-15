#define GLM_SWIZZLE

#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_rect.h>
#include <SDL_video.h>

Camera::Camera() : _position(0, 1.8, 4),
                   _up(0, 1, 0),
                   _lineOfSight(glm::vec3(0, 0, -1)),
                   _aspectRatio(16.f / 9) {}

glm::mat4 Camera::getPerspectiveMatrix() {
    return glm::perspective(_fov, _aspectRatio, _near, _far);// * glm::lookAt(_position, _position + _lineOfSight, _up);
}

glm::mat4 Camera::get_view_matrix() {
    return glm::lookAt(_position, _position + _lineOfSight, _up);
}

void Camera::tick(float seconds) {
    _position += (_lineOfSight * _forwardRate + glm::cross(_lineOfSight, _up) * _sidewaysRate) * seconds;
//    _lineOfSight = glm::vec3(glm::rotate(glm::mat4(1), _sidewaysRate * seconds, _up) * glm::vec4(_lineOfSight, 0));
}

void Camera::setAspectRatio(float aspectRatio) {
    _aspectRatio = aspectRatio;
}

void Camera::rotateRight() {
    _sidewaysRate = _movementSpeed;
}

void Camera::rotateLeft() {
    _sidewaysRate = -_movementSpeed;
}

void Camera::stopRotating() {
    _sidewaysRate = 0;
}

void Camera::moveForward() {
    _forwardRate = _movementSpeed;
}

void Camera::stopMoving() {
    _forwardRate = 0;
}

void Camera::moveBackwards() {
    _forwardRate = -_movementSpeed;
}

void Camera::mouse_motion(int dx, int dy) {
    SDL_Rect bounds;
    SDL_GetDisplayBounds(0, &bounds);
    int display_height = bounds.h;
    float angle_per_pixel = _fov / display_height;

    auto transformation = glm::rotate(glm::mat4(1), -dx * angle_per_pixel, _up) *
                          glm::rotate(glm::mat4(1), -dy * angle_per_pixel, glm::cross(_lineOfSight, _up));

    _lineOfSight = transformation *
                   glm::vec4{_lineOfSight, 0};
//    _up = transformation * glm::vec4{_up, 0};
}
