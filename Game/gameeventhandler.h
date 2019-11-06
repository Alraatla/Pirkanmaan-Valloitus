#include "interfaces/igameeventhandler.h"
#include "objectmanager.h"
#include "core/basicresources.h"

#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <iostream>


namespace Team {

class GameEventHandler : public Course::iGameEventHandler
{
public:
    GameEventHandler();


    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                    Course::BasicResource resource,
                                    int amount);

        /**
         * @brief Modify Player's resources. Can be used to both sum or subtract
         * @param player Pointer to the Player whose resources are being modified.
         * @param resources ResourceMap containing change amounts.
         * @return
         * True - Modification was succesful. \n
         * False - Modification failed. \n
         */
    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                     Course::ResourceMap resources);

    void initializeGame();
    void setPlayercount(int a);

private:
    std::shared_ptr<Course::iObjectManager> objectManager_ = nullptr;
    int playercount_ = 0;
    std::vector<std::shared_ptr<Course::PlayerBase>> players_;
};

}

#endif // GAMEEVENTHANDLER_H
