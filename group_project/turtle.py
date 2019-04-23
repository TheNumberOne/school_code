import glm
import pygame
from OpenGL.GL import *
from pygame import *

from scene import Scene, Edge


class Turtle:
    def __init__(self):
        self._pos = glm.vec4(0, 0, 0, 1)
        self._up = glm.vec4(0, 0, 1, 1)
        self._forward = glm.vec4(1, 0, 0, 1)
        self._scene = Scene()

    def forward(self, distance):
        new_pos = self._pos + self._forward * distance
        self._scene.add_edge(Edge(self._pos, new_pos))
        self._pos = new_pos

    def left(self, angle):
        self._forward = glm.rotate(glm.identity(glm.mat4), glm.radians(angle), self._up.xyz) * self._forward


_the_turtle = None


def _t():
    global _the_turtle
    if _the_turtle is None:
        _the_turtle = Turtle()
    return _the_turtle


def forward(distance):
    _t().forward(distance)


def left(distance):
    _t().left(distance)


def aspect_ratio(size: (int, int)):
    width, height = size
    return width / height


def set_display_size(size: (int, int)):
    """Configures OpenGL and pygame to use a display with specified size."""
    pygame.display.set_mode(size, HWSURFACE | DOUBLEBUF | OPENGL | RESIZABLE)
    glViewport(0, 0, *size)


def main_loop():
    pygame.init()
    display = (800, 600)
    pygame.display.gl_set_attribute(GL_MULTISAMPLEBUFFERS, 1)
    pygame.display.gl_set_attribute(GL_MULTISAMPLESAMPLES, 8)
    pygame.display.set_caption("group project")
    set_display_size(display)

    glClearColor(1, 1, 1, 1)
    glEnable(GL_LINE_SMOOTH)

    view = glm.lookAt((0, 0, 300), (0, 0, 0), (0, 1, 0))
    projection = glm.perspective(90, aspect_ratio(display), 10, 1000)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return
            if event.type == pygame.VIDEORESIZE:
                display = event.dict['size']
                set_display_size(display)
                projection = glm.perspective(90, aspect_ratio(display), 10, 1000)

            if event.type == pygame.KEYUP and event.key == pygame.K_ESCAPE:
                pygame.quit()
                return

        glClear(GL_COLOR_BUFFER_BIT)

        _t()._scene.draw(view, projection)

        pygame.time.wait(100)
        pygame.display.flip()
