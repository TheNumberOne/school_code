#pragma once

#include <optional>
#include "gl_util.h"
#include "gl_util_texture.h"
#include <glm/vec4.hpp>

class material {
public:
    material();

    material(
        const glm::vec4 &color,
        const glm::vec4 &diffuse,
        const glm::vec4 &specular,
        float shininess,
        const glm::vec4 &emissions
    );

    void load() const;

    const glm::vec4 &getColor() const;

    void setColor(const glm::vec4 &color);

    const glm::vec4 &getDiffuse() const;

    void setDiffuse(const glm::vec4 &diffuse);

    const glm::vec4 &getSpecular() const;

    void setSpecular(const glm::vec4 &specular);

    float getShininess() const;

    void setShininess(float shininess);

    const glm::vec4 &getEmissions() const;

    void setEmissions(const glm::vec4 &emissions);

    const std::optional<gl::texture> &getTexture() const;

    void setTexture(gl::texture &&texture);

    void clearTexture();

private:
    glm::vec4 color;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess = 0;
    glm::vec4 emissions;
    std::optional<gl::texture> _texture;
};