/*systems.cpp*/

#include "systems.h"
#include <stdio.h>

// ---------------- Systems ---------------

using namespace Systems;

//--------System Utilities------------------

void Systems::system_sleep (int millisec)
{
    std::this_thread::sleep_for (std::chrono::milliseconds(millisec));
}

//----------------System-------------------

/** constructor
 *
 * @param main_bus the message bus
 * @param system the type identifier of the system (see Systems::sys_type)
 * */
System::System (MessageBus *main_bus)
{
    msgBus = main_bus;
}

System::~System ()
{
}

/** process queue of messages
 * */
void System::messageHandler ()
{
    while (msgBus->isRunning ()) {
        if (!queue.empty ()) {
            //lock queue to prevent seg fault
            std::lock_guard<std::mutex> lock(qGuard);

            while (!queue.empty ()) {
                Msg *m = queue.top ();
                queue.pop ();
                processMsg (m);
            }
        }

        system_sleep (40);
    }
}

void System::processMsg (Msg *msg)
{
}

void System::giveMessage (Msg *msg)
{
    std::lock_guard<std::mutex> lock(qGuard);

    queue.push (msg);
}

void System::start_system ()
{
    msg_handler = std::thread (&System::messageHandler, this);
}

//-----MSG-----
Msg::Msg (int t, void *val)
{
    message_type = t;
    value = val;
    p = normal; // if no priority given, treat a normal
}

Msg::Msg (int t, void *val, priority pr)
{
    message_type = t;
    value = val;
    p = pr;
}

Msg::~Msg ()
{
    if (value) {
        free (value);
        value = NULL;
    }
}

int Msg::getMsgType ()
{
    return message_type;
}

void *Msg::getValue ()
{
    return value;
}

//-----MessageBus-----
MessageBus::MessageBus ()
{
    systems_running = true;

    main_cv = NULL;

    start_bus ();
}

MessageBus::~MessageBus ()
{
    for(auto &sys : systems) {
        if (sys != NULL)
            delete (sys);
    }
    msg_poster.join ();
}

void MessageBus::exit ()
{
    systems_running = false;

    if (main_cv != NULL)
        main_cv->notify_all ();
}

void MessageBus::setCondVar (std::condition_variable *cv)
{
    main_cv = cv;
}

bool MessageBus::isRunning ()
{
    return systems_running;
}

void MessageBus::postMessage (Msg *msg)
{
    std::lock_guard<std::mutex> lock(qGuard);

    queue.push (msg);
}

void MessageBus::start_bus ()
{
    msg_poster = std::thread (&MessageBus::messageProcessor, this);
}

void MessageBus::messageProcessor ()
{
    while (isRunning ()) {
        if (!queue.empty ()) {
            std::lock_guard<std::mutex> lock(qGuard);

            while (!queue.empty ()) {
                Msg *msg = queue.top ();
                queue.pop ();

                for (auto &i : systems)
                    i->giveMessage (msg); //might need to be i.giveMessage()
            }
        }

        //sleep to alleviate stress on the cpu
        system_sleep (50);
    }
}

void MessageBus::addSystem (System *s)
{
    systems.push_back (s);
}

