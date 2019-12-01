#include "gameeventhandler.h"
#include "mapwindow.hh"
#include "core/resourcemaps.h"
#include "teamresourcemaps.h"
#include "buildings/headquarters.h"


namespace Team {



GameEventHandler::GameEventHandler()
{

}



bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount)
{
    if((std::dynamic_pointer_cast<PlayerObject>(player))->modifyResource(resource, amount))
    {
        return true;
    }
    return false;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources)
{
    std::dynamic_pointer_cast<Team::PlayerObject>(player)->modifyResources(resources);
    return true;
}

void GameEventHandler::modifyResourcesAtTurnEnd(std::shared_ptr<PlayerObject> player)
{
    int workerAmount = player->getWorkerAmount("WORKERS");
    int farmerAmount = player->getWorkerAmount("FARMERS");
    int minerAmount = player->getWorkerAmount("MINERS");
    Course::ResourceMap resources = player->getResources();
    for(int i = 0; i < workerAmount; i++)
    {
        if(resources.at(Course::MONEY) > TeamConstResourceMaps::BW_ROUNDLY_COST.at(Course::MONEY) &&
                resources.at(Course::FOOD) > TeamConstResourceMaps::BW_ROUNDLY_COST.at(Course::FOOD))
        {
            player->modifyResources(makeNegative(TeamConstResourceMaps::BW_ROUNDLY_COST));
        }
        else
        {
            player->addPoints(-1);
        }
    }
    for(int i = 0; i < farmerAmount; i++)
    {
        if(resources.at(Course::MONEY) > TeamConstResourceMaps::FARMER_ROUNDLY_COST.at(Course::MONEY) &&
           resources.at(Course::FOOD) > TeamConstResourceMaps::FARMER_ROUNDLY_COST.at(Course::FOOD))
        {
            player->modifyResources(makeNegative(TeamConstResourceMaps::FARMER_ROUNDLY_COST));
        }
        else
        {
            player->addPoints(-2);
        }

    }
    for(int i = 0; i < minerAmount; i++)
    {
        if(resources.at(Course::MONEY) > TeamConstResourceMaps::MINER_ROUNDLY_COST.at(Course::MONEY) &&
           resources.at(Course::FOOD) > TeamConstResourceMaps::MINER_ROUNDLY_COST.at(Course::FOOD))
        {
            player->modifyResources(makeNegative(TeamConstResourceMaps::MINER_ROUNDLY_COST));
        }
        else
        {
            player->addPoints(-3);
        }
    }

    std::map<Course::Coordinate, std::shared_ptr<Course::TileBase> > ownedTiles = player->getOwnedTiles();
    for(std::pair<Course::Coordinate, std::shared_ptr<Course::TileBase>> dataPair: ownedTiles)
    {
        if(dataPair.second->getWorkerCount() == 1 && dataPair.second->getOwner() == player)
        {
            std::shared_ptr<Course::WorkerBase> worker = dataPair.second->getWorkers().at(0);
            if(worker->getType() == "BasicWorker")
            {
                player->modifyResources(makeNegative(TeamConstResourceMaps::BW_ROUNDLY_COST));
                player->addPoints(1);

            }
            else if(worker->getType() == "Farmer")
            {
                player->modifyResources(makeNegative(TeamConstResourceMaps::FARMER_ROUNDLY_COST));
                player->addPoints(2);

            }
            else if(worker->getType() == "Miner")
            {
                player->modifyResources(makeNegative(TeamConstResourceMaps::MINER_ROUNDLY_COST));
                player->addPoints(5);
            }
            dataPair.second->generateResources();
        }

    }

}

void GameEventHandler::setPlayercount(int playerCount, std::vector<std::string> names)
{
    playerCount_ = playerCount;
    // If any 2 given player names are the same, stockNames will be used
    std::vector<std::string> stockNames = {"Player1", "Player2", "Player3", "Player4"};
    bool needForStock = false;
    for (std::string name: names)
    {
        if(std::count(names.begin(), names.end(), name) != 1 || name == "")
        {
            needForStock = true;
        }
    }

    for (std::string name: names) {
        std::shared_ptr<PlayerObject> player = nullptr;
        if(needForStock) {
            player = std::make_shared<Team::PlayerObject>(stockNames.at(players_.size()));
        }
        else {
            player = std::make_shared<Team::PlayerObject>(name);
        }

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
        player->addPoints(1);
        modifyResources(player, makeNegative(Course::ConstResourceMaps::HQ_BUILD_COST));
    }
    else if (objectType == "Tyokkari")
    {
        player->addPoints(30);
        modifyResources(player, makeNegative(Team::TeamConstResourceMaps::TYOKKARI_BUILD_COST));
    }
    else if (objectType == "Farm")
    {
        player->addPoints(10);
        modifyResources(player, makeNegative(Course::ConstResourceMaps::FARM_BUILD_COST));
    }
    else if (objectType == "Mine")
    {
        player->addPoints(15);
        modifyResources(player, makeNegative(Team::TeamConstResourceMaps::MINE_BUILD_COST));
    }
    else if (objectType == "Outpost")
    {
        player->addPoints(5);
        modifyResources(player, makeNegative(Course::ConstResourceMaps::OUTPOST_BUILD_COST));
    }
    else if (objectType == "BasicWorker")
    {
        player->addPoints(1);
        modifyResources(player, makeNegative(Course::ConstResourceMaps::BW_RECRUITMENT_COST));
    }
    else if (objectType == "Farmer")
    {
        player->addPoints(5);
        modifyResources(player, makeNegative(TeamConstResourceMaps::FARMER_RECRUITMENT_COST));
    }
    else if (objectType == "Miner")
    {
        player->addPoints(7);
        modifyResources(player, makeNegative(TeamConstResourceMaps::FARMER_RECRUITMENT_COST));
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

Course::ResourceMap GameEventHandler::makeNegative(Course::ResourceMap resourceMap)
{
    Course::ResourceMap newMap = {};
    for (auto resource: resourceMap) {
        newMap[resource.first] = resource.second * (-1);
    }
    return newMap;
}


}
