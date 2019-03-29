#include <utility>

#include <utility>

#include <sstream>
#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include "materials.h"
#include "glm_util.h"
#include "stb_image.h"

std::istream &operator>>(std::istream &in, materials &self) {
    while (true) {
        std::string line;
        if (!std::getline(in, line)) return in;
        if (line.empty() || line[0] == '#') continue;

        std::stringstream line_ss{line};
        std::string command;
        line_ss >> command;

        if (command == "newmtl") {
            std::string name;
            line_ss >> name;
            self.new_material(name);
        } else if (command == "Ns") {
            float shininess;
            line_ss >> shininess;
            self.shininess(shininess);
        } else if (command == "Ka") {
            glm::vec3 ambient;
            line_ss >> ambient;
            self.ambience(ambient);
        } else if (command == "Kd") {
            glm::vec3 diffuse;
            line_ss >> diffuse;
            self.diffuse(diffuse);
        } else if (command == "Ks") {
            glm::vec3 speculance;
            line_ss >> speculance;
            self.speculance(speculance);
        } else if (command == "Ke") {
            glm::vec3 emmittance;
            line_ss >> emmittance;
            self.emittance(emmittance);
        } else if (command == "Ni") {
            // ignore
        } else if (command == "d") {
            // ignore
        } else if (command == "illum") {
            // ignore
        } else if (command == "map_Kd") {
            std::string file_name;
            line_ss >> file_name;
            self.map_diffuse(file_name);
        }
    }
}

void materials::new_material(std::string name) {
    done();
    _started_material = true;
    _current_material_name = std::move(name);
}

void materials::shininess(float shininess) {
    _current_material.setShininess(shininess);
}

void materials::ambience(glm::vec3 ambience) {
    _current_material.setColor({ambience, 1});
}

void materials::diffuse(glm::vec3 diffuse) {
    _current_material.setDiffuse({diffuse, 1});
}

void materials::emittance(glm::vec3 emittance) {
    _current_material.setEmissions({emittance, 1});
}

void materials::speculance(glm::vec3 speculance) {
    _current_material.setSpecular({speculance, 1});
}

const material &materials::operator[](std::string name) const {
    return _materials.at(name);
}

void materials::done() {
    if (_started_material) {
        _materials[_current_material_name] = std::move(_current_material);
        _current_material.clearTexture();
    }
    _started_material = false;
}

void materials::map_diffuse(std::string file_name) {
    _current_material.setTexture(gl::texture{0, file_name});
}
