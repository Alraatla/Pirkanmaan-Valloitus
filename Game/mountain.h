#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "tiles/tilebase.h"
#include "teamresourcemaps.h"

namespace Team {



class Mountain : public Course::TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;

    Mountain() = delete;

    Mountain(const Course::Coordinate& location,
             const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager,
             const unsigned int& max_build = 2,
             const unsigned int& max_work = 1,
             const Course::ResourceMap& production = Team::TeamConstResourceMaps::MOUNTAIN_BP);

    virtual ~Mountain() = default;

    virtual std::string getType() const override;

}; // class Mountain

} // namespace Team


#endif // MOUNTAIN_H
