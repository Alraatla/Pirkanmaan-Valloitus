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
    PlayerObject(std::string name);

    bool modifyResource(Course::BasicResource resource, int amount);

    Course::ResourceMapDouble getResources ();
    int getWorkerAmount(std::string workerType);
    int getPoints();
    void addPoints(int points);

    bool hasHQ();
private:
    Course::ResourceMapDouble resources_ = {{Course::MONEY, 500},
                                            {Course::FOOD, 300},
                                            {Course::WOOD, 800},
                                            {Course::STONE, 600},
                                            {Course::ORE, 637}};
    std::map<std::string, int> workersMap_ = {{"WORKERS", 0},
                                              {"FARMERS", 0},
                                              {"MINERS", 0}};

    unsigned int points_ = 0;

};
}
#endif // PLAYEROBJECT_H
