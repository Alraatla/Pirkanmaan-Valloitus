#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <memory>
#include <vector>


#include "interfaces/iobjectmanager.h"

namespace Team {


class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager();



    virtual void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);


    virtual std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);


    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);


    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

private:

};

}
#endif // OBJECTMANAGER_H
