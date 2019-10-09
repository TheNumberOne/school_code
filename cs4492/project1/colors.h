#pragma once

glm::vec3 generateRandomColor();


template<size_t width>
std::array<glm::vec3, width> generateColors1() {
    std::array<glm::vec3, width> ret{};
    for (int i = 0; i < width; i++) {
        ret[i] = generateRandomColor();
    }
    return ret;
}

template<size_t width, size_t height>
std::array<std::array<glm::vec3, width>, height> generateColors() {
    std::array<std::array<glm::vec3, width>, height> ret{};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ret[i][j] = generateRandomColor();
        }
    }
    return ret;
}

template<size_t width, size_t height>
std::array<std::array<glm::vec3, width>, height> oneColor(glm::vec3 c) {
    std::array<std::array<glm::vec3, width>, height> ret{};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ret[i][j] = c;
        }
    }
    return ret;
}