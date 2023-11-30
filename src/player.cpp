#include <player.h>
#include <SDL.h>
#include <iostream>
#include <render.h>
GLuint Player::_player_textures[8] = {};

void Player::controller()
{
  if (_keyboard[SDL_SCANCODE_D])
  {
    _state = player_walk_left;
    _rect.x += 3;
  }
  if (_keyboard[SDL_SCANCODE_A])
  {
    _state = player_walk_right;
    _rect.x -= 3;
  }
  if (_keyboard[SDL_SCANCODE_S])
  {
    _state = player_walk_down;
    _rect.y += 3;
  }
  if (_keyboard[SDL_SCANCODE_W])
  {
    _state = player_walk_up;
    _rect.y -= 3;
  }

}

Player::Player():_keyboard(SDL_GetKeyboardState(0))
{
  _rect.x = 0;
  _rect.y = 0;
  auto pair = load_texture_ex("mower.png");
  texture = pair.first;
  _rect.w = pair.second.first;
  _rect.h = pair.second.second;
  vao = load_vertices_ex(_rect.x, _rect.y, _rect.w, _rect.h);


}

void Player::update()
{
  controller();
  camera_x = _rect.x - (WIDTH / 2 - _rect.w / 2);
  camera_y = _rect.y - (HEIGHT / 2 - _rect.h / 2);
}

void Player::render()
{
  //std::cout << "Rect: " << _rect.x << " : " << _rect.y << " : " << _rect.w << " : " << _rect.h << std::endl;
}
