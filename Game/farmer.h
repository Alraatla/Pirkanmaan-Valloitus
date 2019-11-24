#ifndef FARMER_H
#define FARMER_H

#include "workers/basicworker.h"
#include "gameeventhandler.h"
#include "objectmanager.h"
#include "playerobject.h"
#include "teamresourcemaps.h"

namespace Team {


class Farmer : public Course::WorkerBase
{
public:
    Farmer() = delete;


    Farmer(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<ObjectManager>& objectmanager,
                const std::shared_ptr<PlayerObject>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& cost =
                    TeamConstResourceMaps::FARMER_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    TeamConstResourceMaps::FARMER_EFFICIENCY
                );

    virtual ~Farmer() = default;

    virtual std::string getType() const override;

    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;


    virtual void doSpecialAction() override;


    virtual const Course::ResourceMapDouble tileWorkAction() override;
};

} // namespace Team
#endif // FARMER_H
