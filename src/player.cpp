#include <player.h>
#include <SDL.h>
#include <iostream>
#include <render.h>
GLuint Player::_player_textures[8] = {};
const float speed = 0.03;

void Player::Controller()
{
  if (_keyboard[sdl_scancode_d])
  {
    //_state = player_walk_left;
    _rect.x += speed;
  }
  if (_keyboard[sdl_scancode_a])
  {
    //_state = player_walk_right;
    _rect.x -= speed;
  }
  if (_keyboard[sdl_scancode_s])
  {
    //_state = player_walk_down;
    _rect.y += speed;
  }
  if (_keyboard[sdl_scancode_w])
  {
    //_state = player_walk_up;
    _rect.y -= speed;
  }

}

Player::Player():_keyboard(SDL_GetKeyboardState(0)), animation_("player", _rect.x, _rect.y)
{
  std::cout << "Entered Constructor" << std::endl;
  _rect.x = 0;
  _rect.y = 0;
  std::cout << "Created Player" << std::endl;

}

void Player::Update()
{
  Controller();
  camera_x = _rect.x;
  camera_y = -_rect.y;
}

void Player::Render()
{   
    GLuint frame_tex = animation_.GetFrame();
    glBindTexture(GL_TEXTURE_2D, frame_tex);
    RenderTexture(animation_.vao_, frame_tex);
    glBindVertexArray(0);
}
