#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <memory>
#include <vector>


#include "interfaces/iobjectmanager.h"

namespace Team {

using ObjectId = unsigned int;



class objectManager : public Course::iObjectManager
{
public:
    objectManager();

    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles contains the tiles to be added.
     */
    virtual void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    /**
     * @brief Returns a pointer to a Tile that has specified coordinate.
     * @param coordinate
     * @return
     * @post Exception Guarantee: Basic
     */
    virtual std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);

    /**
     * @brief Returns a pointer to a Tile that has specified ID
     * @param id
     * @return
     * @post Exception Guarantee: Basic
     */
    virtual std::shared_ptr<Course::TileBase> getTile(const ObjectId& id);

    /**
     * @brief Returns a vector of pointers to Tiles specified by Coordinates.
     * @param coordinates
     * @return
     * @post Exception Guarantee: Basic
     */
    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

private:

    std::vector<std::shared_ptr<Course::TileBase>> m_tiles;

};

}
#endif // OBJECTMANAGER_H
