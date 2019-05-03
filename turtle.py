import glm
import pygame
from OpenGL.GL import *
from pygame import *

from camera import Camera
from camera import _c
from scene import Scene, Edge

_DEBUG = False
turtle_funcs = []


class Turtle:
    def __init__(self):
        self._pos = glm.vec4(0, 0, 0, 1)
        self._up = glm.vec4(0, 0, 1, 1)
        self._forward = glm.vec4(1, 0, 0, 1)
        self._scene = Scene()
        self._color = glm.vec4(0, 0, 0, 1)
        self._background_color = (1, 1, 1, 1)

    def forward(self, distance):
        new_pos = self._pos + self._forward * distance
        self._scene.add_edge(Edge(self._pos, new_pos, self._color))
        self._pos = new_pos

    def backward(self, distance):
        self.forward(-distance)

    def left(self, angle):
        self._forward = glm.rotate(glm.identity(glm.mat4), glm.radians(angle), self._up.xyz) * self._forward

    def right(self, angle):
        self.left(-angle)

    def roll_clockwise(self, angle):
        """Rotates the turtle around its axis of movement clockwise as viewed from behind"""
        self._up = glm.rotate(glm.identity(glm.mat4), glm.radians(angle), self._forward) * self._up

    def roll_counter_clockwise(self, angle):
        """Rotates the turtle around its axis of movement counter-clockwise as viewed from behind"""
        self.roll_clockwise(-angle)

    def up(self, angle):
        """Rotates the turtle upwards"""
        rotation = glm.rotate(glm.identity(glm.mat4), glm.radians(angle), glm.cross(self._forward.xyz, self._up.xyz))
        self._up = rotation * self._up
        self._forward = rotation * self._forward

    def down(self, angle):
        self.up(-angle)

    def goto(self, x, y=None, z=0):
        if y is None:
            if len(x) == 2:
                x, y = x
            elif len(x) >= 3:
                x, y, z = x
            else:
                raise ValueError("Can't convert {} to a point" % x)
        self._pos.xyz = x, y, z

    def color(self, x, y=None, z=None):
        try:
            c = Color(x, y, z, 0)
        except ValueError:
            try:
                c = Color(x)
            except ValueError:
                c = Color(*x)
        self._color = glm.vec3(c.r, c.g, c.b)

    def background_color(self):
        return self._background_color

    def set_background_color(self, color):
        self._background_color = color


_the_turtle = None


def _t():
    global _the_turtle
    if _the_turtle is None:
        _the_turtle = Turtle()
    return _the_turtle


def forward(distance): _t().forward(distance)


def backward(distance): _t().backward(distance)


def left(angle): _t().left(angle)


def right(angle): _t().right(angle)


def roll_clockwise(angle): _t().roll_clockwise(angle)


def roll_counter_clockwise(angle): _t().roll_counter_clockwise(angle)


def up(angle): _t().up(angle)


def down(angle): _t().down(angle)


def goto(x, y=None, z=0): _t().goto(x, y, z)


def color(x, y=None, z=None): _t().color(x, y, z)


def set_background_color(red, green, blue, alpha): _t().set_background_color((red, green, blue, alpha))


def set_display_size(size: (int, int)):
    """Configures OpenGL and pygame to use a display with specified size."""
    pygame.display.set_mode(size, HWSURFACE | DOUBLEBUF | OPENGL | RESIZABLE)
    glViewport(0, 0, *size)


def main_loop():
    camera = _c()
    pygame.init()
    pygame.display.gl_set_attribute(GL_MULTISAMPLEBUFFERS, 1)
    pygame.display.gl_set_attribute(GL_MULTISAMPLESAMPLES, 4)
    pygame.display.set_caption("group project")
    camera.open_window()
    clock = pygame.time.Clock()

    print("OpenGL version %s" % glGetString(GL_VERSION).decode("ascii"))

    if _DEBUG:
        def cb_dbg_msg(source, msg_type, msg_id, severity, length, raw, user):
            msg = raw[0:length]
            print('debug', source, msg_type, msg_id, severity, msg)

        # Install our debug message callback
        glDebugMessageCallback(GLDEBUGPROC(cb_dbg_msg), None)

    b_color = _t().background_color()
    glClearColor(b_color[0], b_color[1], b_color[2], b_color[3])
    glEnable(GL_LINE_SMOOTH)
    glEnable(GL_DEPTH_TEST)

    grabbed = False

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return
            elif event.type == pygame.VIDEORESIZE:
                display = event.w, event.h
                camera.set_display_size(display)
            elif event.type == pygame.KEYUP and event.key == pygame.K_ESCAPE:
                pygame.quit()
                return
            elif event.type == pygame.MOUSEMOTION and grabbed:
                camera.move_pixels(*event.rel)
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
                grabbed = not grabbed
                pygame.event.set_grab(grabbed)
                pygame.mouse.set_visible(not grabbed)
            elif event.type == pygame.KEYDOWN or event.type == pygame.KEYUP:
                keys = pygame.key.get_pressed()
                forward = keys[pygame.K_w] - keys[pygame.K_s]
                right = keys[pygame.K_d] - keys[pygame.K_a]
                roll = keys[pygame.K_r] - keys[pygame.K_q]
                camera.move(forward * Camera.move_speed)
                camera.move_right(right * camera.move_speed)
                camera.roll_clockwise(roll)

        camera.update(clock.tick(30))
        glClear(GL_COLOR_BUFFER_BIT)
        glClear(GL_DEPTH_BUFFER_BIT)

        _t()._scene.draw(camera.view(), camera.projection())

        pygame.display.flip()
