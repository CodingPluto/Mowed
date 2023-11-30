#ifndef GRASS_H
#define GRASS_H
#include <GL/glew.h>
#include <SDL_OpenGL.h>
#include <SDL.h>

class Grass
{
private:
  float x, y;
public:
  static void generate_grass();
  static void free_grass();
  static void render_grasses();
  Grass(float x, float y);
  static GLuint texture;
  static int width, height;
  GLuint vao;
  void render();
};


#endif