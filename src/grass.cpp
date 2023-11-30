#include <grass.h>
#include <render.h>


std::vector<Grass*> grasses;
void Grass::generate_grass()
{
  for (int i = 0; i < 10; ++i)
  {
    Grass *grass = new Grass(i * 5, i * 5);
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
    render_texture(grasses[i]->vao, grasses[i]->texture);
  }
}
Grass::Grass(float x, float y):x(x), y(y)
{
  auto pair = load_texture_ex("grass.png");
  texture = pair.first;
  _width = pair.second.first;
  _height = pair.second.second;

}

void Grass::render()
{
  vao = load_vertices_ex(x, y, _width, _height);
}
