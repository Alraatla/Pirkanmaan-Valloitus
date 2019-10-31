#include "objectmanager.h"

namespace Team {


objectManager::objectManager()
{

}

/*objectManager::~ObjectManager()
{

}
*/
void objectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{

}

std::shared_ptr<Course::TileBase> objectManager::getTile(const Course::Coordinate &coordinate)
{

}

std::shared_ptr<Course::TileBase> objectManager::getTile(const ObjectId &id)
{

}

std::vector<std::shared_ptr<Course::TileBase> > objectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{

}
}
