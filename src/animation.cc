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
        std::string animation_path = (entry.path()).string() + "/";
        std::vector<std::pair<GLuint, GLuint>> empty;
        animations_.emplace_back(empty);
        for (const auto& animation_entry : std::filesystem::directory_iterator(animation_path)) {
            auto frame = LoadTextureEx(((animation_entry.path()).string()).c_str());
            animations_[index_pointer].emplace_back(frame); 
        }
        index_pointer += 1;
    }
    */
}

std::pair<GLuint, GLuint> animation::GetFrame(int x, int y)
{
    int delta_time = SDL_GetTicks() - last_timestep_;
    if (delta_time != 0) { 
        int mspf = pow((animation_fps_ / 1000), -1);
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
    }
    std::pair dim = animations_[animation_frame_.first][animation_frame_.second].second;
    GLuint vao = LoadVerticesEx(x, y, dim.first, dim.second);
    GLuint texture = animations_[animation_frame_.first][animation_frame_.second].first;
    std::pair<GLuint, GLuint> out = { vao, texture };
    return out;
}

void animation::Setstate(int state)
{
    animation_frame_.first = state;
}

void animation::QueState(int state)
{
    state_que_.emplace_back(state);
}
