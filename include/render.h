#ifndef RENDER_H
#define RENDER_H
#include <SOIL2.h>
#include <GL/glew.h>

#include <SDL_opengl.h>
#include <iostream>
GLuint load_vertices_ex(int raw_x, int raw_y, int raw_width, int raw_height);
GLuint load_vertices(GLfloat old_vertices[32]);
GLuint load_texture(const char imagePath[]);

std::pair<GLuint,std::pair<int,int>>load_texture_ex(const char imagePath[]);

std::pair<GLuint, GLuint>load_texture_and_vertices(const char imagePath[], int raw_x, int raw_y);
#endif //RENDER_H