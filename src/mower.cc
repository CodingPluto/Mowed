#include <mower.h>
#include <render.h>
#include <shader.h>
#include <cmath>
#include <algorithm>

Mower::Mower(int x, int y) : animation_("mower")
{
	std::cout << "Animation Width: " << animation_.width_ << std::endl;
	std::cout << "Animation Height: " << animation_.height_ << std::endl;
	rect_.x = x;
	rect_.y = y;
	rect_.w = animation_.width_;
	rect_.h = animation_.height_;
	vao_ = LoadVerticesEx(0, 0, animation_.width_, animation_.height_);
	for (int i = 0; i < num_rays; i++)
	{
		float angle = i * 2 * M_PI / num_rays;
		angles_[i].first = cos(angle);
		angles_[i].second = sin(angle) * -1;
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
	std::cout << vec.x << ", " << vec.y << std::endl;
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, 0.0f));
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
	// remove interest that lines up with danger
	for (int i = 0; i < num_rays; i++)
	{
		if (danger[i] != 0)
		{
			float danger_magnitude = danger[i] / danger_amount;
			danger_magnitude = pow(danger_magnitude, - 1.2);
			/*danger_magnitude = danger_magnitude * 100;
			danger_magnitude = pow(danger_magnitude, danger_amount);*/
			interest[i] -= danger_magnitude;
		}
	}
	// calculate resulatant interest vector
	std::pair<float, float> resultant = { 0, 0 };
	for (int i = 0; i < num_rays; i++)
	{
		std::pair<float, float> buffer_vec;
		buffer_vec.first = angles_[i].first * interest[i];
		buffer_vec.second = angles_[i].second * interest[i];
		resultant.first += buffer_vec.first;
		resultant.second += buffer_vec.second;
	}
	//vector normalisation
	
	float norm = sqrt((resultant.first * resultant.first) + (resultant.second * resultant.second));
	if (norm != 0.0f)
	{
	resultant.first = resultant.first / norm;
	resultant.second = resultant.second / norm;
	}
	else
	{
		resultant = { 0,0 };
	}
	
	//acceleration calculation
	std::pair<float, float> steer;
	steer.first = (resultant.first - velocity.first) * steer_force;
	steer.second = (resultant.second - velocity.second) * steer_force;

	velocity.first += steer.first;
	velocity.second += steer.second;
	{
		float norm = sqrt((velocity.first * velocity.first) + (velocity.second * velocity.second));
		std::pair<float, float>velocity_norm;
		if (norm != 0)
		{
		velocity_norm.first = velocity.first / norm;
		velocity_norm.second = velocity.second / norm;
		velocity.first = velocity_norm.first * (mower_speed_);
		velocity.second = velocity_norm.second * (mower_speed_);

		}
		else
		{
			velocity = { 0,0 };
		}
	}
	{
		std::pair<float, float> to_target;
		to_target.first = target_item_->rect_.x - rect_.x;
		to_target.second = target_item_->rect_.y - rect_.y;
		float norm = sqrt((to_target.first * to_target.first) + (to_target.second * to_target.second));
		to_target.first = to_target.first / norm;
		to_target.second = to_target.second / norm;

		if (norm <= 50)
		{
			velocity = { 0,0 };
		}
	}
	rect_.x += velocity.first;
	rect_.y += velocity.second;
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
	std::pair<float,float> to_target;
	to_target.first = target_item_->rect_.x - rect_.x;
	to_target.second = target_item_->rect_.y - rect_.y;
	float norm = sqrt((to_target.first * to_target.first) + (to_target.second * to_target.second));
	to_target.first = to_target.first / norm;
	to_target.second = to_target.second / norm;

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
		thisray.first = rays_[i].first + rect_.x + (rect_.w / 2);
		thisray.second = rays_[i].second + rect_.y + (rect_.h / 2);
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
			for (int j = 0; j < lenght; j++)
			{
				std::pair<int, int> p1 = { rect_.x + (rect_.w / 2), rect_.y + (rect_.h / 2) };
				std::pair<int, int> q1 = thisray;

				std::pair<int, int> p2 = points[j];
				std::pair<int, int> q2;
				if (j == lenght - 1)
				{
					q2 = points[0];
				}
				else
				{
					q2 = points[j+1];
				}
				int o1 = GetOrientation(p1, q1, p2);
				int o2 = GetOrientation(p1, q1, q2);
				int o3 = GetOrientation(p2, q2, p1);
				int o4 = GetOrientation(p2, q2, q1);
				if (o1 != o2 && o3 != o4) 
				{
					//y = mx + c
					//m = del_y/del_x

					std::pair<float, float> intersect;

					double a = q1.second - p1.second;
					double b = p1.first - q1.first;
					double c = a * (p1.first) + b * (p1.second);
					// Line CD represented as a2x + b2y = c2
					double a1 = q2.second - p2.second;
					double b1 = p2.first - q2.first;
					double c1 = a1 * (p2.first) + b1 * (p2.second);
					double det = a * b1 - a1 * b;

					intersect.first = (b1 * c - b * c1) / det;
					intersect.second = (a * c1 - a1 * c) / det;

					float norm = sqrt((intersect.first * intersect.first) + (intersect.second * intersect.second));

					danger[i] = norm;
					break;
				}
				else
				{
					danger[i] = 0;
				}
					
			}
		}
	}
	return danger;
}


int GetOrientation(std::pair<int, int> p, std::pair<int, int> q, std::pair<int, int> r)
{
	int val = (q.second - p.second) * (r.first - q.first) -
		(q.first - p.first) * (r.second - q.second);

	if (val == 0) return 0;  // collinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}
