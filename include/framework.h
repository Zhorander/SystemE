//framework.c

#pragma once

#include <SFML/Graphics.hpp>
//#include "json.hpp"

namespace Framework {

    //Key press surfaces constants
    enum KB_Key {
        KB_NULL,
        KB_UP,
        KB_DOWN,
        KB_LEFT,
        KB_RIGHT,
        KB_CHAR
    };

    enum JoyStickEvents {
        DPAD_UP,
        DPAD_DOWN,
        DPAD_LEFT,
        DPAD_RIGHT
    };


    void init_framework ();
    void quit_framework ();

    typedef sf::RenderWindow window;

    namespace Input {
        int poll_kb ();
        char *get_string ();
        /* JoyStickEvents poll_js (); */
    };

    namespace Window {
        extern const window *active_window;
        extern const window *backbuffer;

        void set_active_window (window *win);
        const window *get_active_window ();
        window *create_window (int height, int width, int startx, int starty);
        void free_window (window *win);
        void print (const char *msg);
        void quit ();
        void refresh_window ();
        void clear_window ();
        void clear_window ();
        /**display_window
         *
         * clears the active window,
         * swaps with the backbuffer,
         * and draws it the screen
         * */
        void display_window ();
        void swap_buffers ();
        void clear_backbuffer ();
        /* void change_window (); */
    };

    namespace Sound {
        void play_sound ();
    };

    namespace Utilities {
    };
};
