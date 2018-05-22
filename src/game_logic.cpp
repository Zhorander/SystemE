//game_logic.cpp

#include "game_logic.h"

/** assembleScriptReader
 * Factory method for creating an appropriate script reader for the given
 * script(i.e a lua reader for a lua script, a lily reader for a lily script)
 */
ScriptReader *GameLogic::assembleScriptReader(std::string path)
{
	std::string filename(path);
    std::string::size_type idx;

    idx = filename.rfind('.');

    if(idx != std::string::npos)
    {
        std::string extension = filename.substr(idx+1);

        if (extension == "lua")
            return new LuaReader(path);
#ifdef USING_LILY
        else if (extension == "lily")
            return new LilyReader(path);
        else if (extension == "lly")
            return new LilyReader(path);
#endif
    }

    return NULL;
}

GameLogic::GameLogic(Systems::MessageBus *mbus, std::string path) : super(mbus)
{
    sReader = assembleScriptReader(path);
    if (sReader == NULL) {
        std::cerr << "Error: unable to read script" << std::endl;
    } else {
        sReader->loadScript();
    }

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

