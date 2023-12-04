#include <player.h>
#include <SDL.h>
#include <iostream>
#include <render.h>
GLuint Player::_player_textures[8] = {};
const float speed = 0.03;

void Player::Controller()
{
  if (_keyboard[SDL_SCANCODE_D])
  {
    _state = player_walk_left;
    _rect.x += speed;
  }
  if (_keyboard[SDL_SCANCODE_A])
  {
    _state = player_walk_right;
    _rect.x -= speed;
  }
  if (_keyboard[SDL_SCANCODE_S])
  {
    _state = player_walk_down;
    _rect.y += speed;
  }
  if (_keyboard[SDL_SCANCODE_W])
  {
    _state = player_walk_up;
    _rect.y -= speed;
  }

}

Player::Player():_keyboard(SDL_GetKeyboardState(0)), animation_("player") // this anim constructor is currently causing a seg fault.
{
  std::cout << "Entered Constructor" << std::endl;
  _rect.x = 0;
  _rect.y = 0;
  auto pair = LoadTextureEx("mower.png");
  texture = pair.first;
  _rect.w = pair.second.first;
  _rect.h = pair.second.second;
  vao = LoadVerticesEx(_rect.x, _rect.y, _rect.w, _rect.h);


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
  //std::cout << "Rect: " << _rect.x << " : " << _rect.y << " : " << _rect.w << " : " << _rect.h << std::endl;
}
