#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/gameobject.h"
#include <map>
#include <string>

namespace Team {



class PlayerObject : public Course::PlayerBase
{
public:
    PlayerObject(const std::string& name);

    bool modifyResource(Course::BasicResource, int amount);

    Course::ResourceMapDouble getResources ();
private:
    std::string m_name = "";
    std::vector<std::weak_ptr<Course::GameObject> > p_objects;
    Course::ResourceMapDouble resources_ = {{Course::MONEY, 500},
                                            {Course::FOOD, 300},
                                            {Course::WOOD, 800},
                                            {Course::STONE, 600},
                                            {Course::ORE, 637}};

};
}
#endif // PLAYEROBJECT_H
