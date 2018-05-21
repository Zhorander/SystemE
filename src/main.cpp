#include <iostream>
#include "systems.h"
#include "console.h"
#include "input.h"
#include "graphics.h"
#include "object_manager.h"

int main ()
{
    std::mutex mtx;
    std::condition_variable cv;

    std::cout << "starting message bus...\n";

    Systems::MessageBus mbus;
    mbus.setCondVar (&cv);

    std::cout << "starting system(s)...\n";

    Console *c = new Console (&mbus);
    mbus.addSystem (c);

    Input *in  = new Input (&mbus);
    mbus.addSystem (in);

    ObjectManager *om = new ObjectManager (&mbus);
    mbus.addSystem (om);

    Graphics *grphcs = new Graphics (&mbus, 640, 640);
    mbus.addSystem (grphcs);

    grphcs->setInputHandler(in);

    /* for (int i = 0; i < 100; i++) { */
    /*     mbus.postMessage (new Msg(kb_event, NULL)); */
    /* } */

    std::unique_lock<std::mutex> lck(mtx);

    cv.wait (lck);

    return 0;
}
