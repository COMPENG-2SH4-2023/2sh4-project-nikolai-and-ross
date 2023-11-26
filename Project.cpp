#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000
GameMechs *myGM;
Player *myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// objPos player();

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
    myPlayer = new Player(myGM);
    myFood = newFood(myGM);
}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            if (i == 0 || i == myGM->getBoardSizeY()- 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c",'#');
            }
            else if (i == tempPos.y && j == tempPos.x)
            {
                MacUILib_printf("%c",tempPos.symbol);
            }
            else
            {

                MacUILib_printf("%c",' ');
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n",myGM->getScore(),tempPos.x,tempPos.y);
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
}
