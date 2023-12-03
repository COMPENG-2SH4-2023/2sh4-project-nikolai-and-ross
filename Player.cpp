#include "Player.h"

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2 - 3, '@');

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

void Player::foodConsumed(objPos currentFood, objPosArrayList foodList){
    objPos tempFood;
    int scoreNum = 0;
    bool purge = false;
    if(currentFood.symbol == 'o'){
        scoreNum = 1;
    }
    objPos currHead;
    playerPosList->getHeadElement(currHead);

    for (int i = 0; i < foodList.getSize(); i++){
        foodList.getElement(tempFood, i);
        if(currHead.x == tempFood.x && currHead.y == tempFood.y){
            switch (tempFood.getSymbol()){
            case 'g':
                scoreNum = 1;
                break;
            case 'J':
                scoreNum = 2;
                break;
            case 'Y':
                scoreNum = 3;
                break;
            case 'v':
                scoreNum = 4;
                break;
            case 'K':
                scoreNum = 5;
                break;
            case 's':
                scoreNum = 6;
                break;
            case 'i':
                scoreNum = 7;
                break;
            case 'n':
                scoreNum = 8;
                break;
            case 'E':
                scoreNum = 9;
                break;
            case 'X':
                scoreNum = 1;
                purge = true;
                break;
            default:
                scoreNum = 1;
                purge = false; 
                break;
        }
        }
    }
    if(purge == true){
        objPos tempHead;
        playerPosList->getHeadElement(tempHead);
        playerPosList->purgeList();
        playerPosList->insertHead(tempHead);
    }
    else{
    increasePlayerLength();
    }
    mainGameMechsRef->incrementScore(scoreNum);
}