#ifndef SHED_H
#define SHED_H

#include <animation.h>
#include <SDL.h>

class Shed
{
public:
	Shed(int x, int y);
	animation animation_;
	SDL_FRect rect_ = { 0,0,0,0 };
	void Render();
	GLuint vao_;
private:


};



#endif // SHED_H
