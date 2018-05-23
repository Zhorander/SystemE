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

#include <iostream>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "console.h"
#include "framework.h"

Console::Console (MessageBus *mbus) : super (mbus)
{
    start_system ();
    console_support = true;
}

void Console::inputListener ()
{
    const char *prompt = "se> ";
    char *line = NULL;
    print_logo ();

    while (msgBus->isRunning() && (line = readline(prompt))) {
        if (line && *line) {
            add_history (line);
            process_cmd (std::string(line));
        }
    }
}

void Console::process_cmd (std::string s)
{
    if (s == std::string("shutdown")) {
        printf ("shutting down engine...\n");
        msgBus->exit ();
    } else {
        int i;
        for (i = 0; i < nil_msg; i++) {
            if (s == this->cmd_list[i])
                break;
        }

        /* Msg *m = new Msg((msg_type)i, NULL); */
        /* msgBus->postMessage (m); */
    }
}

void Console::processMsg (Msg msg)
{
    std::cout << "Console:" << this->cmd_list[msg.getMsgType()] << "\n";
}

Console::~Console ()
{
    in_handler.join ();
    msg_handler.join ();
}

void Console::start_system ()
{
    in_handler = std::thread (&Console::inputListener, this);
    msg_handler  = std::thread (&System::messageHandler, this);
}

void Console::print_logo ()
{
    printf (" ______     __  __     ______     ______   ______     __    __        ______    \n");
    printf ("/\\  ___\\   /\\ \\_\\ \\   /\\  ___\\   /\\__  _\\ /\\  ___\\   /\\ \"-./  \\      /\\  ___\\   \n");
    printf ("\\ \\___  \\  \\ \\____ \\  \\ \\___  \\  \\/_/\\ \\/ \\ \\  __\\   \\ \\ \\-./\\ \\     \\ \\  __\\   \n");
    printf (" \\/\\_____\\  \\/\\_____\\  \\/\\_____\\    \\ \\_\\  \\ \\_____\\  \\ \\_\\ \\ \\_\\     \\ \\_____\\ \n");
    printf ("  \\/_____/   \\/_____/   \\/_____/     \\/_/   \\/_____/   \\/_/  \\/_/      \\/_____/ \n");
    printf ("                                                                                \n");

    printf("\n");
    printf ("     System E  Copyright (C) 2018  Elias Flores\n \
    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n \
    This is free software, and you are welcome to redistribute it\n \
    under certain conditions; type `show c' for details.\n");
    printf("\n");
}

