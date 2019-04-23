import glm
import math
import pygame
from OpenGL.GL import *
from pygame.locals import *

from scene import Scene, Edge


def aspect_ratio(size: (int, int)):
    width, height = size
    return width / height


def set_display_size(size: (int, int)):
    """Configures OpenGL and pygame to use a display with specified size."""
    pygame.display.set_mode(size, HWSURFACE | DOUBLEBUF | OPENGL | RESIZABLE)
    glViewport(0, 0, *size)


def compile_shader(source: str, shader_type: Constant):
    shader = glCreateShader(shader_type)
    glShaderSource(shader, source)
    glCompileShader(shader)
    if not glGetShaderiv(shader, GL_COMPILE_STATUS):
        raise RuntimeError("Compile error: %s" % glGetShaderInfoLog(shader))
    return shader


def main():
    pygame.init()
    display = (800, 600)
    pygame.display.gl_set_attribute(GL_MULTISAMPLEBUFFERS, 1)
    pygame.display.gl_set_attribute(GL_MULTISAMPLESAMPLES, 8)
    pygame.display.set_caption("group project")
    set_display_size(display)

    scene = Scene()
    scene.add_edge(Edge(Vec3d(-100, -100, 0), Vec3d(100, -100, 0)))
    scene.add_edge(Edge(Vec3d(100, -100, 0), Vec3d(0, 50 * math.sqrt(3), 0)))
    scene.add_edge(Edge(Vec3d(0, 50 * math.sqrt(3), 0), Vec3d(-100, -100, 0)))
    glClearColor(1, 1, 1, 1)
    glEnable(GL_LINE_SMOOTH)

    view = glm.lookAt((0, 0, -300), (0, 0, 0), (0, 1, 0))
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

        scene.draw(view, projection)

        pygame.time.wait(100)
        pygame.display.flip()


main()
