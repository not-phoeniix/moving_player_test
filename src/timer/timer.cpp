#include <iostream>
#include <SDL2/SDL.h>
#include "timer.h"

using namespace std;

custom_timer::custom_timer() {
    start_ticks = 0;
    paused_ticks = 0;

    started = false;
    paused = false;
}

void custom_timer::start() {
    started = true;
    paused = false;

    start_ticks = SDL_GetTicks();
    paused_ticks = 0;
}

void custom_timer::stop() {
    started = false;
    paused = false;

    start_ticks = 0;
    paused_ticks = 0;
}

void custom_timer::pause() {
    if(started && !paused) {
        paused = true;

        paused_ticks = SDL_GetTicks() - start_ticks;
        start_ticks = 0;
    }
}

void custom_timer::unpause() {
    if(started && paused) {
        paused = false;

        start_ticks = SDL_GetTicks() - paused_ticks;
        paused_ticks = 0;
    }
}

int custom_timer::get_ticks() {
    int time = 0;

    if(started) {
        if(paused) {
            time = paused_ticks;
        } else {
            time = SDL_GetTicks() - start_ticks;
        }
    }

    return time;
}

bool custom_timer::is_started() {
    return started;
}

bool custom_timer::is_paused() {
    return paused && started;
}