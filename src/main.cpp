#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <Shader.h>
#include <fstream>
#include <sstream>
#include <array>
#include <SOIL2.h>
#include <vector>
//#include <SDL_image.h> No longer using SDL_image as I couldn't get image loading to work with it. SOIL2 is being used instead.

GLuint load_vertices(GLfloat old_vertices[32]);
std::pair<GLuint, GLuint>load_texture_and_vertices(const char imagePath[], int raw_x, int raw_y);
GLuint load_texture(const char imagePath[]);
std::vector <GLuint*> vbo_cache;

std::vector<GLuint*> ebo_cache;

std::vector<GLuint*> vao_cache;

const GLuint WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
    //////////////////// INIT INIT /////////////////////////////
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); //?


    //////////////////////// Create Window //////////////////////
    SDL_Window* window = SDL_CreateWindow("OpenGL", 300, 300, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    //////////////////////// INIT GLEW //////////////////////
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
      std::cout << "Couldn't Initalise GLEW" << std::endl;
      return EXIT_FAILURE;
    }

    //////////////////////// Create Viewport //////////////////////
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    // Shaders (see Shader.h)
    Shader our_shader( "core.vs", "core.frag" );

    /////////////////////// Vertex Data //////////////////////
    //auto texture_png = load_texture("mower.png");
    auto pair = load_texture_and_vertices("test_image.jpg", 200, 200);
    GLuint vao = pair.first;
    GLuint texture_jpg = pair.second;
    pair = load_texture_and_vertices("mower.png", 300, 300);
    GLuint vao2 = pair.first;
    GLuint texture_png = pair.second;

    /////////////////////// Loading Texture //////////////////////

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////// Game Loop ///////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    SDL_Event event;
    while (true)
    {
        if (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            break;
          }
        }
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        // Draw the triangle
        our_shader.Use( );
        glActiveTexture( GL_TEXTURE0 );


        glUniform1i( glGetUniformLocation( our_shader.program, "ourTexture" ), 0 );

        glBindTexture(GL_TEXTURE_2D, texture_png);
        glBindVertexArray(vao2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, texture_jpg);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the screen buffers
        SDL_GL_SwapWindow(window);
    }
    /////////////////////////////// Clean Up //////////////////////////////
    for (auto vao : vao_cache)
    {
      glDeleteVertexArrays(1, &(*vao));

    }
    for (auto vbo : vbo_cache)
    {
      glDeleteVertexArrays(1, &(*vbo));

    }
    for (auto ebo : ebo_cache)
    {
      glDeleteVertexArrays(1, &(*ebo));

    }
    vao_cache.clear();
    vbo_cache.clear();
    ebo_cache.clear();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

std::pair<GLuint,GLuint>load_texture_and_vertices(const char imagePath[] , int raw_x, int raw_y)
{
  // Relative positions now work!!
  GLuint texture;
  int width, height;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unsigned char* image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  // Free image (texture kept)
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);
  float adj_x = 0;
  float adj_y = 0;
  if (raw_x != 0) adj_x = (2.0f * ((float)raw_x / WIDTH)) - 1.0f;
  if (raw_y != 0) adj_y = -((2.0f * ((float)raw_y / HEIGHT)) - 1.0f);
  float adj_w = 0;
  float adj_h = 0;
  if (width != 0) adj_w = (2.0f * ((float)width / WIDTH));
  if (height != 0) adj_h = -((2.0f * ((float)height / HEIGHT)));

  GLfloat vertices[] = {
    // Positions          // Colors           // Texture Coords
     adj_x + adj_w,  adj_y,        0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
     adj_x + adj_w , adj_y + adj_h, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
     adj_x,         adj_y + adj_h, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
     adj_x,         adj_y,        0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
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
  int width, height;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unsigned char* image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  // Free image (texture kept)
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);
  return texture;
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
