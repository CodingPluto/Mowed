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
	std::pair<GLuint, GLuint> GetFrame(int x, int y);
	void Setstate(int state);
	void QueState(int state);

private:
	std::vector<std::vector<std::pair<GLuint, std::pair<int,int> >>> animations_;
	std::pair<int, int> animation_frame_ = {0,0};
	int animation_fps_ = 8;
//	int next_animation_;
	int last_timestep_ = 0;
	std::vector<int> state_que_;
	
};

#endif // ANIMATION_H