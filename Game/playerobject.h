#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/gameobject.h"
#include "core/coordinate.h"
#include "tiles/tilebase.h"
#include "objectmanager.h"
#include <map>
#include <string>
#include <iostream>

namespace Team {



class PlayerObject : public Course::PlayerBase
{
public:
    PlayerObject(std::string name);

    bool modifyResource(Course::BasicResource resource, int amount);
    bool modifyResources(Course::ResourceMap resources, bool addition = true);

    Course::ResourceMap getResources ();
    int getWorkerAmount(std::string workerType);
    int getPoints();
    std::map<Course::Coordinate, std::shared_ptr<Course::TileBase>> getOwnedTiles();
    void addPoints(int points);
    void addOwnedTiles(Course::Coordinate coordinate, int amount,
                       std::pair<int, int> mapSize,
                       std::shared_ptr<Course::iObjectManager> objMan);
    void addWorker(std::string workerType);

    std::shared_ptr<Course::WorkerBase> getWorker(std::string workerType, std::vector<std::shared_ptr<Course::WorkerBase> > workers);
    void workerAssigned(std::string workerType);

    bool hasHQ();
    bool hasTyokkari();
    bool isTileOwned(Course::Coordinate coordinate);

    bool hasEnoughResourcesFor(Course::ResourceMap building_cost);
private:
    Course::ResourceMap resources_ =        {{Course::MONEY, 2500},
                                            {Course::FOOD, 3000},
                                            {Course::WOOD, 2000},
                                            {Course::STONE, 1000},
                                            {Course::ORE, 0}};
    std::map<std::string, int> workersMap_ = {{"WORKERS", 0},
                                              {"FARMERS", 0},
                                              {"MINERS", 0}};

    unsigned int points_ = 0;

    std::map<Course::Coordinate, std::shared_ptr<Course::TileBase>> ownedTiles_ = {};

};
}
#endif // PLAYEROBJECT_H
