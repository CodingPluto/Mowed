#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <GL/glew.h>

#include <SDL_OpenGL.h>
#include <animation.h>


class Player
{
private:
  static GLuint _player_textures[8];
  const Uint8* _keyboard;
  void Controller();
public:
  SDL_FRect _rect = {0,0,0,0};
  Player();
  void Update();
  void Render();
  animation animation_;
};


#endif //PLAYER_H