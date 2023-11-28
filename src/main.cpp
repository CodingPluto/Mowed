#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <Shader.h>
#include <fstream>
#include <sstream>
#include <array>
#include <SDL_image.h>
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

  SDL_Window* window_sdl = SDL_CreateWindow("SDL2", kWindowX + kWidth, kWindowY, kWidth, kHeight, 0);
  SDL_Renderer* renderer_sdl = SDL_CreateRenderer(window_sdl, -1, 0);
  IMG_Init(IMG_INIT_JPG);
  SDL_Texture* text = SDL_CreateTextureFromSurface(renderer_sdl, IMG_Load("mower.jpg"));

  SDL_Window* window = SDL_CreateWindow("OpenGL", kWindowX, kWindowY, kWidth, kHeight, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  
  glewExperimental = GL_TRUE;

  if (GLEW_OK != glewInit()){
    std::cout << "Couldn't Initalise GLEW" << std::endl;

    return EXIT_FAILURE;
  }
  glViewport(0, 0, kWidth, kHeight);

  Shader shader_program("core.vs","core.frag");



  // x, y, z
  GLfloat vertices[] = {
  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom right
  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
  };
  //0,1
  //6,7
  //12,13
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

  GLuint vbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);


  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  //unbinding
  //glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


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
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3); // actual draw part lol
  glBindVertexArray(0);

  // Draw OpenGL;
  SDL_GL_SwapWindow(window);
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();


  return EXIT_SUCCESS;
}