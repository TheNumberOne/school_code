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

    def roll_clockwise(self, rate):
        self.roll_rate = rate

    def update(self, ms):
        time = ms / 1000
        self.eye += self.forward * time * self.forward_rate
        self.eye += glm.cross(self.forward, self.up) * time * self.right_rate
        self.up = (glm.rotate(glm.identity(glm.mat4), self.roll_rate * time, self.forward) * glm.vec4(self.up, 1)).xyz
        
    # User additional programmatic commands.
    def set_camera_position(self, position):
        self.eye = glm.vec3(position)
        
    def set_camera_facing(self, position):
        newFacing = glm.normalize(glm.vec3(position - self.eye))
        self.forward = newFacing
        
        
 # Global camera for programmatic user control.       
_the_camera = None

def _c():
    global _the_camera
    if _the_camera is None:
        _the_camera = Camera()
    return _the_camera

def set_display_size(width, height): _c().set_display_size((width, height))

def look_from(x, y, z): _c().set_camera_position((x, y, z))

def look_at(x, y, z): _c().set_camera_facing((x, y, z))   

