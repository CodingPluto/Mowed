#include <grass.h>
#include <render.h>
#include <cstdlib>
#include <Shader.h>
const int grasses_number = 1000;
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
    /*= {

    // Positions 
     adj_x + adj_w,  adj_y,
     adj_x + adj_w , adj_y + adj_h,
     adj_x,          adj_y + adj_h,
     adj_x,          adj_y,
  };*/
  float adj_w = -1;
  float adj_h = -1;
  adj_w = (2.0f * ((float)width / WIDTH));
  adj_h = -((2.0f * ((float)height / HEIGHT)));
  for (int i = 0; i < grasses_number; ++i)
  {
    int x = rand() % 1000 - WIDTH/2;
    int y = rand() % 1000 - HEIGHT/2;
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

    indices[0 + (i * 6)] = 0 + (i * 4);
    indices[1 + (i * 6)] = 1 + (i * 4);
    indices[2 + (i * 6)] = 3 + (i * 4);

    indices[3 + (i * 6)] = 1 + (i * 4);
    indices[4 + (i * 6)] = 2 + (i * 4);
    indices[5 + (i * 6)] = 3 + (i * 4);
    //Grass *grass = new Grass(x, y);
    //grasses.emplace_back(grass);

  }

  /*
  GLuint indices[] = {
      0, 1, 3, // First Triangle
      1, 2, 3,  // Second Triangle
      4, 5, 7, // Third Triangle
      5, 6, 7  // Fourth Triangle
  };
  */
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

  //glBindTexture(GL_TEXTURE_2D, texture);
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
  glBindTexture(GL_TEXTURE_2D,0);

}
Grass::Grass(float x, float y):x(x), y(y)
{
  //vao = LoadVerticesEx(x, y, width, height);
}

void Grass::Render()
{
}
