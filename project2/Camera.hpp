#pragma once


#include <glm/gtc/constants.hpp>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

class Camera {
public:
    Camera();

    glm::mat4 getPerspectiveMatrix();

    glm::mat4 get_view_matrix();

    void tick(float seconds);

    void setAspectRatio(float aspectRatio);

    void rotateRight();

    void rotateLeft();

    void stopRotating();

    void moveForward();

    void moveBackwards();

    void stopMoving();

    void mouse_motion(int dx, int dy);

private:
    glm::vec3 _position;
    glm::vec3 _up;
    glm::vec3 _lineOfSight;
    float _aspectRatio;
    float _sidewaysRate = 0;
    float _forwardRate = 0;
    float _near = .5;
    float _far = 1000;
    float _fov = glm::pi<float>() / 4;
    float _movementSpeed = 1.6;
    float _rotationSpeed = 2 * glm::pi<float>() / 6;
};


