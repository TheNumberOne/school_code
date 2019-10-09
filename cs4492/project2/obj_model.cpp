#include <utility>

#include <GL/glew.h>
#include <string>
#include <sstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include "obj_model.h"
#include "glm_util.h"

std::istream &operator>>(std::istream &in, obj_model &self) {
    while (true) {
        std::string line;
        if (!std::getline(in, line)) return in;

        if (line[0] == '#')
            continue;

        std::istringstream line_ss{line};

        std::string command;
        line_ss >> command;

        if (command == "o") {
            // ignore
        } else if (command == "mtllib") {
            std::string materialFile;
            line_ss >> materialFile;
            self.load_material_file(materialFile);
        } else if (command == "v") {
            glm::vec3 v;
            line_ss >> v;
            self.add_vertex(v);
        } else if (command == "vn") {
            glm::vec3 normal;
            line_ss >> normal;
            self.add_normal(normal);
        } else if (command == "vt") {
            glm::vec2 uv;
            line_ss >> uv;
            self.add_uv(uv);
        } else if (command == "usemtl") {
            std::string material;
            line_ss >> material;
            self.switch_material(material);
        } else if (command == "s") {
            // ignore
        } else if (command == "f") {
            std::vector<int> vertexIndices;
            std::vector<int> uvIndices;
            std::vector<int> normalIndices;

            while (true) {
                std::string vertex;
                line_ss >> vertex;
                if (!line_ss) break;

                std::stringstream vertex_ss{vertex};
                if (vertex_ss.peek() != '/' && vertex_ss) {
                    int i;
                    vertex_ss >> i;
                    vertexIndices.push_back(i);
                }
                vertex_ss.get();
                if (vertex_ss.peek() != '/' && vertex_ss) {
                    int i;
                    vertex_ss >> i;
                    uvIndices.push_back(i);
                }
                vertex_ss.get();
                if (vertex_ss) {
                    int i;
                    vertex_ss >> i;
                    normalIndices.push_back(i);
                }
            }

            self.add_face(vertexIndices, uvIndices, normalIndices);
        }
    }
}

void obj_model::load_material_file(std::string filename) {
    std::ifstream in{filename};
    in >> _materials;
    _materials.done();
}

void obj_model::add_vertex(glm::vec3 vertex) {
    _vertices.push_back(vertex);
}

void obj_model::add_normal(glm::vec3 normal) {
    _normals.push_back(normal);
}

void obj_model::switch_material(std::string material_name) {
    _current_material = std::move(material_name);
}

void obj_model::add_face(std::vector<int> vertexIndices, std::vector<int> uvIndices, std::vector<int> normalIndices) {

    if (vertexIndices.size() != 3) throw std::runtime_error("can only read in triangle _faces");

    while (uvIndices.size() < 3) {
        uvIndices.push_back(-1);
    }
    while (normalIndices.size() < 3) {
        normalIndices.push_back(-1);
    }

    triangle t{};

    for (int i = 0; i < 3; i++) {
        glm::vec3 v = _vertices[vertexIndices[i]];
        std::copy(glm::value_ptr(v), glm::value_ptr(v) + 3, t.vertices[i].vertex);

        glm::vec2 uv;
        if (uvIndices[i] == -1) {
            uv = {0, 0};
        } else {
            uv = _uvs[uvIndices[i]];
        }
        std::copy(glm::value_ptr(uv), glm::value_ptr(v) + 2, t.vertices[i].uv);

        glm::vec3 normal;
        if (normalIndices[i] == -1) {
            glm::vec3 before = _vertices[vertexIndices[i == 0 ? 2 : i - 1]];
            glm::vec3 after = _vertices[vertexIndices[i == 2 ? 0 : i + 1]];
            normal = glm::normalize(glm::cross(v - before, after - v));
        } else {
            normal = _normals[normalIndices[i]];
        }
        std::copy(glm::value_ptr(normal), glm::value_ptr(normal) + 3, t.vertices[i].normal);
    }
    _faces[_current_material].push_back(t);
}

void obj_model::draw() const {
    for (const auto &[material_name, faces] : _faces) {
        _materials[material_name].load();
        for (auto &face : faces) {
            glBegin(GL_POLYGON);
            for (const auto &vertex : face.vertices) {
                glNormal3fv(vertex.normal);
                glTexCoord2fv(vertex.uv);
                glVertex3fv(vertex.vertex);
            }
            glEnd();
        }
    }
}

void obj_model::add_uv(glm::vec2 uv) {
    _uvs.push_back(uv);
}
