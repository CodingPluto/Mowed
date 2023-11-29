#include <player/Player.h>
#include <SDL.h>
#include <iostream>
#include <render.h>
GLuint Player::player_textures[8] = {};

void Player::controller()
{
  if (keyboard[SDL_SCANCODE_D])
  {
    state = player_walk_left;
    rect.x += 3;
  }
  if (keyboard[SDL_SCANCODE_A])
  {
    state = player_walk_right;
    rect.x -= 3;
  }
  if (keyboard[SDL_SCANCODE_S])
  {
    state = player_walk_down;
    rect.y += 3;
  }
  if (keyboard[SDL_SCANCODE_W])
  {
    state = player_walk_up;
    rect.y -= 3;
  }



}

Player::Player():keyboard(SDL_GetKeyboardState(0))
{
  rect.x = 0;
  rect.y = 0;
  auto pair = load_texture_ex("mower.png");
  texture = pair.first;
  rect.w = pair.second.first;
  rect.h = pair.second.second;

}

void Player::update()
{
  std::cout << HEIGHT << std::endl;
  controller();
  camera_x = rect.x - (WIDTH / 2 - rect.w / 2);
  camera_y = rect.y - (HEIGHT / 2 - rect.h / 2);
}

void Player::render()
{
  std::cout << "Rect: " << rect.x << " : " << rect.y << " : " << rect.w << " : " << rect.h << std::endl;
  vao = load_vertices_ex(rect.x, rect.y, rect.w, rect.h);
}
