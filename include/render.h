#ifndef RENDER_H
#define RENDER_H
#include <SOIL2.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL_opengl.h>
#include <iostream>
#include <vector>
extern unsigned int WIDTH, HEIGHT;
extern float camera_x, camera_y;
extern std::vector <GLuint*> vbo_cache;

extern std::vector<GLuint*> ebo_cache;
extern glm::mat4 viewProjection;
extern std::vector<GLuint*> vao_cache;

extern float camera_x;
extern float camera_y;

GLuint LoadVerticesEx(float raw_x, float raw_y, int raw_width, int raw_height);
//GLuint LoadVertices(GLfloat old_vertices[32]);
//GLuint LoadTexture(const char imagePath[]);
void RenderTexture(GLuint vao, GLuint texture);
std::pair<GLuint,std::pair<int,int>>LoadTextureEx(const char imagePath[]);
//std::pair<GLuint, GLuint>LoadTextureAndVertices(const char imagePath[], int raw_x, int raw_y);
#endif //RENDER_H
glm::vec2 ScreenCoordinatesConvert(float x, float y);
void SetModel(const glm::mat4 &model);