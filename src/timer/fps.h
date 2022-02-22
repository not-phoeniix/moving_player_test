#pragma once

class fps_tool {
    public:
        fps_tool();

        int counted_frames;
        
        custom_timer fps_counter_timer, fps_cap_timer;

        float avg_fps();

        int avg_fps_int();

        void lock_fps(int ticks_per_frame);
};