#pragma once

#include <vector>

void display_mesh(const std::vector<glm::vec3> &points, const std::vector<std::vector<size_t>> &shapes,
                  const std::vector<glm::vec3> &normals, const std::vector<size_t> &normal_indices);

void display_mesh(const std::vector<glm::vec3> &points, const std::vector<std::vector<size_t>> &shapes,
                  const std::vector<glm::vec3> &normals, const std::vector<size_t> &normal_indices,
                  const std::vector<material> &materials, const std::vector<size_t> &material_indices);