#pragma once

#include <vector>
#include "material.hpp"

void display_mesh(const std::vector<glm::vec3> &points, const std::vector<std::vector<unsigned long>> &shapes,
                  const std::vector<glm::vec3> &normals, const std::vector<unsigned long> &normal_indices);

void display_mesh(const std::vector<glm::vec3> &points, const std::vector<std::vector<unsigned long>> &shapes,
                  const std::vector<glm::vec3> &normals, const std::vector<unsigned long> &normal_indices,
                  const std::vector<material> &materials, const std::vector<unsigned long> &material_indices);