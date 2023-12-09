#include <render.h>
#include <vector>
 std::vector <GLuint*> vbo_cache;

 std::vector<GLuint*> ebo_cache;
 glm::mat4 viewProjection;
 std::vector<GLuint*> vao_cache;
 float camera_x;
 float camera_y;

std::pair<GLuint, std::pair<int, int>>LoadTextureEx(const char imagePath[]){
  GLuint texture;
  int _width, _height;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unsigned char* image = SOIL_load_image(imagePath, &_width, &_height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  // Free image (texture kept)
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  return std::pair<GLint, std::pair<int, int>>(texture, std::pair<int, int>(_width, _height));
}

/*
void UpdateVertices(float raw_x, float raw_y) {
  // Assuming the sprite occupies the first two vertices in the vertex array
  float adj_x = -1;
  float adj_y = -1;
  adj_x = (2.0f * ((float)raw_x / WIDTH)) - 1.0f;
  adj_y = -((2.0f * ((float)raw_y / HEIGHT)) - 1.0f);
  GLfloat vertices[] = {
    // Positions                                           // Colors                   // Texture Coords
     adj_x + adj_w,  adj_y,
     adj_x + adj_w , adj_y + adj_h,
     adj_x,          adj_y + adj_h,
     adj_x,          adj_y,
  };


  vertices[0] = newX;
  vertices[1] = newY;

  // Update the VBO with the new vertex data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/


GLuint LoadVerticesEx(float raw_x, float raw_y, int raw_width, int raw_height){
  float adj_x = -1;
  float adj_y = -1;
  adj_x = (2.0f * ((float)raw_x / WIDTH)) - 1.0f;
  adj_y = -((2.0f * ((float)raw_y / HEIGHT)) - 1.0f);
  float adj_w = -1;
  float adj_h = -1;
  adj_w = (2.0f * ((float)raw_width / WIDTH));
  adj_h = -((2.0f * ((float)raw_height / HEIGHT)));

  GLfloat vertices[] = {
    // Positions                                           // Colors                   // Texture Coords
     adj_x + adj_w,  adj_y,                             
     adj_x + adj_w , adj_y + adj_h,                     
     adj_x,          adj_y + adj_h,                
     adj_x,          adj_y,                       
  };

  GLuint indices[] = {
      0, 1, 3, // First Triangle
      1, 2, 3  // Second Triangle
  };
  /////////////////////// Creatng Buffers //////////////////////
  GLuint vbo, vao, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  // vao
  glBindVertexArray(vao);
  // vbo
    /////////////////////// Setting Attributes //////////////////////
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  // ebo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0); // Unbind VAO

  vbo_cache.emplace_back(&vbo);
  vao_cache.emplace_back(&vao);
  ebo_cache.emplace_back(&ebo);

  return vao;
}

void RenderTexture(GLuint vao, GLuint texture)
{
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

