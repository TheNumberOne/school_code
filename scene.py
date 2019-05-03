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


class Edge:
    def __init__(self, p1, p2, color):
        self.p1 = p1.xyz
        self.p2 = p2.xyz
        self.color = color.rgb

    def data(self):
        return [*self.p1, *self.color, *self.p2, *self.color]


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
        self._num_edges = 0
        self._vbo_current = False
        self._num_edges_to_show = 0

    def _update_and_bind_vbo(self):
        if self._vao is None:
            self._vao = glGenVertexArrays(1)
        glBindVertexArray(self._vao)
        if self._vbo is None or not self._vbo_current:
            self._vbo = vbo.VBO(numpy.array(self._edges, numpy.float32))
            self._vbo.bind()
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, self._vbo)
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, self._vbo + 12)
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
        glDrawArrays(GL_LINES, 0, self._num_edges_to_show * 2)

    def add_edge(self, edge: Edge):
        self._edges += edge.data()
        self._num_edges += 1
        self._vbo_current = False

    def update(self, ms):
        if self._num_edges_to_show < self._num_edges:
            self._num_edges_to_show += 1
