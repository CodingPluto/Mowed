#ifndef	ANIMATION_H
#define	ANIMATION_H

#include <iostream>
#include <vector>
#include <SDL.h>

class  animation
{
public:
	animation();
	GetFrame();
	SetNextAnmation

private:
	std::vector<std::vector<SDL_Texture>> animations_;
	int animation_;
	int animation_fps_:
	int next_animation;
	
};

#endif // ANIMATION_H