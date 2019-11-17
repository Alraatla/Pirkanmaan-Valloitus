#include "tyokkari.h"

namespace Team {

Tyokkari::Tyokkari(
        const std::shared_ptr<Course::iGameEventHandler> &eventjandler,
        const std::shared_ptr<Course::iObjectManager> &objectmanager,
        const std::shared_ptr<Course::PlayerBase> &owner,
        const int &tilespaces,
        const Course::ResourceMap &buildcost,
        const Course::ResourceMap &production):
    Course::BuildingBase(
        eventjandler,
        objectmanager,
        owner,
        tilespaces,
        buildcost,
        production){}

std::string Tyokkari::getType() const
{
    return "Tyokkari";
}



} // namespace Team
