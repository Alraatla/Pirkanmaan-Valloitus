#include "interfaces/igameeventhandler.h"
#include "objectmanager.h"
#include "core/basicresources.h"
#include "core/playerbase.h"
#include "playerobject.h"
#include "mapwindow.hh"

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
    void setPlayercount(int playerCount, std::vector<std::string> names);
    std::vector<std::shared_ptr<Team::PlayerObject>> getPlayers();
    void addObjectToPlayer(std::shared_ptr<Team::PlayerObject> player, std::string objectType);
    std::shared_ptr<PlayerObject> getPlayer(std::string playerName);

private:
    std::shared_ptr<Course::iObjectManager> objectManager_ = nullptr;
    int playerCount_ = 0;
    std::vector<std::shared_ptr<Team::PlayerObject>> players_;
};

}

#endif // GAMEEVENTHANDLER_H
