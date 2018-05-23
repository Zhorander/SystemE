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
                Msg m = queue.top ();
                queue.pop ();
                processMsg (m);
            }
        }

        system_sleep (40);
    }
}

void System::processMsg (Msg msg)
{
}

void System::giveMessage (Msg msg)
{
    std::lock_guard<std::mutex> lock(qGuard);

    queue.push (msg);
}

void System::start_system ()
{
    msg_handler = std::thread (&System::messageHandler, this);
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

void MessageBus::postMessage (Msg msg)
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
                Msg msg = queue.top ();
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

