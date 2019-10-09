#pragma once

static const char* vertex_shader_text =
    "uniform mat4 MVP;\n"
    "attribute vec3 vCol;\n"
    "attribute vec2 vPos;\n"
    "uniform vec3 inColor;\n"
    "varying vec3 color;\n"
    "void main()\n"
    "{\n"
    "    //float x = vPos.x * 0.1;\n"
    "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
    "    //gl_Position = MVP * vec4(x, vPos.y, 0.0, 1.0);\n"
    "    color = vCol;\n"
    "    color = inColor;\n"
    "    //color = vec3(1.0, 0.0, 0.0);\n"
    "}\n";

static const char* fragment_shader_text =
    "varying vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(color, 1.0);\n"
    "}\n";

struct FlatProgram {
  FlatProgram() {
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    color_location = glGetUniformLocation(program, "inColor");

    // glEnableVertexAttribArray(vpos_location);
    // glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
    //                       sizeof(float) * 2, (void*) 0);
  }

  GLuint program;
  // GLuint vertex_buffer, vertex_shader, fragment_shader;//, program;
  GLuint vertex_shader, fragment_shader;//, program;
  GLint mvp_location, vpos_location, vcol_location, color_location;
};
