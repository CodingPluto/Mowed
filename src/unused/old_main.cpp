#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <Shader.h>
#include <fstream>
#include <sstream>
#include <array>
#include <SDL_image.h>
#include <SOIL2.h>
const GLint kWidth = 800, kHeight = 600;
const GLint kWindowY = 200;
const GLint kWindowX = 200;



int main(int argc, char *argv[]){

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  // Version 3.3
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); //?

  IMG_Init(IMG_INIT_PNG);
  //SDL_Texture* text = SDL_CreateTextureFromSurface(renderer_sdl, IMG_Load("mower.jpg"));

  SDL_Window* window = SDL_CreateWindow("OpenGL", kWindowX, kWindowY, kWidth, kHeight, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  
  glewExperimental = GL_TRUE;

  if (GLEW_OK != glewInit()){
    std::cout << "Couldn't Initalise GLEW" << std::endl;

    return EXIT_FAILURE;
  }
  glViewport(0, 0, kWidth, kHeight);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



  Shader shader_program("core.vs","core.frag");



  // x, y, z            // colours         // Texture Coordinates (NORMALISED 0 - 1)
  GLfloat vertices[] =
  {
    0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // Top right
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // Bottom right
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom left
    -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f
  };

  GLuint indices[] =
  {
    0, 1, 3, // First Triangle
    1, 2, 3 // Second Triangle
  };
  //0,1
  //6,7
  //12,13
  /*
  std::ifstream source;
  try
  {
    source.open("vertices.txt");
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "Vertex file not read properly." << std::endl;
  }
  int i = 0;
  for (std::string line; std::getline(source, line); )   //read stream line by line
  {
    std::istringstream in(line);      //make a stream for the line itself
    in >> vertices[i] >> vertices[i+1] >> vertices[i + 2] >> vertices[i + 3] >> vertices[i + 4] >> vertices[i + 5];
    i += 6;
  }
  source.close();

  for (auto vertice : vertices)
  {
    std::cout << vertice << std::endl;
  }
  */
  GLuint vbo, vao, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


  //Position Attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);


  // Colour Attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // Texture coordinate attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  //unbinding
  //glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); // unbind vao

  GLuint texture;
  int _width = 0; int _height = 0;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // find more abt
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  
  unsigned char *image = SOIL_load_image("test_image.jpg", &_width, &_height, 0, SOIL_LOAD_RGBA);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  SDL_Event event;
  while (true) {

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT){
        break;
      }
    }
  glClearColor(0.1f, 0.1f, 0.4f, 0.5); // set colour
  glClear(GL_COLOR_BUFFER_BIT); // refresh

  shader_program.Use();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(shader_program.program, "My Texture"), 0);


  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // actual draw part lol
  glBindVertexArray(0);
  // Draw OpenGL;
  SDL_GL_SwapWindow(window);
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();


  return EXIT_SUCCESS;
}


/*
  SDL_Surface* image = IMG_Load("test_image.jpg");
  if (!image)
  {
    std::cout << "Couldn't load image" << std::endl;
    std::cout << IMG_GetError() << std::endl;

  }
  else
  {
    _width = image->w;
    _height = image->h;
  }
  GLuint texture_format;
  auto nOfColors = image->format->BytesPerPixel;
  if (nOfColors == 4)     // contains an alpha channel
  {
    if (image->format->Rmask == 0x000000ff){
      texture_format = GL_RGBA;
      std::cout << "Yoo" << std::endl;
    }
    else{
      texture_format = GL_BGRA;
    }
  }
  else if (nOfColors == 3)     // no alpha channel
  {
    if (image->format->Rmask == 0x000000ff)
      texture_format = GL_RGB;
    else
      texture_format = GL_BGR;
  }
  else {
    printf("warning: the image is not truecolor..  this will probably break\n");
    // this error should not go unhandled
  }


  glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, _width, _height, 0, texture_format, GL_UNSIGNED_BYTE, image->pixels);
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);*/