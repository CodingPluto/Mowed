#include <player/Player.h>
#include <SDL.h>
#include <iostream>
#include <render.h>


void Player::controller()
{
  if (keyboard[SDL_SCANCODE_D])
  {
    rect.x += 3;
  }
  if (keyboard[SDL_SCANCODE_A])
  {
    rect.x -= 3;
  }
  if (keyboard[SDL_SCANCODE_S])
  {
    rect.y += 3;
  }
  if (keyboard[SDL_SCANCODE_W])
  {
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
  camera_x = rect.x - (WIDTH / 2 - rect.w / 2);
  camera_y = rect.y - (HEIGHT / 2 - rect.h / 2);
  controller();
}

void Player::render()
{
  std::cout << "Rect: " << rect.x << " : " << rect.y << " : " << rect.w << " : " << rect.h << std::endl;
  vao = load_vertices_ex(rect.x, rect.y, rect.w, rect.h);
}
