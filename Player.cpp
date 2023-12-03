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
    case 'W':
    case 'w':
        if (myDir != DOWN)
            myDir = UP;
        break;
    case 'A':
    case 'a':
        if (myDir != RIGHT)
            myDir = LEFT;
        break;
    case 'S':
    case 's':
        if (myDir != UP)
            myDir = DOWN;
        break;
    case 'D':
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
bool Player::checkFoodConsumption(objPos currentFood, objPosArrayList foodList)
{

    bool foodEaten = false;
    objPos headPos;
    objPos tempFood;
    playerPosList->getHeadElement(headPos);

    if (mainGameMechsRef->getScore() < 1)
    {
        if (headPos.x == currentFood.x && headPos.y == currentFood.y)
        {
            foodEaten = true;
        }
    }
    for (int i = 0; i < foodList.getSize(); i++)
    {

        foodList.getElement(tempFood, i);
        if (headPos.x == tempFood.x && headPos.y == tempFood.y)
        {
            foodEaten = true;
            break;
        }
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
    playerPosList->getTailElement(headPos);
    playerPosList->insertTail(headPos);
}

void Player::updatePlayerState(objPos currentFood, objPosArrayList foodList)
{
    objPosArrayList tempArrayList = getPlayerPos();
    if (checkFoodConsumption(currentFood, foodList))
    {
        foodConsumed(currentFood, foodList);
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

void Player::foodConsumed(objPos currentFood, objPosArrayList foodList)
{
    if (checkFoodConsumption(currentFood, foodList))
    {
        objPos tempFood;
        for (int i = 0; i < foodList.getSize(); i++)
        {
            foodList.getElement(tempFood, i);
            switch (tempFood.getSymbol())
            {
            case 'A':
                mainGameMechsRef->incrementScore(5);
                increasePlayerLength();
                break;
            case '+':
                mainGameMechsRef->incrementScore(10);
                increasePlayerLength();
                break;
            case 'L':
                mainGameMechsRef->incrementScore(20);
                for (int i = 0; i < 20; i++)
                {
                    increasePlayerLength();
                    break;
                }

                break;
            case 'o':
                mainGameMechsRef->incrementScore();
                increasePlayerLength();
                break;
            case '.':
                mainGameMechsRef->incrementScore(-10);
                increasePlayerLength();
                break;
            case 'F':
                mainGameMechsRef->incrementScore(50);
                increasePlayerLength();
                break;
            case 'y':
                mainGameMechsRef->incrementScore(-40);
                increasePlayerLength();
                break;
            case 's':
                mainGameMechsRef->incrementScore(10);
                increasePlayerLength();
                break;
            case '-':
                mainGameMechsRef->incrementScore(-30);
                increasePlayerLength();
                break;
            case 'W':
                mainGameMechsRef->incrementScore(100);
                increasePlayerLength();
                break;

            default:
                break;
            }
        }
    }
}