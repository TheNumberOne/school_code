#pragma once


#include <iostream>
#include <map>
#include "material.hpp"

class materials {
public:
    friend std::istream &operator>>(std::istream &in, materials &self);

    void done();

    const material &operator[](std::string name) const;

private:
    void new_material(std::string name);

    void shininess(float shininess);

    void ambience(glm::vec3 ambience);

    void diffuse(glm::vec3 diffuse);

    void speculance(glm::vec3 speculance);

    void emittance(glm::vec3 emittance);

    void map_diffuse(std::string file_name);

    std::map<std::string, material> _materials;
    material _current_material;
    bool _started_material = false;
    std::string _current_material_name;
};


