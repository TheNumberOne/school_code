import glm
import math
import pygame as pg
import OpenGL.GL as gl


class Camera:
    move_speed = 2
    rotate_speed = 2 * glm.pi() / 3

    def __init__(self, initial_screen_height=10):
        self.near = .01
        self.far = 1000
        self.field_of_vision = glm.pi() / 4
        self.eye = glm.vec3(0, 0, initial_screen_height / 2 / math.tan(self.field_of_vision / 2))
        self.forward = glm.vec3(0, 0, -1)
        self.up = glm.vec3(0, 1, 0)
        self.display = (800, 600)
        self.set_display_size(self.display)
        self.forward_rate = 0
        self.roll_rate = 0
        self.right_rate = 0

    def aspect_ratio(self):
        width, height = self.display
        return width / height

    def projection(self):
        return glm.perspectiveFov(self.field_of_vision, *self.display, self.near, self.far)

    def view(self):
        return glm.lookAt(self.eye, self.forward + self.eye, self.up)

    def set_display_size(self, display):
        self.display = display
        pg.display.set_mode(display, pg.HWSURFACE | pg.DOUBLEBUF | pg.OPENGL | pg.RESIZABLE)
        gl.glViewport(0, 0, *display)

    def move_pixels(self, dx, dy):
        width, height = self.display
        rotate_up = self.field_of_vision * -dy / height
        rotate_right = self.field_of_vision * self.aspect_ratio() * -dx / width
        rotate = glm.rotate(glm.identity(glm.mat4), rotate_right, self.up)
        rotate = glm.rotate(rotate, rotate_up, glm.cross(self.forward, self.up))
        self.forward = (rotate * glm.vec4(self.forward, 1)).xyz

    def move(self, rate):
        self.forward_rate = rate

    def move_right(self, rate):
        self.right_rate = rate

    def roll(self, rate):
        self.roll_rate = rate

    def update(self, ms):
        time = ms / 1000
        self.eye += self.forward * time * self.forward_rate
        self.eye += glm.cross(self.forward, self.up) * time * self.right_rate
