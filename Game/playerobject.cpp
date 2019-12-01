#include "playerobject.h"

#include <algorithm>
#include <QDebug>
#include "exceptions/keyerror.h"

namespace Team {


PlayerObject::PlayerObject(std::string name): Course::PlayerBase(name)
{
}


bool PlayerObject::modifyResource(Course::BasicResource resource, int amount)
{
    if(resources_.at(resource) + amount >= 0)
    {
        resources_.at(resource) += amount;
        return true;
    }
    else
    {
        return false;
    }

}

bool PlayerObject::modifyResources(Course::ResourceMap resources, bool addition)
{
    if (addition) {
        resources_ = Course::mergeResourceMaps(resources_, resources);
        return true;
    }
    return false;
}

Course::ResourceMap PlayerObject::getResources()
{
    return resources_;
}

int PlayerObject::getWorkerAmount(std::string workerType)
{
    return workersMap_[workerType];
}

int PlayerObject::getPoints()
{
    return points_;
}

std::map<Course::Coordinate, std::shared_ptr<Course::TileBase> > PlayerObject::getOwnedTiles()
{
    return ownedTiles_;
}

void PlayerObject::addPoints(int points)
{
    points_ += points;
}

void PlayerObject::addOwnedTiles(Course::Coordinate coordinate,
                                 int amount, std::pair<int,
                                 int> mapSize,
                                 std::shared_ptr<Course::iObjectManager> objMan)
{
    int x = coordinate.x();
    int y = coordinate.y();
    std::pair<int, int> x_limits = {x - amount, x + amount};
    std::pair<int, int> y_limits = {y - amount, y + amount};
    mapSize.first--;
    mapSize.second--;

    if(x_limits.first < 0) {
        x_limits.first = 0;
    }
    if(x_limits.second > mapSize.first) {
        x_limits.second = mapSize.first;
    }
    if(y_limits.first < 0) {
        y_limits.first = 0;
    }
    if(y_limits.second > mapSize.second) {
        y_limits.second = mapSize.second;
    }

    for (int x = x_limits.first; x<= x_limits.second; x++) {
        for (int y = y_limits.first; y<= y_limits.second; y++) {
            Course::Coordinate coordinate = Course::Coordinate(x, y);
            ownedTiles_[coordinate] = objMan->getTile(coordinate);
        }
    }
}

void PlayerObject::addWorker(std::string workerType)
{
    workersMap_[workerType]++;
}

std::shared_ptr<Course::WorkerBase> PlayerObject::getWorker(std::string workerType,
                                                            std::vector<std::shared_ptr<Course::WorkerBase>> workers)
{

    for(std::shared_ptr<Course::WorkerBase> worker : workers)
    {
        if(worker->getType() == workerType && worker->getCoordinatePtr() == nullptr)
        {
            return worker;
        }
    }


    return nullptr;
}

void PlayerObject::workerAssigned(std::string workerType)
{
    workersMap_[workerType]--;
}

bool PlayerObject::hasHQ()
{
    for(std::shared_ptr<Course::GameObject> object: getObjects()) {
        if (object->getType() == "HeadQuarters") {
            return true;
        }
    }
    return false;
}

bool PlayerObject::hasTyokkari()
{
    for(std::shared_ptr<Course::GameObject> object: getObjects()) {
        if (object->getType() == "Tyokkari") {
            return true;
        }
    }
    return false;
}

bool PlayerObject::isTileOwned(Course::Coordinate coordinate)
{
    if(ownedTiles_.find(coordinate) != ownedTiles_.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool PlayerObject::hasEnoughResourcesFor(Course::ResourceMap building_cost)
{
    for(std::pair<Course::BasicResource, int> cost : building_cost) {

        if (resources_.at(cost.first) < cost.second) {
            return false;
        }
    }
    return true;
}
}
