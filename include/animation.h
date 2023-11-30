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
	void QueState(int state);

private:
	std::vector<std::vector<std::pair<GLuint, GLuint>>> animations_;
	std::pair<int, int> animation_frame_; 
	int animation_fps_;
//	int next_animation_;
	int last_timestep_ = 0;
	std::vector<int> state_que_;
	
};

#endif // ANIMATION_H