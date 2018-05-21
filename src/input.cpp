//input.cpp

#include "input.h"

Input::Input (Systems::MessageBus *mbus)
    : super (mbus)
{
    start_system ();
    input_type = INPUT_ON;
    printf ("Input system starting...\n");
}

Input::~Input ()
{
    msg_handler.join ();
}

void Input::start_system ()
{
    msg_handler  = std::thread (&System::messageHandler, this);
}

void Input::notify(Framework::event e)
{
    /* Msg *m = nullptr; */
    /* char *str = NULL; */

    //send key if not blocked
    switch (e.type) {
        case sf::Event::KeyPressed:
            printf ("A key was pressed\n\r");
            break;
        case sf::Event::KeyReleased:
            printf ("The key was released\n\r");
            break;
        case sf::Event::MouseButtonPressed:
            printf ("Mouse Button Pressed\n\r");
            break;
        case sf::Event::Closed:
            printf ("Window requested to be closed\n");
            break;
        default:
            break;
    }
}

const char *Input::key_to_string ()
{
    // int k = 1;

    // switch (k) {
    //     case KB_DOWN: return "Down"; break;
    //     case KB_UP: return "Up"; break;
    //     case KB_LEFT: return "Left"; break;
    //     case KB_RIGHT: return "Right"; break;
    //     default:
    //         break;
    // }

    return "Other";
}

void Input::blockInput ()
{
    input_type = INPUT_OFF;
}

bool Input::isBlocked ()
{
    return !input_type;
}
