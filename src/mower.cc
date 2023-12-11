#include <mower.h>
#include <render.h>
#include <shader.h>
Mower::Mower() : animation_("mow", rect_.x, rect_.y)
{
	std::cout << "Animation Width: " << animation_.width_ << std::endl;
	std::cout << "Animation Height: " << animation_.height_ << std::endl;
	vao_ = LoadVerticesEx(rect_.x, rect_.y, animation_.width_, animation_.height_);
	
}

void Mower::Render()
{
	//Update();
	rect_.x = 0;
	rect_.y = 0;
	auto vec = ScreenCoordinatesConvert(rect_.x, rect_.y);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	SetModel(model);

	GLuint frame_tex = animation_.GetFrame();
	glBindTexture(GL_TEXTURE_2D, frame_tex);
	RenderTexture(vao_, frame_tex);
	glBindVertexArray(0);
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
