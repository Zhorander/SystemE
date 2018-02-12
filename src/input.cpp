#include "input.h"

Input::Input (Systems::MessageBus *mbus)
    : super (mbus)
{
    start_system ();
    input_type = INPUT_BY_CHAR;
    printf ("Input system starting...\n");
}

Input::~Input ()
{
    input_listener.join ();
    msg_handler.join ();
}

void Input::start_system ()
{
    input_listener = std::thread (&Input::inputListener, this);
    msg_handler  = std::thread (&System::messageHandler, this);
}

void Input::inputListener ()
{
    int *key = NULL;
    Msg *m = nullptr;
    char *str = NULL;

    while (msgBus->isRunning ()) {
        //send key if not blocked
        switch (input_type) {
            case INPUT_BY_CHAR:
                key = (int *)malloc (sizeof (char));
                *key = Framework::Input::poll_kb ();
                m = new Msg (kb_event, key);
                msgBus->postMessage (m);

                if (*key == 21 || *key == 'q') {
                    msgBus->exit ();
                }
                break;
            case INPUT_BY_STRING:
                str = Framework::Input::get_string ();
                m = new Msg (kb_event, str);
                msgBus->postMessage (m);
                break;
            default:
                break;
        }
    }
}

const char *Input::key_to_string (Framework::KB_Key k)
{
    using namespace Framework;

    switch (k) {
        case KB_DOWN: return "Down"; break;
        case KB_UP: return "Up"; break;
        case KB_LEFT: return "Left"; break;
        case KB_RIGHT: return "Right"; break;
        default:
            break;
    }

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
