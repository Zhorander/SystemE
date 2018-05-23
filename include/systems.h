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

#include <iostream>
#include <list>
#include <thread>
#include <set>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <ostream>
#include <chrono>

#include "messages.h"

#ifdef __linux__
#include <unistd.h>

#elif _WIN32
#include <windows.h>
#else
//if the os isn't found we can't use system
//dependent utilities
#define NO_OS
#endif

#define NUM_SYSTEMS 32 //can be changed later if needed

namespace Systems {

    class MessageBus;
    class System;

    //---------System Utilities--------------------
    //IT IS EXTREMELY ADVISED THAT YOU DON'T USE THESE
    //FUNCTIONS IN NON-SYSTEMS

    void system_sleep (int millisec);

    //----------------------------------------------

    class MessageBus {
        public:
            MessageBus ();
            ~MessageBus ();

            void setCondVar (std::condition_variable *cv);
            void postMessage (Msg msg);
            void messageProcessor (); //thread that posts when there are available messages
            void addSystem (System *s);
            void exit ();
            bool isRunning ();
            void start_bus ();
        private:
            bool systems_running;    //continue running or exit gracefully
            //mutex for queue since threads are posting to it
            std::mutex qGuard;
            //thread safe queue
            std::priority_queue<Msg> queue;
            //must hold references to systems to be able to use overriden functions
            std::list<System *> systems;
            //continuously check for and send messages
            std::thread msg_poster;
            //notify the main thread to continue running
            void notify_main_thread ();
            //condition variable for the main thread
            std::condition_variable *main_cv;
    };

    class System {
        public:
            virtual ~System ();
            System (MessageBus *main_bus);

            void messageHandler (); //handler for recieving messages
            virtual void processMsg (Msg msg); //message processor
            void giveMessage (Msg msg); //hand a message off to the system
            virtual void start_system ();
            std::thread getMsgThread ();

        protected:
            //thread for handling messages
            std::thread msg_handler;
            //the message bus
            MessageBus *msgBus;

        private:
            //message queue
            std::priority_queue<Msg> queue;
            //mutex for pr queue
            std::mutex qGuard;
    };

};

