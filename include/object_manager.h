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

#pragma once

#include "systems.h"

using namespace Systems;

typedef struct item_t {
    int age;    //age of item
    Msg *item; //reference to item
    item_t ();
    ~item_t ();
}item_t;

class ObjectManager : public Systems::System {
    public:
        ObjectManager (Systems::MessageBus *mbus);
        ~ObjectManager ();
        void start_system () override;
        void setLifeCycle (int lc); //set the amount of cycles an obj can live for (default: 3)
        void processMsg (Msg *msg) override;
        void startCycle (); //start a collection cycle, removing as necessary
    private:
        using Systems::System::System;
        typedef System super;
        std::list<item_t *> collection;
        std::thread cycle_thread;
        //mutex for collection
        std::mutex qGuard;
        void cycler ();
        int life_cycle;
};
