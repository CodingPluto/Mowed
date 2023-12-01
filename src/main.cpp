#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include <Shader.h>
#include <fstream>
#include <sstream>
#include <array>
#include <SOIL2.h>
#include <vector>
#include <player.h>
#include <render.h>
#include <chrono>
#include <thread>
#include <animation.h>
#include <grass.h>

//#include <SDL_image.h> No longer using SDL_image as I couldn't get image loading to work with it. SOIL2 is being used instead.

void GetOpenGLErrors();

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

    Shader our_shader( "core.vs", "core.frag" );





    /////////////////////// Vertex Data //////////////////////
    //auto texture_png = load_texture("mower.png");
    //auto pair = load_texture_ex("test_image.jpg");
    //auto texture_test = pair.first;
    //int test_width = pair.second.first;
    //int test_height = pair.second.second;
    //auto vao = load_vertices_ex(300, 300, test_width, test_height);

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////// Game Loop ///////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    SDL_Event event;
    //Player player;
    Grass::generate_grass();
    animation animation1("grass");

    double old_time = 0;
    double current_time = 0;
    double delta_time = 0;
    while (true)
    {
      old_time = current_time;
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
    }
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      our_shader.Use();
      

      glActiveTexture(GL_TEXTURE0);
      //glUniform1i( glGetUniformLocation( our_shader.program, "ourTexture" ), 0 );
      Grass::RenderGrasses();
      SDL_GL_SwapWindow(window);
      current_time = SDL_GetTicks();
      delta_time = (current_time - old_time) * pow(10, -3);
      GetOpenGLErrors();
      std::cout << delta_time << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    for (auto vao : vao_cache)
    {
      glDeleteVertexArrays(1, &(*vao));
    }
    for (auto vbo : vbo_cache)
    {
      glDeleteVertexArrays(1, &(*vbo));
      glDeleteBuffers(1, &(*vbo));
    }
    for (auto ebo : ebo_cache)
    {
      glDeleteVertexArrays(1, &(*ebo));
      glDeleteBuffers(1, &(*ebo));
    }
    GetOpenGLErrors();
    vao_cache.clear();
    vbo_cache.clear();
    ebo_cache.clear();
    /////////////////////////////// Clean Up //////////////////////////////

    Grass::free_grass();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}


void GetOpenGLErrors()
{
  GLenum error;
  while ((error = glGetError()) != GL_NO_ERROR) {
    switch (error) {
    case GL_INVALID_ENUM:
      std::cerr << "OpenGL Error: GL_INVALID_ENUM\n";
      break;
    case GL_INVALID_VALUE:
      std::cerr << "OpenGL Error: GL_INVALID_VALUE\n";
      break;
    case GL_INVALID_OPERATION:
      std::cerr << "OpenGL Error: GL_INVALID_OPERATION\n";
      break;
    case GL_STACK_OVERFLOW:
      std::cerr << "OpenGL Error: GL_STACK_OVERFLOW\n";
      break;
    case GL_STACK_UNDERFLOW:
      std::cerr << "OpenGL Error: GL_STACK_UNDERFLOW\n";
      break;
    case GL_OUT_OF_MEMORY:
      std::cerr << "OpenGL Error: GL_OUT_OF_MEMORY\n";
      break;
      // Add more cases as needed based on the potential error codes
    default:
      std::cerr << "Unknown OpenGL Error\n";
      break;
    }
  }
}