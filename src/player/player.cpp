#include <iostream>
#include <SDL2/SDL.h>
#include "player.h"
#include "../colliders/colliders.h"
#include "../main.h"

using namespace std;

extern SDL_Rect floor_rect;

player::player() {
    pos_x = 0;
    pos_y = 0;

    vel_x = 0;
    vel_y = 0;

    flip_type = SDL_FLIP_NONE;

    on_ground = false;
}

void player::input() {
    const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
    
    //right and left movement
    if(keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D]) {
        vel_x = PLAYER_VEL;
        flip_type = SDL_FLIP_NONE;
    } else if(keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A]) {
        vel_x = -PLAYER_VEL;
        flip_type = SDL_FLIP_HORIZONTAL;
    } else {
        vel_x = 0;
    }

    //jump
    if(keyboard_state[SDL_SCANCODE_SPACE] || keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W]) {
        if(on_ground) {
            vel_y = -GRAVITY_SCALE * JUMP_SCALE;
            on_ground = false;
        }
    }
}

void player::move(float time_step, int screen_height, int screen_width) {
    pos_x += vel_x * time_step;
    
    if(pos_x < 0){
        vel_x = 0;
        pos_x = 0;
    } else if(pos_x + BOX_SIZE > screen_width) {
        vel_x = 0;
        pos_x = screen_width - BOX_SIZE;
    }

    vel_y += GRAVITY_SCALE;
    pos_y += vel_y * time_step;

    if(SDL_HasIntersection(&player_collider, &floor_rect)) {
        vel_y = 0;
        pos_y = floor_rect.y - BOX_SIZE;
        on_ground = true;
    }

    /*
    if(pos_y < 0) {
        vel_y = 0;
        pos_y = 0;
    } else if(pos_y + BOX_SIZE > screen_height) {
        vel_y = 0;
        pos_y = screen_height - BOX_SIZE;
        on_ground = true;
    }
    */
}

void player::render(SDL_Renderer *renderer, SDL_Texture *texture) {
    player_collider = {
        .x = (int)pos_x,
        .y = (int)pos_y,
        .w = BOX_SIZE,
        .h = BOX_SIZE
    };

    SDL_RenderCopyEx(renderer, texture, NULL, &player_collider, 0, NULL, flip_type);
}