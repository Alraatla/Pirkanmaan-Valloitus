#ifndef WATER_H
#define WATER_H

#include "tiles/tilebase.h"
#include "teamresourcemaps.h"

namespace Team {



class Water : public Course::TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;

    Water() = delete;

    Water(const Course::Coordinate& location,
             const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager,
             const unsigned int& max_build = 0,
             const unsigned int& max_work = 0,
             const Course::ResourceMap& production = Team::TeamConstResourceMaps::WATER_BP);

    virtual ~Water() = default;

    virtual std::string getType() const override;

}; // Class Water
} // namespace Team
#endif // WATER_H
