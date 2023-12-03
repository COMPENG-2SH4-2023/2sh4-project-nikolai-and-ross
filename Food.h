#ifndef FOOD_H
#define FOOD_H

#include "GameMechs.h"
#include "Player.h"
#include "objPos.h"
#include "objPosArrayList.h"

#include <cstdlib>
#include <time.h>

class GameMechs;
class Player;

class Food
{
private:
    objPos foodPos;
    objPosArrayList specialFood;
    GameMechs *mainGameRef;

public:
    Food(GameMechs *thisGMRef);
    objPosArrayList getFoodPos();
    ~Food();
    objPos getFoodPos(objPos &returnPos);
    objPosArrayList getFoodPosList();
    void generateFood(objPosArrayList blockOff);
};

#endif