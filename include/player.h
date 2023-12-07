#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <GL/glew.h>

#include <SDL_OpenGL.h>
#include <animation.h>


class Player
{
private:
  static GLuint player_textures_[8];
  const Uint8* keyboard_;
  void Controller();
  float myX = 4;
public:
  SDL_FRect rect_ = {0,0,0,0};
  Player();
  void Update();
  void Render();
  animation animation_;
  GLuint vao_;

};


#endif //PLAYER_H