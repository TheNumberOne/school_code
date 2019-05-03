import glm
import numpy
from OpenGL.GL import *
from OpenGL.arrays import vbo

_edge_vertex_shader = """#version 100
attribute vec3 pos;
attribute vec3 in_color;
varying lowp vec3 color;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(pos.x, pos.y, pos.z, 1.0);
    color = in_color;
}
"""

_edge_fragment_shader = """#version 100
varying lowp vec3 color;
void main()
{
    gl_FragColor = vec4(color, 1.0);
}
"""

FLOATS_PER_EDGE = 12
FLOATS_PER_VERTEX = 6
BYTES_PER_VERTEX = FLOATS_PER_VERTEX * sizeof(GLfloat)
POSITION_INDEX = 0
POSITION_BYTES_INDEX = POSITION_INDEX * sizeof(GLfloat)
COLOR_INDEX = 3
COLOR_BYTES_INDEX = COLOR_INDEX * sizeof(GLfloat)
POSITION_SIZE = 3
COLOR_SIZE = 3
POSITION_SHADER_LOCATION = 0
COLOR_SHADER_LOCATION = 1


class Edge:

    def __init__(self, p1, p2, color, speed):
        self.p1 = p1.xyz
        self.p2 = p2.xyz
        self.color = color.rgb
        self.speed = speed

    def data(self):
        return [*self.p1, *self.color, *self.p2, *self.color]

    def len(self):
        return glm.distance(self.p1, self.p2)

    def time(self):
        return self.len() / self.speed

    @staticmethod
    def data_index(edge_num, vertex, data_index):
        return edge_num * FLOATS_PER_EDGE + vertex * FLOATS_PER_VERTEX + data_index


def compile_shader(source: str, shader_type: Constant):
    shader = glCreateShader(shader_type)
    glShaderSource(shader, source)
    glCompileShader(shader)
    if not glGetShaderiv(shader, GL_COMPILE_STATUS):
        raise RuntimeError("Compile error: %s" % glGetShaderInfoLog(shader))
    return shader


class Scene:
    _program = None

    @staticmethod
    def _generate_and_bind_program():
        if Scene._program is None:
            vertex_shader = compile_shader(_edge_vertex_shader, GL_VERTEX_SHADER)
            fragment_shader = compile_shader(_edge_fragment_shader, GL_FRAGMENT_SHADER)
            program = glCreateProgram()
            glAttachShader(program, vertex_shader)
            glAttachShader(program, fragment_shader)
            glLinkProgram(program)
            if not glGetProgramiv(program, GL_LINK_STATUS):
                raise RuntimeError("Linking error: %s" % glGetProgramInfoLog(program))
            glDeleteShader(vertex_shader)
            glDeleteShader(fragment_shader)
            Scene._program = program
        glUseProgram(Scene._program)

    def __init__(self):
        self._vao = None
        self._vbo = None
        self._edges = []
        self._displayed_edges = []
        self._num_edges = 0
        self._num_displayed_edges = 0
        self._vbo_current = False

    def _update_and_bind_vbo(self):
        if self._vao is None:
            self._vao = glGenVertexArrays(1)
        glBindVertexArray(self._vao)
        if self._vbo is None or not self._vbo_current:
            self._vbo = vbo.VBO(numpy.array(self._displayed_edges, numpy.float32))
            self._vbo.bind()
            glVertexAttribPointer(
                POSITION_SHADER_LOCATION,
                POSITION_SIZE,
                GL_FLOAT,
                GL_FALSE,
                BYTES_PER_VERTEX,
                self._vbo + POSITION_BYTES_INDEX
            )
            glVertexAttribPointer(
                COLOR_SHADER_LOCATION,
                COLOR_SIZE,
                GL_FLOAT,
                GL_FALSE,
                BYTES_PER_VERTEX,
                self._vbo + COLOR_BYTES_INDEX
            )
            glEnableVertexAttribArray(0)
            glEnableVertexAttribArray(1)
            self._vbo.unbind()
            self._vbo_current = True

    def _uniform(self, name, value):
        view_loc = glGetUniformLocation(self._program, name)
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm.value_ptr(value))

    def draw(self, view, projection):
        Scene._generate_and_bind_program()
        self._update_and_bind_vbo()
        self._uniform("view", view)
        self._uniform("projection", projection)
        glDrawArrays(GL_LINES, 0, self._num_displayed_edges * 2)

    def add_edge(self, edge: Edge):
        self._edges += [edge]
        self._num_edges += 1
        self._vbo_current = False

    def update(self, time):
        if self._num_displayed_edges > 0:
            last_edge_index = self._num_displayed_edges - 1
            data_index = Edge.data_index(last_edge_index, 1, POSITION_INDEX)
            last_vertex = glm.vec3(*self._displayed_edges[data_index: data_index + POSITION_SIZE])
            last_edge = self._edges[last_edge_index]
            next_target = last_edge.p2

            time_left = glm.distance(last_vertex, next_target) / last_edge.speed

            if time_left > time:
                frac = time / time_left
                last_vertex = frac * next_target + (1 - frac) * last_vertex
                self._displayed_edges[data_index: data_index + POSITION_SIZE] = [*last_vertex]
                self._vbo_current = False
                return
            if time_left > 0:
                self._displayed_edges[data_index: data_index + POSITION_SIZE] = [*next_target]
                self._vbo_current = False
                time -= time_left

        if self._num_displayed_edges == self._num_edges:
            return
        self._vbo_current = False
        while self._num_displayed_edges < self._num_edges:
            next_edge = self._edges[self._num_displayed_edges]
            self._displayed_edges += next_edge.data()
            self._num_displayed_edges += 1
            if next_edge.time() > time:
                frac = time / next_edge.time()
                data_index = Edge.data_index(self._num_displayed_edges - 1, 1, POSITION_INDEX)
                last_vertex = frac * next_edge.p2 + (1 - frac) * next_edge.p1
                self._displayed_edges[data_index: data_index + POSITION_SIZE] = [*last_vertex]
                return
            else:
                time -= next_edge.time()
