#include <item.h>
#include <render.h>
#include <Shader.h>

Item::Item(std::string name) : animation_(name, rect_.x, rect_.y)
{
	std::cout << "initilsed item " << name << std::endl;
	vao_ = LoadVerticesEx(0, 0, animation_.width_, animation_.height_);
}

Item* Item::Get_Pointer()
{
	return this;
}

void Item::Render()
{	
  auto vec = ScreenCoordinatesConvert(rect_.x, rect_.y);
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(vec.x, vec.y, 0.0f));
  SetModel(model);
  //glUniformMatrix4fv(glGetUniformLocation(Shader::shader_program->program, "model"), 1, GL_FALSE, glm::value_ptr(model));

	GLuint frame_tex = animation_.GetFrame();
	glBindTexture(GL_TEXTURE_2D, frame_tex);
	RenderTexture(vao_, frame_tex);
	glBindVertexArray(0);

}

void Item::update()
{
	
 }
