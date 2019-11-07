#include "gameeventhandler.h"
#include "mapwindow.hh"


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

std::shared_ptr<Team::PlayerObject> GameEventHandler::setPlayercount(int a)
{
    playercount_ = a;
    for (int x = 1; x <= a; ++x) {
        std::string name = "player";
        name += std::to_string(x);
        auto player = std::make_shared<Team::PlayerObject>(name);
        players_.push_back(player);
    }
    return players_.at(0);
}

}
