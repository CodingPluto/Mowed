#ifndef	MOWER_H
#define	MOWER_H

#include <animation.h>
#include <SDL.h>
#include <vector>
#include <item.h>

class Mower
{
public:
	Mower();
	animation animation_;
	SDL_Rect rect_ = { 0,0,0,0 };
	void Render();
	void Update();
	GLuint vao_;
private:
	Item* target_item_;
	bool target = 0; //  0 for item, 1 for player
	
};



#endif