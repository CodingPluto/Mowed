#include <item.h>
#include <render.h>

Item::Item(std::string name) : animation_(name, rect_.x, rect_.y)
{
	std::cout << "initilsed item " << name << std::endl;
	vao_ = LoadVerticesEx(rect_.x, rect_.y, animation_.width_, animation_.height_);
}

Item* Item::Get_Pointer()
{
	return this;
}

void Item::Render()
{	
	GLuint frame_tex = animation_.GetFrame();
	glBindTexture(GL_TEXTURE_2D, frame_tex);
	RenderTexture(vao_, frame_tex);
	glBindVertexArray(0);
}

void Item::update()
{
	vao_ = LoadVerticesEx(rect_.x, rect_.y, animation_.width_, animation_.height_);
}
