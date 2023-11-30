#include "animation.h"

#include <SDL.h>
#include <render.h>

animation::animation(std::string name)
{
    std::string path = "../assets/" + name + /;
    int index_pointer = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string animation_path = entry.path();
        index_pointer += 1;
        for (const auto& animation_entry : std::filesystem::directory_iterator(animation_path)) {
            auto frame = load_texture_ex(animation_entry.path());
            std::pair<GLuint, GLuint>(texture, vao)> buffer;
            buffer.first = frame.first;
            buffer.second = load_vertices_ex(300, 300, frame.second.first, frame.second.second);
            animation_[index_pointer].emplace_back(buffer); 
        }
    }
}

GLuint animation::GetFrame()
{

}

void animation::Setstate(int state)
{
}

