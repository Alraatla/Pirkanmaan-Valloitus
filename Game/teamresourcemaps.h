#ifndef TEAMRESOURCEMAPS_H
#define TEAMRESOURCEMAPS_H

#include "core/basicresources.h"

namespace Team {

namespace TeamConstResourceMaps {

const Course::ResourceMap EMPTY = {};

// Building - Tyokkari
const Course::ResourceMap TYOKKARI_BUILD_COST = {
    {Course::BasicResource::MONEY, 2000},
    {Course::BasicResource::FOOD, 600},
    {Course::BasicResource::WOOD, 800},
    {Course::BasicResource::STONE, 400}
};
const Course::ResourceMap TYOKKARI_PRODUCTION = {
    {Course::BasicResource::MONEY, -10},
    {Course::BasicResource::FOOD, -5},
};

// Building - Mine
const Course::ResourceMap MINE_BUILD_COST = {
    {Course::BasicResource::MONEY, 750},
    {Course::BasicResource::FOOD, 1000},
    {Course::BasicResource::WOOD, 500},
    {Course::BasicResource::STONE, 250}
};
const Course::ResourceMap MINE_PRODUCTION = {
    {Course::BasicResource::MONEY, 5},
    {Course::BasicResource::STONE, 10},
    {Course::BasicResource::ORE, 10},
};

const Course::ResourceMap MOUNTAIN_BP = {
    {Course::MONEY, 2},
    {Course::FOOD, 1},
    {Course::WOOD, 0},
    {Course::STONE, 5},
    {Course::ORE, 3},
};

}
}


#endif // TEAMRESOURCEMAPS_H
