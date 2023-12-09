#include <grass.h>
#include <render.h>
#include <cstdlib>
#include <Shader.h>

std::vector<Grass*> Grass::grasses;
GLuint Grass::texture;
int Grass::width, Grass::height;
void Grass::generate_grass()
{
  auto pair = LoadTextureEx("grass.png");
  texture = pair.first;
  width = pair.second.first;
  height = pair.second.second;
  for (int i = 0; i < 100; ++i)
  {
    int x = rand() % 1600 - 800;
    int y = rand() % 1200 - 600;
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
  glm::mat4 grass_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
  glUniformMatrix4fv(glGetUniformLocation(Shader::shader_program->program, "model"), 1, GL_FALSE, glm::value_ptr(grass_model));

  glBindTexture(GL_TEXTURE_2D, texture);
  for (int i = 0; i < grasses.size(); ++i)
  {
    //grasses[i]->Render();
    //std::cout << "grass rendered!" << std::endl;
    RenderTexture(grasses[i]->vao, texture);
  }
  glBindTexture(GL_TEXTURE_2D,0);

}
Grass::Grass(float x, float y):x(x), y(y)
{
  vao = LoadVerticesEx(x, y, width, height);
}

void Grass::Render()
{
}
