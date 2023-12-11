#include <player.h>
#include <SDL.h>
#include <iostream>
#include <render.h>
#include <Shader.h>
#include <Grass.h>
GLuint Player::player_textures_[8] = {};
float speed = 0.5;
float z = 0;
void Player::Controller()
{

  if (keyboard_[SDL_SCANCODE_D])
  {
    //_state = player_walk_left;
    velocity.x += speed;
  }
  if (keyboard_[SDL_SCANCODE_A])
  {
    //_state = player_walk_right;
    velocity.x -= speed;
  }
  if (keyboard_[SDL_SCANCODE_S])
  {
    //_state = player_walk_down;
    velocity.y += speed;
  }
  if (keyboard_[SDL_SCANCODE_W])
  {
    //_state = player_walk_up;
    velocity.y -= speed;
  }
  if (keyboard_[SDL_SCANCODE_EQUALS])
  {
    //_state = player_walk_up;
    if (speed <= 25) speed += speed / speed / 2;
    else speed = 25;
  }
  if (keyboard_[SDL_SCANCODE_MINUS])
  {
    if (speed > 0.5) speed -= speed;
    else speed = 0.5;
  }
  if (keyboard_[SDL_SCANCODE_BACKSPACE])
  {
      PutDown();
  }
  if (keyboard_[SDL_SCANCODE_RETURN])
  {
      PickUp(close_);
  }
}

Player::Player(float x, float y):keyboard_(SDL_GetKeyboardState(0)), animation_("player", rect_.x, rect_.y)
{
  std::cout << "Entered Constructor" << std::endl;
  velocity.x = 0;
  velocity.y = 0;
  starting_position.x = x;
  starting_position.y = y;
  rect_.x = 0;
  rect_.y = 0;
  std::cout << "Created Player" << std::endl;
  vao_ = LoadVerticesEx(rect_.x, rect_.y, animation_.width_, animation_.height_);
}




void Player::Update()
{
  Controller();
  rect_.x += velocity.x;
  rect_.y += velocity.y;
  velocity.x *= 0.7;
  velocity.y *= 0.7;
  if (rect_.x > (GRASS_BORDER_X + GRASS_BORDER_OFFSET_X - animation_.width_ / 2) - starting_position.x)
  {
    rect_.x = GRASS_BORDER_X + GRASS_BORDER_OFFSET_X - animation_.width_ / 2 - starting_position.x;
  }
  else if (rect_.x < (GRASS_BORDER_OFFSET_X + animation_.width_ / 2) - starting_position.x)
  {
    rect_.x = GRASS_BORDER_OFFSET_X + animation_.width_ / 2 - starting_position.x;
  }

  if (rect_.y > (GRASS_BORDER_Y + GRASS_BORDER_OFFSET_Y - animation_.height_ / 2) - starting_position.y)
  {
    rect_.y = (GRASS_BORDER_Y + GRASS_BORDER_OFFSET_Y - animation_.height_ / 2) - starting_position.y;
  }
  else if (rect_.y < (GRASS_BORDER_OFFSET_Y + animation_.height_ / 2) - starting_position.y)
  {
    rect_.y = GRASS_BORDER_OFFSET_Y + animation_.height_ / 2 - starting_position.y;
  }

  if (holding_ != nullptr) {
      holding_->rect_.x = (rect_.x + starting_position.x + (WIDTH/2));
      holding_->rect_.y = (rect_.y + starting_position.y + (HEIGHT/2));
  }
  float adj_w = -1;
  float adj_h = -1;
  adj_w = (2.0f * ((float)animation_.width_ / WIDTH));
  adj_h = -((2.0f * ((float)animation_.height_ / HEIGHT)));
  float adj_x = -1;
  float adj_y = -1;
  adj_x = (2.0f * ((float)(rect_.x) / WIDTH)) - 1.0f;
  adj_y = -((2.0f * ((float)(rect_.y) / HEIGHT)) - 1.0f);
  auto vec = ScreenCoordinatesConvert(starting_position.x, starting_position.y);
  camera_x = adj_x + 1 - (adj_w / 2) + vec.x;
  camera_y = adj_y - 1 - (adj_h / 2) + vec.y;
}


void Player::Render()
{

  player_model = glm::translate(glm::mat4(1.0f), glm::vec3(camera_x + 1,camera_y - 1, 0.0f));
  glUniformMatrix4fv(glGetUniformLocation(Shader::shader_program->program, "model"), 1, GL_FALSE, glm::value_ptr(player_model));
  GLuint frame_tex = animation_.GetFrame();
  glBindTexture(GL_TEXTURE_2D, frame_tex);
  RenderTexture(vao_, frame_tex);
  glBindTexture(GL_TEXTURE_2D,0);
}

void Player::PickUp(Item* item)
{     
    holding_ = item;
}

void Player::PutDown()
{
    holding_ = nullptr;
}

int Player::GetDistanceToItem(Item* item)
{
    std::pair<int, int> buffer_vector;
    buffer_vector.first =  item->rect_.x - (rect_.x + starting_position.x + (WIDTH / 2));
    buffer_vector.second =  item->rect_.y - (rect_.y + starting_position.y + (HEIGHT / 2));
    int sum = (buffer_vector.first * buffer_vector.first) + (buffer_vector.second * buffer_vector.second);
    int norm = sqrt(sum);
    return norm;
}
