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

        Msg *m = new Msg((msg_type)i, NULL);
        msgBus->postMessage (m);
    }
}

void Console::processMsg (Msg *msg)
{
    std::cout << this->cmd_list[msg->getMsgType()] << "\n";
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

}

