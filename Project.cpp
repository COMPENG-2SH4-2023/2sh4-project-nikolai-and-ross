#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
GameMechs *myGM;
Player *myPlayer;
Food *myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (myGM->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(30, 15);
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);

    bool foodPresent = true;
    if (!foodPresent)
    {
        objPosArrayList *playerBody = myPlayer->getPlayerPos();
        myFood->generateFood(playerBody);
        foodPresent = true;
    }
}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    objPosArrayList *playerBody = myPlayer->getPlayerPos();
    objPos currentFoodPos;
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myFood->getFoodPos(currentFoodPos);
    myPlayer->updatePlayer(currentFoodPos);
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;
    int itemPresent = 0;
    
    objPosArrayList *playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    objPos currentFoodPos;
    myFood->getFoodPos(currentFoodPos);
    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {

            drawn = false;
            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            if (!drawn)
            {
                if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c", '#');
                }
                else if (i == currentFoodPos.y && j == currentFoodPos.x)
                {
                    MacUILib_printf("%c", currentFoodPos.getSymbol());
                }
                else
                {
                    MacUILib_printf("%c", ' ');
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("Player positions:\n");
    for (int l = 0; l < playerBody->getSize(); l++)
    {
        playerBody->getElement(tempBody, l);
        MacUILib_printf("<%d, %d>\n", tempBody.x, tempBody.y);
    }
    MacUILib_printf("Food positions:\n");
    MacUILib_printf("<%d, %d>\n", currentFoodPos.x, currentFoodPos.y);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
    delete myFood;
}
