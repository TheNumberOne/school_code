
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "material.hpp"

material::material(
    const glm::vec4 &color,
    const glm::vec4 &diffuse,
    const glm::vec4 &specular,
    float shininess,
    const glm::vec4 &emissions
) : color(color), diffuse(diffuse), specular(specular), shininess(shininess), emissions(emissions) {}

const glm::vec4 &material::getColor() const {
    return color;
}

void material::setColor(const glm::vec4 &color) {
    material::color = color;
}

const glm::vec4 &material::getDiffuse() const {
    return diffuse;
}

void material::setDiffuse(const glm::vec4 &diffuse) {
    material::diffuse = diffuse;
}

const glm::vec4 &material::getSpecular() const {
    return specular;
}

void material::setSpecular(const glm::vec4 &specular) {
    material::specular = specular;
}

float material::getShininess() const {
    return shininess;
}

void material::setShininess(float shininess) {
    material::shininess = shininess;
}

const glm::vec4 &material::getEmissions() const {
    return emissions;
}

void material::setEmissions(const glm::vec4 &emissions) {
    material::emissions = emissions;
}

void material::load() const {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(color));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emissions));
}

