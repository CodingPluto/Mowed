#include <player.h>
#include <SDL.h>
#include <iostream>
#include <render.h>
GLuint Player::player_textures_[8] = {};
const float speed = 3;

void Player::Controller()
{
  if (keyboard_[SDL_SCANCODE_D])
  {
    //_state = player_walk_left;
    rect_.x += speed;
  }
  if (keyboard_[SDL_SCANCODE_A])
  {
    //_state = player_walk_right;
    rect_.x -= speed;
  }
  if (keyboard_[SDL_SCANCODE_S])
  {
    //_state = player_walk_down;
    rect_.y += speed;
  }
  if (keyboard_[SDL_SCANCODE_W])
  {
    //_state = player_walk_up;
    rect_.y -= speed;
  }

}

Player::Player():keyboard_(SDL_GetKeyboardState(0)), animation_("player", rect_.x, rect_.y)
{
  std::cout << "Entered Constructor" << std::endl;
  rect_.x = 0;
  rect_.y = 0;
  std::cout << "Created Player" << std::endl;

}

const float cameraSpeedX = 400;
const float cameraSpeedY = 300;
void Player::Update()
{
  Controller();
  camera_x = (rect_.x / cameraSpeedX) - 1;
  camera_y = (( - rect_.y)/ cameraSpeedY) + 1;
}

void Player::Render()
{
  vao_ = LoadVerticesEx(rect_.x, rect_.y, animation_.width, animation_.height);
  GLuint frame_tex = animation_.GetFrame();
  glBindTexture(GL_TEXTURE_2D, frame_tex);
  RenderTexture(vao_, frame_tex);
  glBindVertexArray(0);
}
