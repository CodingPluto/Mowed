#include <grass.h>
#include <render.h>
#include <cstdlib>

std::vector<Grass*> Grass::grasses;
GLuint Grass::texture;
int Grass::width, Grass::height;
void Grass::generate_grass()
{
  auto pair = LoadTextureEx("grass.png");
  texture = pair.first;
  width = pair.second.first;
  height = pair.second.second;
  for (int i = 0; i < 1000; ++i)
  {
    int x = rand() % 8000 - 4000;
    int y = rand() % 6000 - 3000;
    Grass *grass = new Grass(x, y);
    grasses.emplace_back(grass);
  }

}
void Grass::FreeGrass()
{
  for (int i = 0; i < grasses.size(); ++i)
  {
    delete grasses[i];
  }
}
void Grass::RenderGrasses()
{
  glBindTexture(GL_TEXTURE_2D, texture);
  for (int i = 0; i < grasses.size(); ++i)
  {
    //grasses[i]->Render();
    //std::cout << "grass rendered!" << std::endl;
    RenderTexture(grasses[i]->vao, texture);
  }
  glBindVertexArray(0);

}
Grass::Grass(float x, float y):x(x), y(y)
{
  vao = LoadVerticesEx(x, y, width, height);
}

void Grass::Render()
{
}
