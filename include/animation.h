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
	animation(std::string name, int x, int y);
	GLuint GetFrame();
	void Setstate(int state);
	void QueState(int state);
	//GLuint vao_ = NULL;
	int width_;
	int height_;

private:
	std::vector<std::vector<GLuint>> animations_;
	std::pair<int, int> animation_frame_ = {0,0};
	int animation_fps_ = 8;
//	int next_animation_;
	int last_timestep_ = 0;
	std::vector<int> state_que_;
	
};

#endif // ANIMATION_H