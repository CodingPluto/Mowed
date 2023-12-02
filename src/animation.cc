#include "animation.h"

#include <SDL.h>
#include <render.h>
#include <math.h>
#include <filesystem>

animation::animation(std::string name)
{
    std::string path = name + "/";
    int index_pointer = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string animation_path = (entry.path()).string() + "/";
        std::vector<std::pair<GLuint, std::pair<int, int>>> empty;
        animations_.emplace_back(empty);
        
        for (const auto& animation_entry : std::filesystem::directory_iterator(animation_path)) {
            auto frame = LoadTextureEx(((animation_entry.path()).string()).c_str());
            animations_[index_pointer].emplace_back(frame); 
        }
        index_pointer += 1;
    }
}

std::pair<GLuint, GLuint> animation::GetFrame(int x, int y)
{
    int ticks = (int) SDL_GetTicks64();
    int delta_time = ticks - last_timestep_;
    if (delta_time != 0) { 
        int mspf = std::pow(((float)animation_fps_ / 1000), -1);
        int step = delta_time / mspf;
        if (step >= 1) {
            last_timestep_ = SDL_GetTicks();
            animation_frame_.second += step;
            if (animation_frame_.second > (animations_[animation_frame_.first].size()) - 1) {
                animation_frame_.second = 0;
            }

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
