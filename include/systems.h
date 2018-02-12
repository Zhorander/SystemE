/*systems.h*/

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
    class Msg;

    enum priority {
        low = 0,
        normal,
        high
    };

    enum msg_types {
        kb_event = 0, //keyboard event
        js_event, //joystick event
        error,
        warning,
        quit,
        block_input,
        unblock_input,
        shutdown,
        pause_audio,
        resume_audio,
        stop_audio,
        play_audio,
        set_audio,
        nil_msg, //mark end of enum
    };

    //---------System Utilities--------------------
    //IT IS EXTREMELY ADVISED THAT YOU DON'T USE THESE
    //FUNCTIONS IN NON-SYSTEMS

    void system_sleep (int millisec);

    //----------------------------------------------

    class Msg {
        public:
            Msg (int t, void *val);
            Msg (int t, void *val, priority pr);
            ~Msg ();

            int getMsgType ();
            void *getValue ();

            //judge msg priority
            bool operator < (Msg *y)
            {
                return this->p < y->p;
            }

        private:
            int message_type;
            void *value;
            priority p;
    };

    class MessageBus {
        public:
            MessageBus ();
            ~MessageBus ();

            void setCondVar (std::condition_variable *cv);
            void postMessage (Msg *msg); //val may be NULL
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
            std::priority_queue<Msg *> queue;
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
            virtual void processMsg (Msg *msg); //message processor
            void giveMessage (Msg *msg); //hand a message off to the system
            virtual void start_system ();
            std::thread getMsgThread ();

        protected:
            //thread for handling messages
            std::thread msg_handler;
            //the message bus
            MessageBus *msgBus;

        private:
            //message queue
            std::priority_queue<Msg *> queue;
            //mutex for pr queue
            std::mutex qGuard;
    };

};

