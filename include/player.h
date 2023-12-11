#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <GL/glew.h>

#include <SDL_OpenGL.h>
#include <animation.h>
#include <item.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Player
{
private:
  glm::vec2 starting_position = {};
  static GLuint player_textures_[8];
  const Uint8* keyboard_;
  void Controller();
  float myX = 4;
  Item * holding_ = nullptr;
  glm::mat4 player_model;
  glm::vec2 velocity;
public:
  SDL_FRect rect_ = {0,0,0,0};
  Player(float x, float y);
  void Update();
  void Render();
  animation animation_;
  GLuint vao_;
  void PickUp(Item* item);
  void PutDown();
  Item* close_ = nullptr;
};


#endif //PLAYER_H