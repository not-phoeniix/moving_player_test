#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include "timer.h"
#include "fps.h"

using namespace std;

fps_tool::fps_tool() {
    int counted_frames = 0;

    custom_timer fps_counter_timer, fps_cap_timer;
}

float fps_tool::avg_fps() {
    float fps = counted_frames / (fps_counter_timer.get_ticks() / 1000.f);

    if(fps > 2000000) {
        fps = 0;
    }

    return fps;
}

int fps_tool::avg_fps_int() {
    return (int)fps_tool::avg_fps();
}

void fps_tool::lock_fps(int ticks_per_frame) {
    if(fps_cap_timer.get_ticks() < ticks_per_frame) {
        SDL_Delay(ticks_per_frame - fps_cap_timer.get_ticks());
    }
}