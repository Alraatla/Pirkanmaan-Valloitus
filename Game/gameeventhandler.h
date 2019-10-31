#include "interfaces/igameeventhandler.h"

#include "core/basicresources.h"

#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <memory>
#include <vector>


namespace Team {

class gameEventHandler : public Course::iGameEventHandler
{
public:
    gameEventHandler();


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

};

}

#endif // GAMEEVENTHANDLER_H
