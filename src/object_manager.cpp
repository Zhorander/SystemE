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

#include <object_manager.h>

item_t::item_t ()
{
    item = NULL;
}

item_t::~item_t ()
{
    if (item != NULL && item != nullptr) {
        delete item;
        item = NULL;
    }
}

ObjectManager::ObjectManager (Systems::MessageBus *mbus)
    : super (mbus)
{
    start_system ();
    life_cycle = 3;
}

ObjectManager::~ObjectManager ()
{
    std::lock_guard<std::mutex> lock(qGuard);

    std::list<item_t *>::iterator it = collection.begin();
    for (; it != collection.end(); it++) {
        std::list<item_t *>::iterator tmp;
        tmp = collection.erase (it);
        delete *it;
        it = tmp;
    }

    msg_handler.join ();
    cycle_thread.join ();
}

void ObjectManager::processMsg (Msg *msg)
{
    std::lock_guard<std::mutex> lock(qGuard);

    item_t *temp = new item_t();
    temp->age = 0;
    temp->item = msg;
    collection.push_back (temp);
}

void ObjectManager::start_system ()
{
    msg_handler = std::thread (&System::messageHandler, this);
    cycle_thread = std::thread (&ObjectManager::cycler, this);
}

void ObjectManager::startCycle ()
{
    //lock collection while we process its cycle
    std::lock_guard<std::mutex> lock(qGuard);

    std::list<item_t *>::iterator it = collection.begin ();

    for (; it != collection.end(); it++) {
        if ((*it)->age > life_cycle) {
            std::list<item_t *>::iterator tmp;
            tmp = collection.erase (it);
            delete *it;
            it = tmp;
        } else {
            (*it)->age++;
        }
    }
}

void ObjectManager::cycler ()
{
    while (msgBus->isRunning()) {
        startCycle ();
        system_sleep (1000); //each cycle will last 1 second
    }
}

