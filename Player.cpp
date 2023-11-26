#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    playerPosList =  new objPosArrayList();
    playerPosList->insertHead(tempPos);

    //debug 4 segments
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
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
    objPos currHead;
    playerPosList->getHeadElement(currHead);
    // PPA3 Finite State Machine logic
    switch(myDir){
        case UP:
            currHead.y--;
            if(currHead.y <= 0){
                currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case DOWN:
            currHead.y++;
            if(currHead.y >= mainGameMechsRef->getBoardSizeY()){
                currHead.y = 1;
            }
            break;

        case LEFT:
            currHead.x--;
            if(currHead.x <= 0){
                currHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;

        case RIGHT:
            currHead.x++;
            if(currHead.x >= mainGameMechsRef->getBoardSizeX()){
                currHead.x = 1;
            }
            break;
    }

    playerPosList->insertHead(currHead);
    playerPosList->removeTail();
}
