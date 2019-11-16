#include "playerobject.h"

#include <algorithm>
#include "exceptions/keyerror.h"

namespace Team {


PlayerObject::PlayerObject(std::string name): Course::PlayerBase(name)
{
}


bool PlayerObject::modifyResource(Course::BasicResource, int amount)
{
    return true;
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
