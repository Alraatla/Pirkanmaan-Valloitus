#ifndef RESOURCEMAPS_H
#define RESOURCEMAPS_H

#include "core/basicresources.h"

namespace Team {

namespace ConstResourceMaps {

const Course::ResourceMap EMPTY = {};

const Course::ResourceMap MOUNTAIN_BP = {
    {Course::MONEY, 2},
    {Course::FOOD, 1},
    {Course::WOOD, 0},
    {Course::STONE, 5},
    {Course::ORE, 3},
};

}
}


#endif // RESOURCEMAPS_H
