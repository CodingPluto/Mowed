#ifndef	MOWER_H
#define	MOWER_H

#include <animation.h>
#include <SDL.h>
#include <vector>
#include <item.h>

const int interest_amount = 5;
const float danger_amount = 0.01;

class Mower
{
public:
	Mower();
	animation animation_;
	SDL_Rect rect_ = { 0,0,0,0 };
	void Render();
	void Update();
	GLuint vao_;
	void SetTarget(Item * item);
	void ChangeTargetType();
private:
	Item* target_item_ = nullptr;
	bool target_type_ = 0; //  0 for item, 1 for player
	float mower_speed_ = 0.6;
	std::vector<std::pair<int, int>> obstructions_;
};



#endif