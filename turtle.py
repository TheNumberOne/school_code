from typing import Union

import glm

from scene import Scene, Edge

number = Union[float, int]


class Turtle:
    def __init__(self):
        self._pos = glm.vec3()
        self._up = glm.vec3(0, 0, -1)
        self._forward = glm.vec3(1, 0, 0)
        self._scene = Scene()

    def forward(self, distance):
        new_pos = self._pos + self._forward * distance
        self._scene.add_edge(Edge(self._pos, new_pos))
        self._pos = new_pos

    def left(self, angle):
        self._forward = glm.rotate(self._forward, glm.radians(angle), self._up)


def _t():
    global _the_turtle
    if _the_turtle is None:
        _the_turtle = Turtle()
    return _the_turtle


def forward(distance):
    _t().forward(distance)


def left(distance):
    _t().left(distance)
