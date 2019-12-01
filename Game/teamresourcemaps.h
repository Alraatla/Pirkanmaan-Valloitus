#ifndef TEAMRESOURCEMAPS_H
#define TEAMRESOURCEMAPS_H

#include "core/basicresources.h"

namespace Team {

namespace TeamConstResourceMaps {

const Course::ResourceMap EMPTY = {};

// Building - Tyokkari
const Course::ResourceMap TYOKKARI_BUILD_COST = {
    {Course::BasicResource::MONEY, 10},
    {Course::BasicResource::FOOD, 2},
    {Course::BasicResource::WOOD, 1},
    {Course::BasicResource::STONE, 50}
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

// Tile Mountain
const Course::ResourceMap MOUNTAIN_BP = {
    {Course::MONEY, 2},
    {Course::FOOD, 1},
    {Course::WOOD, 0},
    {Course::STONE, 5},
    {Course::ORE, 3},
};
// Tile Water
const Course::ResourceMap WATER_BP = {
    {Course::MONEY, 0},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 0},
    {Course::ORE, 0},
};

// Farmer
const Course::ResourceMapDouble FARMER_EFFICIENCY = {
    {Course::MONEY, 4.00},
    {Course::FOOD, 3.00},
    {Course::WOOD, 0},
    {Course::STONE, 0},
    {Course::ORE, 0}
};

const Course::ResourceMap FARMER_RECRUITMENT_COST = {
    {Course::MONEY, 20},
    {Course::FOOD, 35}
};

// Miner
const Course::ResourceMapDouble MINER_EFFICIENCY = {
    {Course::MONEY, 2},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 2},
    {Course::ORE, 1}
};

const Course::ResourceMap MINER_RECRUITMENT_COST = {
    {Course::MONEY, 50},
    {Course::FOOD, 40}
};


const Course::ResourceMap BW_ROUNDLY_COST = {
    {Course::MONEY, 1},
    {Course::FOOD, 2}
};

const Course::ResourceMap FARMER_ROUNDLY_COST = {
    {Course::MONEY, 2},
    {Course::FOOD, 3}
};

const Course::ResourceMap MINER_ROUNDLY_COST = {
    {Course::MONEY, 3},
    {Course::FOOD, 3}
};

}
}


#endif // TEAMRESOURCEMAPS_H
