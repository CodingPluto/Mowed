#include <item.h>
#include <render.h>
#include <Shader.h>

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
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(ScreenCoordinatesConvert(0,0)));
  glUniformMatrix4fv(glGetUniformLocation(Shader::shader_program->program, "model"), 1, GL_FALSE, glm::value_ptr(model));

	GLuint frame_tex = animation_.GetFrame();
	glBindTexture(GL_TEXTURE_2D, frame_tex);
	RenderTexture(vao_, frame_tex);
	glBindVertexArray(0);

}

void Item::update()
{
  float x = 1000;// 1095
  float y = 1000;// 890
  // 890 - 845 = 45
  // 1095 - 1080 = 15
  /*
  * Screen Dimensions:
  * WIDTH: 1095
  * HEIGHT: 890
  * startX: 295
  */
  
  //glm::mat4 player_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));

 }
