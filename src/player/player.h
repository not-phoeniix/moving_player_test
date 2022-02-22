#pragma once
#include "../main.h"

class player {
    public:
        const int BOX_SIZE = (SCREEN_WIDTH / SCREEN_PIX_WIDTH) * 4;
        const int PLAYER_VEL = 500;
        const int JUMP_SCALE = 40;
        const int GRAVITY_SCALE = 20;

        player();

        void update_collider();

        void input();

        void move(float time_step, int screen_height, int screen_width);

        void render(SDL_Renderer *renderer, SDL_Texture *texture);

        SDL_Rect player_collider;

    private:
        float pos_x, pos_y;

        float vel_x, vel_y;

        SDL_RendererFlip flip_type;

        bool on_ground;
};