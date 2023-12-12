#ifndef	MOWER_H
#define	MOWER_H

#include <animation.h>
#include <SDL.h>
#include <vector>
#include <item.h>

const float steer_force = 0.1;
const int look_ahead = 100;
const int num_rays = 8;

class Mower
{
public:
	Mower();
	animation animation_;
	SDL_FRect rect_ = { 250,250,0,0 };
	void Render();
	void Update();
	GLuint vao_;
	void SetTarget(Item * item);
	void ChangeTargetType();
private:
	Item* target_item_ = nullptr;
	bool target_type_ = 0; //  0 for item, 1 for player
	float mower_speed_ = 0.5;
	std::vector<float> GetInterest();
	std::vector<int> GetDanger();
	std::pair<float, float> angles_[num_rays];
};



#endif