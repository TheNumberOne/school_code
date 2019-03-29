#pragma once

#include <iostream>
#include "materials.h"
#include "gl_util.h"

struct vertex {
    float vertex[3];
    float uv[2];
    float normal[3];
};

struct triangle {
    vertex vertices[3];
};

class obj_model {
public:
    friend std::istream &operator>>(std::istream &in, obj_model &self);

    void draw() const;


private:
    void load_material_file(std::string filename);

    void add_vertex(glm::vec3 vertex);

    void add_normal(glm::vec3 normal);

    void add_uv(glm::vec2 uv);

    void switch_material(std::string material_name);

    void add_face(std::vector<int> vertexIndices, std::vector<int> uvIndices, std::vector<int> normalIndices);

    materials _materials;
    std::map<std::string, std::vector<triangle>> _faces;
    std::vector<glm::vec3> _vertices{{}};
    std::vector<glm::vec3> _normals{{}};
    std::vector<glm::vec2> _uvs{{}};
    std::string _current_material;
};