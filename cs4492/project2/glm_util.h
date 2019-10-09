#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

std::istream &operator>>(std::istream &in, glm::vec3 &rhs);

std::istream &operator>>(std::istream &in, glm::vec2 &rhs);