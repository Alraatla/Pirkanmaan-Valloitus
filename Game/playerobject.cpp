#include "playerobject.h"

#include <algorithm>
#include "exceptions/keyerror.h"

namespace Team {


PlayerObject::PlayerObject(std::string name): Course::PlayerBase(name)
{
}


bool PlayerObject::modifyResource(Course::BasicResource resource, int amount)
{
    resources_[resource] += amount;
}

Course::ResourceMapDouble PlayerObject::getResources()
{
    return resources_;
}

int PlayerObject::getWorkerAmount(std::string workerType)
{
    return workersMap_[workerType];
}

int PlayerObject::getPoints()
{
    return points_;
}

void PlayerObject::addPoints(int points)
{
    points_ += points;
}

bool PlayerObject::hasHQ()
{
    for(std::shared_ptr<Course::GameObject> object: getObjects()) {
        if (object->getType() == "HeadQuarters") {
            return true;
        }
    }
    return false;
}
}
