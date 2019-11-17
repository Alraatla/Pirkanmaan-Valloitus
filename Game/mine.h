#ifndef MINE_H
#define MINE_H

#include "buildings/buildingbase.h"
#include "teamresourcemaps.h"

namespace Team {

class Mine : public Course::BuildingBase
{
public:
    Mine() = delete;

    explicit Mine(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Team::TeamConstResourceMaps::MINE_BUILD_COST,
            const Course::ResourceMap& production = Team::TeamConstResourceMaps::MINE_PRODUCTION);

    virtual ~Mine() = default;

    virtual std::string getType() const override;

};

} // namespace Team

#endif // MINE_H
