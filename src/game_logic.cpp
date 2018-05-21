//game_logic.cpp

#include "game_logic.h"

GameLogic::GameLogic(Systems::MessageBus *mbus, std::string path) : super(mbus)
{
    sReader = new ScriptReader(path);
    start_system();
}

GameLogic::~GameLogic()
{
    if (sReader)
        delete sReader;

    msg_handler.join();
}

void GameLogic::start_system()
{
    msg_handler = std::thread(&System::messageHandler, this);
}

void GameLogic::processMsg(Msg *msg)
{
}

