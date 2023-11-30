#include <render.h>
#include <vector>
 std::vector <GLuint*> vbo_cache;

 std::vector<GLuint*> ebo_cache;

 std::vector<GLuint*> vao_cache;
float camera_x = 0; float camera_y = 0;
std::pair<GLuint, std::pair<int, int>>load_texture_ex(const char imagePath[])
{
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





GLuint load_vertices_ex(int raw_x, int raw_y, int raw_width, int raw_height, bool relative)
{
  std::cout << "CAMERA POSITION: " << camera_x << " : " << camera_y << std::endl;
  float adj_x = -1;
  float adj_y = -1;
  adj_x = (2.0f * ((float)raw_x / WIDTH)) - 1.0f;
  adj_y = -((2.0f * ((float)raw_y / HEIGHT)) - 1.0f);
  float adj_w = -1;
  float adj_h = -1;
  adj_w = (2.0f * ((float)raw_width / WIDTH));
  adj_h = -((2.0f * ((float)raw_height / HEIGHT)));

  float cam_x_adj = -1;
  float cam_y_adj = -1;
  cam_x_adj = (2.0f * ((float)camera_x / WIDTH));
  cam_y_adj = -((2.0f * ((float)camera_y / HEIGHT)));

  GLfloat vertices[] = {
    // Positions                                           // Colors                   // Texture Coords
     adj_x - cam_x_adj + adj_w,  adj_y - cam_y_adj,          0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
     adj_x - cam_x_adj + adj_w , adj_y + adj_h - cam_y_adj,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
     adj_x - cam_x_adj,          adj_y + adj_h - cam_y_adj,  0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
     adj_x - cam_x_adj,          adj_y - cam_y_adj,          0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
  };

  GLuint indices[] =
  {
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
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // ebo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  /////////////////////// Setting Attributes //////////////////////
  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // Texture Coordinate attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0); // Unbind VAO

  vbo_cache.emplace_back(&vbo);
  vao_cache.emplace_back(&vao);
  ebo_cache.emplace_back(&ebo);

  return vao;
}





std::pair<GLuint, GLuint>load_texture_and_vertices(const char imagePath[], int raw_x, int raw_y)
{
  // Relative positions now work!!
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

  float adj_x = 0;
  float adj_y = 0;
  adj_x = (2.0f * ((float)raw_x / WIDTH)) - 1.0f;
  adj_y = -((2.0f * ((float)raw_y / HEIGHT)) - 1.0f);
  float adj_w = 0;
  float adj_h = 0;
  adj_w = (2.0f * ((float)_width / WIDTH));
  adj_h = -((2.0f * ((float)_height / HEIGHT)));
  float cam_x_adj = -1;
  float cam_y_adj = -1;
  cam_x_adj = (2.0f * ((float)camera_x / WIDTH));
  cam_y_adj = -((2.0f * ((float)camera_y / HEIGHT)));

  GLfloat vertices[] = {
    // Positions                                           // Colors                   // Texture Coords
     adj_x - cam_x_adj + adj_w,  adj_y - cam_y_adj,          0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
     adj_x - cam_x_adj + adj_w , adj_y + adj_h - cam_y_adj,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
     adj_x - cam_x_adj,          adj_y + adj_h - cam_y_adj,  0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
     adj_x - cam_x_adj,          adj_y - cam_y_adj,          0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
  };

  GLuint indices[] =
  {
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
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // ebo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  /////////////////////// Setting Attributes //////////////////////
  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // Texture Coordinate attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0); // Unbind VAO

  vbo_cache.emplace_back(&vbo);
  vao_cache.emplace_back(&vao);
  ebo_cache.emplace_back(&ebo);


  return std::pair<GLuint, GLuint>(texture, vao);
}


GLuint load_texture(const char imagePath[])
{
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
  return texture;
}

void render_texture(GLuint vao, GLuint texture)
{
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}


GLuint load_vertices(GLfloat old_vertices[32])
{
  GLfloat vertices[32];
  for (int i = 0; i < 32; ++i)
  {
    vertices[i] = old_vertices[i];
  }
  GLuint indices[] =
  {
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
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // ebo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


  vbo_cache.emplace_back(&vbo);
  vao_cache.emplace_back(&vao);
  ebo_cache.emplace_back(&ebo);
  return vao;
}
