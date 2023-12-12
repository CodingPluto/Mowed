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
	for (int i = 0; i < num_rays; i++)
	{
		rays_[i].first = angles_[i].first * look_ahead;
		rays_[i].second = angles_[i].second * look_ahead;
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
	std::vector<float> interest = GetInterest();
	std::vector<int> danger = GetDanger();
	
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
	std::vector<int> danger(num_rays);
	for (int i = 0; i < num_rays; i++)
	{
		std::pair<float, float> thisray;
		thisray.first = rays_[i].first + rect_.x;
		thisray.second = rays_[i].second + rect_.y;
		for (auto obj : objects_)
		{
			std::pair<int, int> points[] = {
			{obj.x, obj.y}, // top left
			{obj.x + obj.w, obj.y}, // top right
			{obj.x + obj.w, obj.y + obj.h}, // bottom right
			{obj.x, obj.y + obj.h} // bottom left
			// use lines with adject indexes
			};
			int lenght = sizeof(points) / sizeof(std::pair<int, int>);
			for (int i = 0; i < lenght; i++)
			{
				std::pair<int, int> p1 = { rect_.x, rect_.y };
				std::pair<int, int> q1 = thisray;

				std::pair<int, int> p2 = points[i];
				if (i == lenght - 1)
				{
					std::pair<int, int> q2 = points[i + 1];
				}
				else
				{
					std::pair<int, int> q2 = points[i+1];
				}

			}
		}
	}
	return danger;
}


int GetOrientation(std::pair<int, int> p, std::pair<int, int> q, std::pair<int, int> r)
{
	if (q.first <= std::max(p.first, r.first) && q.first >= std::min(p.first, r.first) &&
		q.second <= std::max(p.second, r.second) && q.second >= std::min(p.second, r.second))
		return true;

	return false;
}
