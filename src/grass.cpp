#include <grass.h>
#include <render.h>
#include <cstdlib>
#include <Shader.h>
const int grasses_number = 100000;
std::vector<Grass*> Grass::grasses;
GLuint Grass::texture;
GLuint vao_test;
int Grass::width, Grass::height;
void Grass::generate_grass()
{
  auto pair = LoadTextureEx("grass.png");
  texture = pair.first;
  width = pair.second.first;
  height = pair.second.second;
  GLfloat *vertices = new GLfloat[(4 * 2) * grasses_number];
  GLuint *indices = new GLuint[6 * grasses_number];

  float adj_w = -1;
  float adj_h = -1;
  adj_w = (2.0f * ((float)width / WIDTH));
  adj_h = -((2.0f * ((float)height / HEIGHT)));
  for (int i = 0; i < grasses_number; ++i)
  {
    int x = rand() % 10000 - WIDTH/2;
    int y = rand() % 10000 - HEIGHT/2;
    float adj_x = -1;
    float adj_y = -1;
    adj_x = (2.0f * ((float) x / WIDTH)) - 1.0f;
    adj_y = -((2.0f * ((float) y / HEIGHT)) - 1.0f);

    vertices[(i * 8) + 0] = adj_x + adj_w;
    vertices[(i * 8) + 1] = adj_y;

    vertices[(i * 8) + 2] = adj_x + adj_w;
    vertices[(i * 8) + 3] = adj_y + adj_h;

    vertices[(i * 8) + 4] = adj_x;
    vertices[(i * 8) + 5] = adj_y + adj_h;

    vertices[(i * 8) + 6] = adj_x;
    vertices[(i * 8) + 7] = adj_y;

    const unsigned int index_offset = i * 6;
    const unsigned int indice_offset = i * 4;
    indices[index_offset + 0] = indice_offset + 0;
    indices[index_offset + 1] = indice_offset + 1;
    indices[index_offset + 2] = indice_offset + 3;

    indices[index_offset + 3] = indice_offset + 1;
    indices[index_offset + 4] = indice_offset + 2;
    indices[index_offset + 5] = indice_offset + 3;
    //Grass *grass = new Grass(x, y);
    //grasses.emplace_back(grass);

  }
  GLuint vbo, vao, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  // vao
  glBindVertexArray(vao);
  // vbo
    /////////////////////// Setting Attributes //////////////////////
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (4 * 2) * grasses_number, vertices, GL_STATIC_DRAW);
  // ebo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6 * grasses_number,indices, GL_STATIC_DRAW);
  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0); // Unbind VAO

  vbo_cache.emplace_back(&vbo);
  vao_cache.emplace_back(&vao);
  ebo_cache.emplace_back(&ebo);
  vao_test = vao;
  delete[] vertices;
  delete[] indices;
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


  //glActiveTexture(GL_TEXTURE0);
  //glBindTexture(GL_TEXTURE_2D, texture);
  glBindTextureUnit(0, texture);
  glBindVertexArray(vao_test);
  glDrawElements(GL_TRIANGLES, 6 * grasses_number, GL_UNSIGNED_INT, nullptr);
  //glBindVertexArray(0);
  /*
  for (int i = 0; i < grasses.size(); ++i)
  {
    //grasses[i]->Render();
    //std::cout << "grass rendered!" << std::endl;
    RenderTexture(grasses[i]->vao, texture);
  }*/
  glBindTextureUnit(0, 0);
  glBindVertexArray(0);
}
Grass::Grass(float x, float y):x(x), y(y)
{
  //vao = LoadVerticesEx(x, y, width, height);
}

void Grass::Render()
{
}
