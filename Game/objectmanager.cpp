#include "objectmanager.h"

namespace Team {


ObjectManager::ObjectManager()
{

}



void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    tiles_ = tiles;
    for (std::shared_ptr<Course::TileBase> tile : tiles_) {
        tilesMappedByCoordinate_[tile->getCoordinate()] = tile;
    }
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    for(auto const& tiles: tilesMappedByCoordinate_) {
        if (tiles.first == coordinate) {
            return tiles.second;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    for (std::shared_ptr<Course::TileBase> tile: tiles_) {
        if (tile->ID == id) {
            return tile;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(
        const std::vector<Course::Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> tilesFound = {};
    for (Course::Coordinate coordinate : coordinates) {
        for (std::shared_ptr<Course::TileBase> tile : tiles_) {
            if(tile->getCoordinate() == coordinate) {
                tilesFound.push_back(tile);
            }
        }
    }
    return tilesFound;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTilesForMap()
{
    return tiles_;
}

void ObjectManager::addWorker(const std::shared_ptr<Course::WorkerBase> &worker)
{
    std::shared_ptr<Course::PlayerBase> player = worker->getOwner();
    if(workersByPlayer_.find(player) == workersByPlayer_.end())
    {
        std::vector<std::shared_ptr<Course::WorkerBase>> workerVector = {};
        workerVector.push_back(worker);
        workersByPlayer_[player] = workerVector;
    }
    else
    {
        workersByPlayer_.at(player).push_back(worker);
    }

    workers_.push_back(worker);
}

std::vector<std::shared_ptr<Course::WorkerBase>> ObjectManager::getPlayersWorkers(const std::shared_ptr<Course::PlayerBase> player)
{
    return workersByPlayer_.at(player);
}

} // namespace Team
