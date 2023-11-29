#ifndef PLAYER_PLAYER_H
#define PLAYER_PLAYER_H
#include <SDL.h>
#include <GL/glew.h>

#include <SDL_OpenGL.h>

enum PlayerState
{
  player_idle = 0,
  player_walk_left,
  player_walk_right,
  player_walk_up,
  player_walk_down
};

class Player
{
private:
  static GLuint player_textures[8];
  PlayerState state;
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