#include "farmer.h"



namespace Team {


Farmer::Farmer(const std::shared_ptr<GameEventHandler>& eventhandler,
               const std::shared_ptr<ObjectManager>& objectmanager,
               const std::shared_ptr<PlayerObject>& owner,
               const int& tilespaces,
               const Course::ResourceMap& cost,
               const Course::ResourceMapDouble& efficiency):
    WorkerBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        cost,
        efficiency)
{
}


std::string Farmer::getType() const
{
    return "Farmer";
}

bool Farmer::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return target->getOwner() == getOwner() and
            Farmer::canBePlacedOnTile(target);
}

void Farmer::doSpecialAction()
{

}

const Course::ResourceMapDouble Farmer::tileWorkAction()
{
    auto player = getOwner();
    auto events = lockEventHandler();
    double satisfaction = 0;
    Course::BasicResource focus = getResourceFocus();

    Course::ResourceMapDouble final_modifier;

    if ( events->modifyResource(player, Course::FOOD, -1) )
    {
        satisfaction = 0.5;
        if ( events->modifyResource(player, Course::MONEY, -1) )
        {
            satisfaction = 1;
        }
    }


    if( focus != Course::NONE )
    {
        final_modifier[focus] =
                WORKER_EFFICIENCY.at(focus) * (satisfaction + 0.25);
    }
    else
    {
        for( auto it = WORKER_EFFICIENCY.begin();
             it != WORKER_EFFICIENCY.end();
             ++it )
        {
            final_modifier[it->first] = it->second * satisfaction;
        }
    }

    return final_modifier;
}


} // namespace Team
