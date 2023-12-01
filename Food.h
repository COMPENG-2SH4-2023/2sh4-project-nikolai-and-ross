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
    GameMechs *mainGameRef;

public:
    Food(GameMechs *thisGMRef);
    ~Food();
    objPos getFoodPos(objPos &returnPos);
    void generateFood(objPosArrayList *blockOff);
};

#endif