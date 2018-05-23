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
#include "systems.h"
#include "console.h"
#include "input.h"
#include "graphics.h"
#include "game_logic.h"

/** main.cpp
 * Main entrance of the game engine
 * To Do:
 *   -command line interface
 *   -build an abstract factory to create subsystems
 *   -extend engine with a plugin interface
 *   -read a config file
 */

int main ()
{
    std::mutex mtx;
    std::condition_variable cv;

    /** Start the message bus
     */
    Systems::MessageBus mbus;
    mbus.setCondVar (&cv);

    /** Start the console subsystem
     * To Do:
     * make this into a graphical console
     */
    Console *c = new Console (&mbus);
    mbus.addSystem (c);

    /** Start the input subsystem
     * To Do:
     * turn input events into readable strings and send them to the
     * game logic
     */
    Input *in  = new Input (&mbus);
    mbus.addSystem (in);

    /** Start the object manager
     * To Do:
     * deprecate this subsystem and use refrence counted objects instead
     */
    /* ObjectManager *om = new ObjectManager (&mbus); */
    /* mbus.addSystem (om); */

    /** Start the graphics subsystem
     * To Do:
     * read from config file or script to determine window size and other
     * attributes
     */
    Graphics *grphcs = new Graphics (&mbus, 640, 640);
    mbus.addSystem (grphcs);

    //set the input subsystem to recieve input events from the winow
    grphcs->setInputHandler(in);

    /** Start the game logic
     * To Do:
     * make script reader more flexible
     * create modules
     */
    GameLogic *glogic = new GameLogic(&mbus, "test.lua");
    mbus.addSystem(glogic);

    std::unique_lock<std::mutex> lck(mtx);
    //pause thread until engine shuts down
    cv.wait (lck);

    return 0;
}
