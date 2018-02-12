#include "framework.h"

using namespace Framework;

const window *Window::active_window = NULL;
const window *Window::backbuffer = NULL;

void Framework::init_framework ()
{
    window *win = new sf::RenderWindow(sf::VideoMode(200, 200), "Hello World!");

    Window::active_window = win;
    /* initscr (); */
    /* /1* raw (); *1/ */
    /* keypad (stdscr, TRUE); */
    /* Window::active_window = stdscr; */
    /* box (stdscr, 0, 0); */
}

void Framework::quit_framework ()
{
    if (Window::active_window) {
        delete Window::active_window;
    }
}


/*-------------INPUT------------------------*/

int Input::poll_kb ()
{
    return 0;
}

char *Input::get_string ()
{
    return NULL;
}

/*--------------WINDOW---------------------*/

window *Window::create_window (int height, int width, int startx, int starty)
{
    window *win = new window (sf::VideoMode(height, width), "hello world!");

    return win;
}

void Window::set_active_window (sf::RenderWindow *win)
{
    Window::active_window = win;
}

const window *Window::get_active_window ()
{
    return Window::active_window;
}

void Window::free_window (window *win)
{
    delete win;
}

void Window::clear_window ()
{
    ((window *)active_window)->clear ();
}

void Window::refresh_window ()
{
}

void Window::swap_buffers ()
{
    const window *tmp = active_window;

    active_window = backbuffer;
    backbuffer = tmp;
}

void Window::display_window ()
{
    clear_window ();
    swap_buffers ();
    ((window *)active_window)->display ();
}

void Window::clear_backbuffer ()
{
    ((window *)backbuffer)->clear ();
}

