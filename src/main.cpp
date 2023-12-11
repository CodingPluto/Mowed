#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
#include <gas-can.h>

//#include <SDL_image.h> No longer using SDL_image as I couldn't get image loading to work with it. SOIL2 is being used instead.
Shader* Shader::shader_program = nullptr;
void GetOpenGLErrors();
int main(int argc, char *argv[])
{
    camera_x = 0;
    camera_y = 0;
    //////////////////// INIT INIT /////////////////////////////
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); //?


    //////////////////////// Create Window //////////////////////
    SDL_DisplayMode monitor_dimensions;
    if (SDL_GetCurrentDisplayMode(0, &monitor_dimensions) != 0) {
      std::cerr << "SDL_GetCurrentDisplayMode failed: " << SDL_GetError() << std::endl;
      SDL_Quit();
      return 1;
    }
    //std::cout << "Monitor: " << "w: " << monitor_dimensions.w << "h: " << monitor_dimensions.h << std::endl;

    SDL_Window* window = SDL_CreateWindow("OpenGL", 0, 25, monitor_dimensions.w, monitor_dimensions.h - 25, SDL_WINDOW_OPENGL);//SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    WIDTH = monitor_dimensions.w;
    HEIGHT = monitor_dimensions.h -25;
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

    Shader shader = Shader("core.vs", "core.frag");
    Shader::shader_program = &shader;

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////// Game Loop ///////////////////////////////
    //////////////////////////////////////////////////////////////////////////


    glm::vec3 cameraPosition(0.0f, 0.0f, 0.0f);

    SDL_Event event;
    auto keyboard = SDL_GetKeyboardState(0);
    double old_time = 0;
    double current_time = 0;
    double delta_time = 0;
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);
    Grass::generate_grass();
    Player player(5250, 5250);
    std::vector<Item*> items = { &GasCan(5200, 5250), &GasCan(5300, 5250) };
    
    //Mower mower;
    auto time_at_frame_end = std::chrono::system_clock::now();
    double millis_passed_since_previous_frame = 0;
    while (true)
    {
      if (millis_passed_since_previous_frame >= 0.016)
      {
        old_time = current_time;
        if (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            break;
          }
        }
        if (keyboard[SDL_SCANCODE_ESCAPE] || ((keyboard[SDL_SCANCODE_LCTRL] || keyboard[SDL_SCANCODE_RCTRL]) && keyboard[SDL_SCANCODE_W]))
        {
          break;
        }
        player.close_ = nullptr;
        for (Item* i : items) {
            if (player.GetDistanceToItem(i) <= 50) {
                player.close_ = i;
            }
        }
        player.Update();

        glClearColor(0.03f, 0.1f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Shader::shader_program->Use();
        cameraPosition.x = camera_x;
        cameraPosition.y = camera_y;
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraPosition.x, -cameraPosition.y, 0.0f));
        //std::cout << "Camera X: " << cameraPosition.x  << ", Camera Y: " << cameraPosition.y << std::endl;
        viewProjection = projection * view;


        glUniformMatrix4fv(glGetUniformLocation(Shader::shader_program->program, "viewProjection"), 1, GL_FALSE, glm::value_ptr(viewProjection));

        glm::mat4 default_model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f,1.0f,0));
        SetModel(default_model);
        glUniform1f(glGetUniformLocation(Shader::shader_program->program, "opacity"), 1.0f);
        for (Item* i : items) {
            i -> Render();
        }
        glUniform1f(glGetUniformLocation(Shader::shader_program->program, "opacity"), 0.9f);
        player.Render();
        glUniform1f(glGetUniformLocation(Shader::shader_program->program, "opacity"), 0.6f);
        Grass::RenderGrasses();
        SDL_GL_SwapWindow(window);
        current_time = SDL_GetTicks();
        delta_time = (current_time - old_time) * pow(10, -3);
        GetOpenGLErrors();
        std::cout << "Delta Time: " << delta_time << std::endl;

        time_at_frame_end = std::chrono::system_clock::now();
      }
      millis_passed_since_previous_frame = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time_at_frame_end).count() / 1000000.0f;
    }
    /////////////////////////////// Clean Up //////////////////////////////
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
    Grass::FreeGrass();

    GetOpenGLErrors();
    vao_cache.clear();
    vbo_cache.clear();
    ebo_cache.clear();
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