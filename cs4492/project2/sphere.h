#pragma once


class sphere {
public:
    void draw() const;

private:
    unsigned int num_strips = 100;
    unsigned int num_slices = 100;

    glm::vec3 get_point(unsigned int strip, unsigned int slice) const;
};


