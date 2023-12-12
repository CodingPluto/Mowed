#include <mower.h>
#include <render.h>
#include <shader.h>
#include <cmath>
#include <algorithm>

Mower::Mower() : animation_("mower", rect_.x, rect_.y)
{
	std::cout << "Animation Width: " << animation_.width_ << std::endl;
	std::cout << "Animation Height: " << animation_.height_ << std::endl;
	vao_ = LoadVerticesEx(rect_.x, rect_.y, animation_.width_, animation_.height_);
	for (int i = 0; i < num_rays; i++)
	{
		float angle = i * 2 * M_PI / num_rays;
		angles_[i].first = cos(angle);
		angles_[i].second = sin(angle);
	}
}

void Mower::Render()
{
	Update();
	auto vec = ScreenCoordinatesConvert(rect_.x, rect_.y);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, 0.1f));
	SetModel(model);

	GLuint frame_tex = animation_.GetFrame();
	glBindTexture(GL_TEXTURE_2D, frame_tex);
	RenderTexture(vao_, frame_tex);
	glBindVertexArray(0);
}

void Mower::Update()
{
	//interest vector calculation
	std::vector interest = GetInterest();
	
}

void Mower::SetTarget(Item* item)
{
	target_item_ = item;
}

void Mower::ChangeTargetType()
{
	target_type_ = ~target_type_;
}

std::vector<float> Mower::GetInterest()
{
	std::vector<float> interest;
	std::pair<int,int> to_target;
	to_target.first = rect_.x - target_item_->rect_.x;
	to_target.second = rect_.y - target_item_->rect_.y;
	for (auto i : angles_)
	{
		//dot product
		float d = (i.first * to_target.first) + (i.second * to_target.second);
		interest.push_back(std::max(0.0f, d));
	}
	return interest;
}

std::vector<int> Mower::GetDanger()
{
	return std::vector<int>();
}


