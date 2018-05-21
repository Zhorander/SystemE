//graphics.cpp

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
        while (win->isOpen() && win->pollEvent(&e)) {
            if (winObserver)
                winObserver->notify(e);
        }
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
