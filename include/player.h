#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <GL/glew.h>

#include <SDL_OpenGL.h>
#include <animation.h>

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
  static GLuint _player_textures[8];
  PlayerState _state;
  SDL_Rect _rect;
  const Uint8* _keyboard;
  void Controller();
public:
  Player();
  void Update();
  void Render();
  GLint texture;
  GLint vao;
  animation animation_;
};


#endif //PLAYER_H