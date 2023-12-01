#include <grass.h>
#include <render.h>
#include <cstdlib>

std::vector<Grass*> grasses;
GLuint Grass::texture;
int Grass::width, Grass::height;
void Grass::generate_grass()
{
  auto pair = LoadTextureEx("grass.png");
  texture = pair.first;
  width = pair.second.first;
  height = pair.second.second;
  for (int i = 0; i < 10; ++i)
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
void Grass::RenderGrasses()
{
  for (int i = 0; i < grasses.size(); ++i)
  {
    grasses[i]->Render();
    RenderTexture(grasses[i]->vao, texture);
  }
}
Grass::Grass(float x, float y):x(x), y(y)
{
  vao = LoadVerticesEx(x, y, width, height);
}

void Grass::Render()
{
}
