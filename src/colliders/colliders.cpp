#include <iostream>
#include <SDL2/SDL.h>
#include "../main.h"

using namespace std;

int pix_x_coord(int w_offset) {
    int pixels_per_box = SCREEN_WIDTH / SCREEN_PIX_WIDTH;

    return w_offset * pixels_per_box;
}

int pix_y_coord(int h_offset) {
    int pixels_per_box = SCREEN_HEIGHT / SCREEN_PIX_HEIGHT;

    return h_offset * pixels_per_box;
}

SDL_Rect floor_rect = {
    .x = pix_x_coord(3),
    .y = pix_y_coord(32),
    .w = pix_x_coord(60),
    .h = pix_y_coord(3)
};

SDL_Rect left_edge_rect = {
    .x = 0,
    .y = 0,
    .w = pix_x_coord(1),
    .h = SCREEN_HEIGHT
};

SDL_Rect right_edge_rect = {
    .x = pix_x_coord(63),
    .y = 0,
    .w = pix_x_coord(1),
    .h = SCREEN_HEIGHT
};

SDL_Rect top_edge_rect = {
    .x = 0,
    .y = 0,
    .w = SCREEN_WIDTH,
    .h = pix_y_coord(1)
};

SDL_Rect bottom_edge_rect = {
    .x = 0,
    .y = pix_y_coord(35),
    .w = SCREEN_WIDTH,
    .h = pix_y_coord(1)
};