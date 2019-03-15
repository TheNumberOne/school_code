#include "walkway.h"

void walkway::draw() const {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glTexCoord2d(-width / 2 / texture_scale_x, -length / 2 / texture_scale_y);
    glVertex3f(-width / 2, 0, 0);
    glTexCoord2d(width / 2 / texture_scale_x, -length / 2 / texture_scale_y);
    glVertex3f(width / 2, 0, 0);
    glTexCoord2d(width / 2 / texture_scale_x, length / 2 / texture_scale_y);
    glVertex3f(width / 2, 0, -length);
    glTexCoord2d(-width / 2 / texture_scale_x, length / 2 / texture_scale_y);
    glVertex3f(-width / 2, 0, -length);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

walkway::walkway(float width, float length) : width(width), length(length) {}
