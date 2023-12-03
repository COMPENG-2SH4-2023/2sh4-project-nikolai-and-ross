#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

class GameMechs;
class Food;

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

public:
    enum Dir
    {
        STOP,
        UP,
        DOWN,
        LEFT,
        RIGHT
    }; // This is the direction state

    Player(GameMechs *thisGMRef, Food *thisFoodRef);
    ~Player();

    objPosArrayList getPlayerPos(); // Upgrade this in iteration 3.
    void updatePlayerDir();
    void movePlayer();
    void increasePlayerLength();
    void updatePlayerState(objPos currentFood, objPosArrayList foodList);
    void foodConsumed(objPos currentFood, objPosArrayList foodList);
    bool checkFoodConsumption(objPos currentFood, objPosArrayList foodList);
    bool checkSelfCollision();

private:
    objPosArrayList *playerPosList; // Upgrade this in iteration 3.
    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;
    Food *mainFoodRef;
    enum Dir myDir;
};

#endif