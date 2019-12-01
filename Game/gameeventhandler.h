
#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H


#include "interfaces/igameeventhandler.h"
#include "objectmanager.h"
#include "core/basicresources.h"
#include "core/playerbase.h"
#include "playerobject.h"

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <utility>


namespace Team {

class GameEventHandler : public Course::iGameEventHandler
{
public:
    GameEventHandler();

    /**
     * @brief Modify Player's resource. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resource what resource is to be modified.
     * @param amount the amount to be changed
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
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
    /**
     * @brief Modifies players resources at turn end and gives or deducts points
     * @param player Pointer to the player whos resources are being modified
     */
    void modifyResourcesAtTurnEnd(std::shared_ptr<Team::PlayerObject> player);

    /**
     * @brief Sets player count and names for players.
     * @param playerCount How many players there are
     * @param names Names of players, if any 2 given names are the same, stockNames
     *        will be used
     */
    void setPlayercount(int playerCount, std::vector<std::string> names);

    std::vector<std::shared_ptr<Team::PlayerObject>> getPlayers();

    /**
     * @brief addObjectToPlayer adds points for player depending on
     * the type of the object
     * @param player Pointer to player object
     * @param objectType type of the object
     */
    void addObjectToPlayer(std::shared_ptr<Team::PlayerObject> player, std::string objectType);
    std::shared_ptr<PlayerObject> getPlayer(std::string playerName);

    /**
     * @brief makeNegative multiplies given resource map with -1
     * @param resourceMap
     * @return the flipped map
     */
    Course::ResourceMap makeNegative(Course::ResourceMap resourceMap);

private:
    std::shared_ptr<Course::iObjectManager> objectManager_ = nullptr;
    int playerCount_ = 0;
    std::vector<std::shared_ptr<Team::PlayerObject>> players_;

};

}

#endif // GAMEEVENTHANDLER_H
