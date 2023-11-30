#ifndef GRASS_H
#define GRASS_H
#include <GL/glew.h>
#include <SDL_OpenGL.h>
#include <SDL.h>

class Grass
{
private:
  float x, y;
  int _width, _height;

public:
  static void generate_grass();
  static void free_grass();
  static void render_grasses();
  Grass(float x, float y);
  GLuint texture;
  GLuint vao;
  void render();
};


#endif