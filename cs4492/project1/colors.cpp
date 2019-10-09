//
// Created by thenumberone on 2/6/19.
//

#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <glm/vec3.hpp>
#include <random>
#include "colors.h"

auto getRng() {
    std::random_device rd;
    std::default_random_engine re(rd());
    return re;
}

glm::vec3 generateRandomColor() {
    static auto rng = getRng();
    static auto dist = std::uniform_real_distribution<float>();
    return {dist(rng), dist(rng), dist(rng)};
}
