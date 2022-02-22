#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "timer/timer.h"
#include "player/player.h"
#include "timer/fps.h"

using namespace std;

SDL_Window *main_window = NULL;
SDL_Renderer *main_renderer = NULL;
SDL_Texture *bg_texture = NULL;
SDL_Texture *player_texture = NULL;

extern SDL_Rect floor_rect;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    main_window = SDL_CreateWindow("player_move", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
}

SDL_Texture *load_texture(string path) {
    SDL_Texture *final_texture = NULL;

    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if(loaded_surface == NULL) {
        cout << "image failed to load! error: " << SDL_Error << "\n";
    } else {
        final_texture = SDL_CreateTextureFromSurface(main_renderer, loaded_surface);

        SDL_FreeSurface(loaded_surface);
    }

    return final_texture;
}

void load_media() {
    bg_texture = load_texture("images/bg1.png");
    if(bg_texture == NULL) {
        cout << "bg_texture failed to load! error: " << SDL_GetError() << "\n";
    }

    player_texture = load_texture("images/player1.png");
    if(player_texture == NULL) {
        cout << "player_texture failed to load! error: " << SDL_GetError() << "\n";
    }
}

void clear_bg() {
    SDL_SetRenderDrawColor(main_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(main_renderer);
}

void end() {
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(main_window);

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    init();
    load_media();

    player main_player;
    fps_tool fps;
    custom_timer step_timer;

    fps.counted_frames = 0;
    fps.fps_counter_timer.start();

    SDL_Event e;
    bool running = true;
    while(running) {
        fps.fps_cap_timer.start();

        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }

        float time_step = step_timer.get_ticks() / 1000.f;

        //background resolution: 64 x 36
        clear_bg();

        SDL_RenderCopy(main_renderer, bg_texture, NULL, NULL);

        main_player.input();
        main_player.move(time_step, SCREEN_HEIGHT, SCREEN_WIDTH);
        main_player.render(main_renderer, player_texture);

        if(SCREEN_SHOW_COLLIDERS) {
            SDL_SetRenderDrawColor(main_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderDrawRect(main_renderer, &floor_rect);
            SDL_RenderDrawRect(main_renderer, &main_player.player_collider);
        }

        step_timer.start();

        SDL_RenderPresent(main_renderer);

        ++fps.counted_frames;

        cout << "current fps: " << fps.avg_fps() << "\n";

        fps.lock_fps(SCREEN_TICKS_PER_FRAME);
    }

    end();
}