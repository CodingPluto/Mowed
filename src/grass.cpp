#include <grass.h>
#include <render.h>
#include <cstdlib>

std::vector<Grass*> grasses;
GLuint Grass::texture;
int Grass::width, Grass::height;
void Grass::generate_grass()
{
  auto pair = load_texture_ex("grass.png");
  texture = pair.first;
  width = pair.second.first;
  height = pair.second.second;
  for (int i = 0; i < 1000; ++i)
  {
    int x = rand() % 800 - 30;
    int y = rand() % 600 - 30;
    Grass *grass = new Grass(x, y);
    grasses.emplace_back(grass);
  }

}
void Grass::free_grass()
{
  for (int i = 0; i < grasses.size(); ++i)
  {
    delete grasses[i];
  }
}
void Grass::render_grasses()
{
  for (int i = 0; i < grasses.size(); ++i)
  {
    grasses[i]->render();
    render_texture(grasses[i]->vao, texture);
  }
}
Grass::Grass(float x, float y):x(x), y(y)
{
  vao = load_vertices_ex(x, y, width, height);
}

void Grass::render()
{
}
