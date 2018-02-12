//object_manager.h

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
        void processMsg (Systems::Msg *msg) override;
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
