#include "Player.h"

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    // debug 4 segments
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

objPosArrayList *Player::getPlayerPos()
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
    switch (myDir)
    {
    case UP:
        currHead.y--;
        if (currHead.y <= 0)
        {
            currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        break;

    case DOWN:
        currHead.y++;
        if (currHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
        {
            currHead.y = 1;
        }
        break;

    case LEFT:
        currHead.x--;
        if (currHead.x <= 0)
        {
            currHead.x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        break;

    case RIGHT:
        currHead.x++;
        if (currHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
        {
            currHead.x = 1;
        }
        break;
    }

    playerPosList->insertHead(currHead);
    playerPosList->removeTail();
}
bool Player::checkFoodConsumption(const objPos &currentFood)
{

    bool foodEaten = false;
    objPos currHead;

    playerPosList->getHeadElement(currHead);
    if (currHead.x == currentFood.x && currHead.y == currentFood.y)
    {
        foodEaten = true;
    }

    return foodEaten;
}

bool Player::checkSelfCollision()
{
    objPos bodyElement;
    objPos currHead;
    if (playerPosList->getSize() > 1)
    {
        for (int i = 0; i < playerPosList->getSize(); i++)
        {
            playerPosList->getElement(bodyElement, i);

            if (currHead.x == bodyElement.x && currHead.y == bodyElement.y)
            {
                return true;
            }
        }
    }
}

void Player::increasePlayerLength()
{
    objPos tempPos;
    playerPosList->insertHead(tempPos);
}

void Player::updatePlayer(const objPos &currentFood)
{
    // mainFoodRef->getFoodPos();
    if (checkFoodConsumption(currentFood))
    {

        mainGameMechsRef->incrementScore();
        increasePlayerLength();
        mainFoodRef->generateFood((getPlayerPos()));
    }
    if (checkSelfCollision())
    {

        mainGameMechsRef->setLoseTrue();
        mainGameMechsRef->setExitTrue();
    }
}