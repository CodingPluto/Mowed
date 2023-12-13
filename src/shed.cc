#include "shed.h"
#include <render.h>

Shed::Shed(int x, int y) : animation_("shed", x, y)
{
	rect_.w = animation_.width_;
	rect_.h = animation_.height_;
	rect_.x = x;
	rect_.y = y;
	vao_ = LoadVerticesEx(0, 0, animation_.width_, animation_.height_);
}

void Shed::Render()
{	
	auto vec = ScreenCoordinatesConvert(rect_.x, rect_.y);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, 0.0f));
	SetModel(model);
	GLuint frame_tex = animation_.GetFrame();
	glBindTexture(GL_TEXTURE_2D, frame_tex);
	RenderTexture(vao_, frame_tex);
	glBindVertexArray(0);
}
