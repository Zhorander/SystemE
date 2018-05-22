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

#include "graphics.h"

Graphics::Graphics(Systems::MessageBus *mbus, int height, int width)
 : super(mbus)
{
    win = new Framework::Window(height, width, "System E");
    start_system();
}

Graphics::~Graphics()
{
    win->closeWindow();

    msg_handler.join();
    event_poller.join();
}

void Graphics::setInputHandler(Framework::WindowObserver *wo)
{
    winObserver = wo;
}

void Graphics::eventHandler()
{
    Framework::event e;

    while (msgBus->isRunning()) {
        if (win->isOpen() && win->pollEvent(&e)) {
            if (winObserver)
                winObserver->notify(e);
        }

        Systems::system_sleep(10);
    }
}

void Graphics::processMsg(Msg *msg)
{

}

void Graphics::start_system()
{
    msg_handler = std::thread(&System::messageHandler, this);
    event_poller = std::thread(&Graphics::eventHandler, this);
}
