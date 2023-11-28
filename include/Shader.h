#ifndef SNAKE_SHADER_H
#define SNAKE_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_Opengl.h>

class Shader{
public:
  GLuint program;

  void Use()
  {
    glUseProgram(program);
  }

  Shader(const GLchar *vertex_path, const GLchar *fragment_path){
    std::string vertex_code, fragment_code;
    std::ifstream v_shader_file, f_shader_file;

    // ensures exceptions
    v_shader_file.exceptions(std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::badbit);

    try{
      v_shader_file.open(vertex_path);
      f_shader_file.open(fragment_path);

      std::stringstream v_shader_stream, f_shader_stream;

      v_shader_stream << v_shader_file.rdbuf();
      f_shader_stream << f_shader_file.rdbuf();

      v_shader_file.close();
      f_shader_file.close();

      vertex_code = v_shader_stream.str();
      fragment_code = f_shader_stream.str();

    }
    catch(std::ifstream::failure e)
    {
      std::cout << "Shader files not read properly." << std::endl;
    }
    const GLchar* v_shader_code = vertex_code.c_str();
    const GLchar* f_shader_code = fragment_code.c_str();

    std::cout << "VERTEX SHADER CODE: \n" << v_shader_code << std::endl;
    std::cout << "FRAGMENT SHADER CODE: \n" << f_shader_code << std::endl;

    GLint success;
    GLchar info_log[512];

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &v_shader_code, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
      std::cout << "Couldn't compile vertex shaders.\n" << info_log << std::endl;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &f_shader_code, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
      std::cout << "Couldn't compile fragment shaders.\n" << info_log << std::endl;
    }
    program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(program, 512, NULL, info_log);
      std::cout << "Couldn't link shaders.\n" << info_log << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

  }

};

#endif