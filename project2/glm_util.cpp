
#include "glm_util.h"
#include <iostream>

std::istream &operator>>(std::istream &in, glm::vec3 &rhs) {
    in >> rhs.x;
    in >> rhs.y;
    in >> rhs.z;
    return in;
}

std::istream &operator>>(std::istream &in, glm::vec2 &rhs) {
    in >> rhs.x;
    in >> rhs.y;
    return in;
}
