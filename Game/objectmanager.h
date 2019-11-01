#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <memory>
#include <vector>


#include "interfaces/iobjectmanager.h"

namespace Team {

<<<<<<< HEAD
using ObjectId = unsigned int;



class objectManager : public Course::iObjectManager
=======

class ObjectManager : public Course::iObjectManager
>>>>>>> test
{
public:
    ObjectManager();


<<<<<<< HEAD
    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles contains the tiles to be added.
     */
=======

>>>>>>> test
    virtual void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);


    virtual std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);


    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);


    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

private:
<<<<<<< HEAD

    std::vector<std::shared_ptr<Course::TileBase>> m_tiles;
=======
>>>>>>> test

};

}
#endif // OBJECTMANAGER_H
