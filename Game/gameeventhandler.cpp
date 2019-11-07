#include "gameeventhandler.h"


namespace Team {



GameEventHandler::GameEventHandler()
{

}



bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount)
{
    return true;
}

bool GameEventHandler::modifyResources(
        std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources)
{
    return true;
}

void GameEventHandler::setPlayercount(int a)
{
    playercount_ = a;
    for (int x = 1; x <= a; ++x) {
        std::string name = "player";
        name += std::to_string(x);
        auto player = std::make_shared<Team::PlayerObject>(name);
        players_.push_back(player);
    }
}

}
