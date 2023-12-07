#ifndef	ITEM_H
#define	ITEM_H

#include <SDL.h>
#include <animation.h>
#include <GL/glew.h>
#include <SDL_OpenGL.h>

class Item
{
public:
	Item(std::string name);
	Item* Get_Pointer();
	void Render();
	SDL_FRect rect_ = {0, 0, 0, 0};
	void update();
protected:
	animation animation_;
	GLuint vao_;
};


#endif   //ITEM_H