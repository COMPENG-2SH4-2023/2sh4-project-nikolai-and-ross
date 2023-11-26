#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    playerPosList =  new objPosArrayList();
    playerPosList.insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    // PPA3 input processing logic
    switch (input)
    {
    // process WASD
    case 'w':
        if (myDir != DOWN)
            myDir = UP;
        break;
    case 'a':
        if (myDir != RIGHT)
            myDir = LEFT;
        break;
    case 's':
        if (myDir != UP)
            myDir = DOWN;
        break;
    case 'd':
        if (myDir != LEFT)
            myDir = RIGHT;
        break;
    default:
        break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    if (myDir == UP)
    {
        playerPos.setObjPos(playerPos.x, playerPos.y - 1, '*');
    }
    else if (myDir == DOWN)
    {
        playerPos.setObjPos(playerPos.x, playerPos.y + 1, '*');
    }
    else if (myDir == LEFT)
    {
        playerPos.setObjPos(playerPos.x - 1, playerPos.y, '*');
    }
    else if (myDir == RIGHT)
    {
        playerPos.setObjPos(playerPos.x + 1, playerPos.y, '*');
    }

    if (playerPos.x < 1)
    {
        playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (playerPos.x >= mainGameMechsRef->getBoardSizeX() - 1)
    {
        playerPos.x = 1;
    }

    if (playerPos.y < 1)
    {
        playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (playerPos.y >= mainGameMechsRef->getBoardSizeY() - 1)
    {
        playerPos.y = 1;
    }
}
