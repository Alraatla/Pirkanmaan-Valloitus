#include "gameeventhandler.h"
#include "mapwindow.hh"
#include "core/resourcemaps.h"
#include "teamresourcemaps.h"


namespace Team {



GameEventHandler::GameEventHandler()
{

}



bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount)
{
    if(getPlayer(player->getName())->modifyResource(resource, amount))
    {
        return true;
    }
    return false;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources)
{
    std::shared_ptr<Team::PlayerObject> tPlayer = getPlayer(player->getName());
    for (auto resource : resources) {
        if(!tPlayer->modifyResource(resource.first, resource.second))
        {
            return false;
        }

    }
    return true;
}

void GameEventHandler::setPlayercount(int playerCount, std::vector<std::string> names)
{
    playerCount_ = playerCount;
    for (std::string name: names) {
        auto player = std::make_shared<Team::PlayerObject>(name);
        players_.push_back(player);
    }
}

std::vector<std::shared_ptr<PlayerObject> > GameEventHandler::getPlayers()
{
    return players_;
}

void GameEventHandler::addObjectToPlayer(std::shared_ptr<PlayerObject> player,
                                         std::string objectType)
{
    if (objectType == "HeadQuarters")
    {
        player->addPoints(50);
        modifyResources(player, Course::ConstResourceMaps::HQ_BUILD_COST);
    }
    if (objectType == "Tyokkari")
    {
        player->addPoints(69);
        modifyResources(player, Team::TeamConstResourceMaps::TYOKKARI_BUILD_COST);
    }
}

std::shared_ptr<PlayerObject> GameEventHandler::getPlayer(std::string playerName)
{
    for (std::shared_ptr<PlayerObject> player: players_) {
        if (player->getName() == playerName) {
            return player;
        }
    }
    return nullptr;
}


}
