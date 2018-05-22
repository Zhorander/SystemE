/*
 *  System E is a general use 2D game engine mostly built for learning
 *  Copyright (C) 2018  Elias Flores
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  contact information: elias_50@live.com
 */

#include "input.h"

Input::Input (Systems::MessageBus *mbus)
    : super (mbus)
{
    start_system ();
    input_type = INPUT_ON;
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
