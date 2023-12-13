#ifndef GRASS_H
#define GRASS_H
#include <GL/glew.h>
#include <SDL_OpenGL.h>
#include <SDL.h>
#include <vector>

#define GRASS_NUMBER 3000
#define GRASS_BORDER_X 10000
#define GRASS_BORDER_Y 10000
#define GRASS_BORDER_OFFSET_X 0 
#define GRASS_BORDER_OFFSET_Y 0
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