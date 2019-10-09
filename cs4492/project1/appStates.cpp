//
// Created by thenumberone on 2/6/19.
//

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include "appStates.h"
#include "globalState.h"
#include "colors.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>


constexpr double PI = std::acos(-1);

template<size_t width>
std::array<glm::vec3, width> oneColor1(glm::vec3 c) {
    std::array<glm::vec3, width> ret{};
    for (int i = 0; i < width; i++) {
        ret[i] = c;
    }
    return ret;
}


InitialAppState::InitialAppState()
        : m_bigSquareColors(oneColor1<36>({1, 0, 0})),
          m_littleSquareColors(oneColor1<16>({0, 0, 1})) {}


glm::mat4 InitialAppState::getCamera() {
    return glm::frustum(-30.f * width / height, 30.f * width / height, -30.f, 30.f, 20.f, 100.f) *
           glm::lookAt(glm::vec3{0, 0, 30}, {0, 0, 1}, {0, 1, 0});
}

std::unique_ptr<AppState> InitialAppState::nextState() {
    return std::make_unique<SecondAppState>();
}

glm::mat4 SecondAppState::getCamera() {
    return glm::frustum(-30.f * width / height, 30.f * width / height, -30.f, 30.f, 20.f, 100.f) *
           glm::lookAt(glm::vec3{20, 0, 30}, {0, 0, 1}, {0, 1, 0});
}

std::unique_ptr<AppState> SecondAppState::nextState() {
    return std::make_unique<ThirdAppState>();
}

ThirdAppState::ThirdAppState():
    m_bigSquareColors(generateColors1<36>()),
    m_littleSquareColors(generateColors1<16>()){}

std::unique_ptr<AppState> ThirdAppState::nextState() {
    return std::make_unique<FourthAppState>();
}

glm::mat4 FourthAppState::getCamera() {

    glm::vec3 redCenter{-15, 15, 2};
    glm::vec3 blueCenter{10, -10, 0};
    glm::vec3 center = (redCenter + blueCenter) / 2.f;
    float distance = 50;
    glm::vec3 cameraPosition = glm::normalize(glm::cross(blueCenter - center, {0, 1, 0})) * distance + center;

    float theta = std::atan2(height, width);
    float width = glm::length(redCenter - center);

    float near = distance / 2;
    float far = distance * 2;
    float right = width * std::cos(theta);
    float left = -right;
    float top = width * std::sin(theta);
    float bottom = -top;

    // First look at the center of the two centers with the red center oriented upwards.
    glm::mat4 camera = glm::lookAt(cameraPosition, center, redCenter - center);

    // Then rotate the image such that the centers align along the diagonal from upper left
    // to lower right.
    camera = glm::rotate(static_cast<float>(PI) / 2 - theta, glm::vec3{0, 0, 1}) * camera;

    // Then convert that to a perspective view.
    camera = glm::frustum(left, right, bottom, top, near, far) * camera;

    return camera;
}

std::unique_ptr<AppState> FourthAppState::nextState() {
    return std::make_unique<InitialAppState>();
}
