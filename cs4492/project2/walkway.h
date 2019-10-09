#pragma once


#include <GL/gl.h>

class walkway {
public:
    walkway(float width, float length);

    void draw() const;

private:
    float width = 5;
    float length = 5;
    GLuint texture = 1;
    float texture_scale_x = 2;
    float texture_scale_y = 2;
};


