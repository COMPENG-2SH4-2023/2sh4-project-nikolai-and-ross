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

    MacUILib_printf("+==================================================================================+\n");
    MacUILib_printf("|..................................................................................|\n");
    MacUILib_printf("|.##...##..######..##.......####....####...##...##..######..........######...####..|\n");
    MacUILib_printf("|.##...##..##......##......##..##..##..##..###.###..##................##....##..##.|\n");
    MacUILib_printf("|.##.#.##..####....##......##......##..##..##.#.##..####..............##....##..##.|\n");
    MacUILib_printf("|.#######..##......##......##..##..##..##..##...##..##................##....##..##.|\n");
    MacUILib_printf("|..##.##...######..######...####....####...##...##..######............##.....####..|\n");
    MacUILib_printf("|..................................................................................|\n");
    MacUILib_printf("|....................####...##..##...####...##..##..######.........................|\n");
    MacUILib_printf("|...................##......###.##..##..##..##.##...##.............................|\n");
    MacUILib_printf("|....................####...##.###..######..####....####...........................|\n");
    MacUILib_printf("|.......................##..##..##..##..##..##.##...##.............................|\n");
    MacUILib_printf("|....................####...##..##..##..##..##..##..######.........................|\n");
    MacUILib_printf("|..................................................................................|\n");
    MacUILib_printf("+==================================================================================+\n");
    MacUILib_Delay(99999);
    MacUILib_Delay(99999);
    MacUILib_Delay(99999);
    MacUILib_clearScreen();
}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    objPos currentFoodPos;
    objPosArrayList foodList = myFood->getFoodPosList();
    myPlayer->updatePlayerDir();
    myFood->getFoodPos(currentFoodPos);
    myPlayer->updatePlayerState(currentFoodPos, foodList);
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool playerDrawn;
    bool foodDrawn;

    objPosArrayList playerBody = myPlayer->getPlayerPos();
    objPosArrayList foodList = myFood->getFoodPosList();
    objPos tempBody;
    objPos tempFood;

    // Default Food on game start-up extra food is generated after for fun
    objPos currentFoodPos;
    myFood->getFoodPos(currentFoodPos);

    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            if (myGM->getScore() < 1)
            {
                if (currentFoodPos.x == j && currentFoodPos.y == i)
                {
                    MacUILib_printf("%c", currentFoodPos.getSymbol());
                    continue;
                }
            }

            playerDrawn = false;
            for (int k = 0; k < playerBody.getSize(); k++)
            {
                playerBody.getElement(tempBody, k);
                if (tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    playerDrawn = true;
                    break;
                }
            }

            foodDrawn = false;
            if (!playerDrawn)
            {
                // foodDrawn = false;
                for (int l = 0; l < foodList.getSize(); l++)
                {
                    foodList.getElement(tempFood, l);
                    if (tempFood.x == j && tempFood.y == i)
                    {
                        MacUILib_printf("%c", tempFood.symbol);
                        foodDrawn = true;
                        break;
                    }
                }
            }
            if (!playerDrawn && !foodDrawn)
            {

                if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c", '#');
                }
                else
                {
                    MacUILib_printf("%c", ' ');
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("\n");
    MacUILib_printf("Score: %d\n", myGM->getScore());

    // Debugging
    //     MacUILib_printf("Player positions:\n");
    //     for (int m = 0; m < playerBody.getSize(); m++)
    //     {
    //         playerBody.getElement(tempBody, m);
    //         MacUILib_printf("<%d, %d>\n", tempBody.x, tempBody.y);
    //     }
    //     MacUILib_printf("Food positions:\n");
    //     for (int n = 0; n < foodList.getSize(); n++)
    //     {
    //         foodList.getElement(tempFood, n);
    //         MacUILib_printf("<%d, %d, %c>\n", tempFood.x, tempFood.y, tempFood.symbol);
    //     }
    //     MacUILib_printf("<%d, %d>\n", currentFoodPos.x, currentFoodPos.y);
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
