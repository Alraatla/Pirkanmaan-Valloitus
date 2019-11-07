#include "playerobject.h"

#include <algorithm>
#include "exceptions/keyerror.h"

namespace Team {


PlayerObject::PlayerObject(const std::string& name): Course::PlayerBase(name)
{
    setName(name);
}


bool PlayerObject::modifyResource(Course::BasicResource, int amount)
{
    return true;
}

Course::ResourceMapDouble PlayerObject::getResources()
{
    return resources_;
}
}
