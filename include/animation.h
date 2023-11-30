#ifndef	ANIMATION_H
#define	ANIMATION_H

#include <iostream>
#include <vector>
#include <SOIL2.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

class  animation
{
public:
	animation(std::string name);
	GLint GetFrame();
	void Setstate(int state);

private:
	std::vector<std::vector<std::pair<GLuint, GLuint>(texture, vao)>> animations_;
	std::pair<int> animation_frame_;
	int animation_fps_:
	int next_animation;
	int last_timestep = 0;
	
};

#endif // ANIMATION_H