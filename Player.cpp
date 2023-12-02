#include "Player.h"

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = RIGHT;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList Player::getPlayerPos()
{

    return *playerPosList;
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
bool Player::checkFoodConsumption(objPos currentFood)
{

    bool foodEaten = false;
    objPos headPos;

    playerPosList->getHeadElement(headPos);
    if (headPos.x == currentFood.x && headPos.y == currentFood.y)
    {
        foodEaten = true;
    }

    return foodEaten;
}

bool Player::checkSelfCollision()
{
    objPos currentHead;
    bool collision = true;
    playerPosList->getHeadElement(currentHead);

    for (int i = 2; i < playerPosList->getSize(); i++)
    {
        objPos bodyElement;
        playerPosList->getElement(bodyElement, i);

        if (currentHead.x == bodyElement.x && currentHead.y == bodyElement.y)
        {
            return (collision);
        }
    }

    return (!collision);
}

void Player::increasePlayerLength()
{
    objPos headPos;
    playerPosList->getHeadElement(headPos);
    playerPosList->insertHead(headPos);
}

void Player::updatePlayerState(objPos currentFood)
{
    objPosArrayList tempArrayList = getPlayerPos();
    if (checkFoodConsumption(currentFood))
    {
        mainGameMechsRef->incrementScore();
        increasePlayerLength();
        mainFoodRef->generateFood(tempArrayList);
    }
    if (checkSelfCollision() == true)
    {
        mainGameMechsRef->setLoseTrue();
        mainGameMechsRef->loseGameScreen();
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->endGameScreen();
    }
}