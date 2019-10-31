#include "gameeventhandler.h"

namespace Team {



gameEventHandler::gameEventHandler()
{

}



bool gameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount)
{
    return true;
}

bool gameEventHandler::modifyResources(
        std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources)
{
    return true;
}

}
