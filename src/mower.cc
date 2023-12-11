#include <mower.h>

Mower::Mower() : animation_("mower", rect_.x, rect_.y)
{

}

void Mower::Render()
{
	Update();
}

void Mower::Update()
{
	//interest vector calculation
	std::pair<int, int> interest;
	interest.first = (target_item_ -> rect_.x - rect_.x) * mower_speed_;
	interest.second = (target_item_ -> rect_.y - rect_.y) * mower_speed_;
	float norm = sqrt((interest.first * interest.first) + (interest.second * interest.second));
	interest.first = (interest.first / norm) * interest_amount;
	interest.second = (interest.second / norm) * interest_amount;

	// obstructions vector calculation
	std::pair<int, int> obs_vector;
	for (auto obs : obstructions_) {
		std::pair<int,int> buffer = obs;
		//inversion of direction
		buffer.first = buffer.first * -1;
		buffer.second = buffer.second * -1;
		//inversion of distance
		buffer.first = 250 / buffer.first;
		buffer.second = 250 / buffer.second;
		//scaling
		buffer.first = buffer.first * danger_amount;
		buffer.second = buffer.second * danger_amount;
		//sum to vector
		obs_vector.first += buffer.first;
		obs_vector.first += buffer.second;
	}

	std::pair<int, int> velocity;
	velocity.first = interest.first + obs_vector.first;
	velocity.second = interest.second + obs_vector.second;

	rect_.x += velocity.first * mower_speed_;
	rect_.y += velocity.second * mower_speed_;
}

void Mower::SetTarget(Item* item)
{
	target_item_ == item;
}

void Mower::ChangeTargetType()
{
	target_type_ = ~target_type_;
}
