#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

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

    while(exitFlag == false)  
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

    // player.setObjPos(5,5,'*')

    exitFlag = false;
}

void GetInput(void)
{

}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos border[30][15]; // Change to be gamemechanics board size

    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 15; j++){
            if (i == 0 || i == 30 || j == 0 || j == 15){
                border[i][j].setObjPos(i,j,'#');
                MacUILib_printf("%c", border[i][j].symbol);
            }
        }
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
