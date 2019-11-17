#ifndef TYOKKARI_H
#define TYOKKARI_H

#include "buildings/buildingbase.h"
#include "teamresourcemaps.h"

namespace Team {


class Tyokkari : public Course::BuildingBase
{
public:
    Tyokkari() = delete;

    explicit Tyokkari(
            const std::shared_ptr<Course::iGameEventHandler>& eventjandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Team::TeamConstResourceMaps::TYOKKARI_BUILD_COST,
            const Course::ResourceMap& production = Team::TeamConstResourceMaps::TYOKKARI_PRODUCTION);

    virtual ~Tyokkari() = default;

    virtual std::string getType() const override;


}; // class Tyokkari

} // namespace Team

#endif // TYOKKARI_H
