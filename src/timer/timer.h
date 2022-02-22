#pragma once

class custom_timer {
    public:
        custom_timer();

        void start();
        void stop();
        void pause();
        void unpause();

        int get_ticks();

        bool is_started();
        bool is_paused();

    private:
        int start_ticks;
        int paused_ticks;

        bool paused;
        bool started;
};