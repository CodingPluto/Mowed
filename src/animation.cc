#include "animation.h"

#include <SDL.h>
#include <render.h>
#include <math.h>
#include <filesystem>

animation::animation(std::string name)
{
  /*
    std::string path = "../assets/" + name + "/";
    int index_pointer = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string animation_path = (entry.path()).string();
        index_pointer += 1;
        for (const auto& animation_entry : std::filesystem::directory_iterator(animation_path)) {
            auto frame = LoadTextureEx(((animation_entry.path()).string()).c_str());
            std::pair<GLuint, GLuint> buffer;
            buffer.first = frame.first;
            buffer.second = LoadVerticesEx(300, 300, frame.second.first, frame.second.second);
            animations_[index_pointer].emplace_back(buffer); 
        }
    }
    */
}

std::pair<GLuint, GLuint> animation::GetFrame()
{
    int delta_time = SDL_GetTicks() - last_timestep_;
    int mspf = pow((animation_fps_ * 1000), -1);
    if (delta_time / mspf > 1) {
        animation_frame_.second += (delta_time / mspf);
        last_timestep_ = SDL_GetTicks();
    }
    if (state_que_.size() != 0) {
        if (animation_frame_.second == 0) {
            animation_frame_.first = state_que_.back();
            state_que_.pop_back();
        }
    }
    return animations_[animation_frame_.first][animation_frame_.second];
}

void animation::Setstate(int state)
{
    animation_frame_.first = state;
}

void animation::QueState(int state)
{
    state_que_.emplace_back(state);
}
