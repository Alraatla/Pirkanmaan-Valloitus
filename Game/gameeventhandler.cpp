#include "gameeventhandler.h"
#include "mapwindow.hh"
#include "core/resourcemaps.h"


namespace Team {



GameEventHandler::GameEventHandler()
{

}



bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount)
{
    getPlayer(player->getName())->modifyResource(resource, amount);
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources)
{
    std::shared_ptr<Team::PlayerObject> tPlayer = getPlayer(player->getName());
    for (auto resource : resources) {
        tPlayer->modifyResource(resource.first, resource.second);
    }

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

std::vector<std::shared_ptr<PlayerObject> > GameEventHandler::getPlayers()
{
    return players_;
}

void GameEventHandler::addObjectToPlayer(std::shared_ptr<PlayerObject> player,
                                         std::string objectType) {
    if (objectType == "HeadQuarters") {
        player->addPoints(50);
        modifyResources(player, Course::ConstResourceMaps::HQ_BUILD_COST);
    }
}

std::shared_ptr<PlayerObject> GameEventHandler::getPlayer(std::string playerName)
{
    for (std::shared_ptr<PlayerObject> player: players_) {
        if (player->getName() == playerName) {
            return player;
        }
    }
}


}
