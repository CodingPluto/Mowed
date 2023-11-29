#ifndef PLAYER_PLAYER_H
#define PLAYER_PLAYER_H
#include <SDL.h>
#include <GL/glew.h>

#include <SDL_OpenGL.h>
class Player
{
private:
  SDL_Rect rect;
  void controller();
  const Uint8* keyboard;
public:
  Player();
  void update();
  void render();
  GLint texture;
  GLint vao;
};


#endif //PLAYER_PLAYER_H