#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <memory>
#include <vector>


#include "interfaces/iobjectmanager.h"
#include "buildings/buildingbase.h"
#include "workers/workerbase.h"
#include "playerobject.h"
#include "core/gameobject.h"
#include "tiles/tilebase.h"


namespace Team {



class ObjectManager : public Course::iObjectManager


{
public:
    ObjectManager();


    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles contains the tiles to be added.
     */

    virtual void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);


    virtual std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);


    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);


    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

    std::vector<std::shared_ptr<Course::TileBase>> getTilesForMap();

    void addWorker(const std::shared_ptr<Course::WorkerBase>& worker);

    std::vector<std::shared_ptr<Course::WorkerBase> > getPlayersWorkers(const std::shared_ptr<Course::PlayerBase> player);


private:


    std::vector<std::shared_ptr<Course::TileBase>> tiles_ = {};
    std::vector<std::shared_ptr<Course::WorkerBase>> workers_ = {};
    std::map<std::shared_ptr<Course::PlayerBase>, std::vector<std::shared_ptr<Course::WorkerBase>>> workersByPlayer_ = {};
    std::map<Course::Coordinate, std::shared_ptr<Course::TileBase>> tilesMappedByCoordinate_ = {};

};

}
#endif // OBJECTMANAGER_H
