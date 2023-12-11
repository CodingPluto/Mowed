#ifndef GRASS_H
#define GRASS_H
#include <GL/glew.h>
#include <SDL_OpenGL.h>
#include <SDL.h>
#include <vector>

class Grass
{
private:
  static GLuint vbo;
  float x, y;
public:
  static void generate_grass();
  static void FreeGrass();
  static void RenderGrasses();
  Grass(float x, float y);
  static GLuint texture;
  static int width, height;
  GLuint vao;
  void Render();
  static std::vector<Grass*> grasses;
};


#endif