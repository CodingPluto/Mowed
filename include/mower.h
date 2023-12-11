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
private:
	Item target_;
};



#endif