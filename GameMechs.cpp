#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    loseFlag = false;
    exitFlag = false;
    input = 0; // Set input to null character
    gameBoard = new char *[boardSizeY];
    for (int i = 0; i < boardSizeY; i++)
    {
        gameBoard[i] = new char[boardSizeX];
    }
}

GameMechs::GameMechs(int boardX, int boardY)
{

    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    loseFlag = false;
    exitFlag = false;
    input = 0;
    gameBoard = new char *[boardSizeY];
    for (int i = 0; i < boardSizeY; i++)
    {
        gameBoard[i] = new char[boardSizeX];
    }

    // foodPos.setObjPos(-1,-1,'.');
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    for (int i = 0; i < boardSizeY; i++)
    {
        delete[] gameBoard[i];
    }

    delete[] gameBoard;
}

// void GameMechs::generateGameboard()
// {

//     for (int i = 0; i < boardSizeY; i++)
//     {
//         for (int j = 0; j < boardSizeX; ++j)
//         {
//             if (i == 0 || i == boardSizeY - 1 || j == 0 || j == boardSizeX - 1)
//             {
//                 gameBoard[i][j] = '#';
//             }
//             else
//             {
//                 gameBoard[i][j] = ' ';
//             }
//         }
//     }
// }

// void GameMechs::DrawGameboard()
// {
//     objPos tempPos;
//     myPlayer->getPlayerPos(tempPos);
//     for (int i = 0; i < myGM->getBoardSizeY(); i++)
//     {
//         for (int j = 0; j < myGM->getBoardSizeX(); j++)
//         {
//             if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
//             {
//                 MacUILib_printf("%c", '#');
//             }
//             else if (i == tempPos.y && j == tempPos.x)
//             {
//                 MacUILib_printf("%c", tempPos.symbol);
//             }
//             else
//             {

//                 MacUILib_printf("%c", ' ');
//             }
//         }
//         MacUILib_printf("\n");
//     }
//     MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n", myGM->getScore(), tempPos.x, tempPos.y);
// }

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar() != 0)
    {
        input = MacUILib_getChar();
    }
    if (input == 27)
    {
        setExitTrue();
        endGameScreen();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setExitFalse()
{
    exitFlag = false;
}
void GameMechs::setLoseTrue()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    fflush(stdin);
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::LoadingScreen()
{
    int i=0; 
    while (i<5)
    {
        MacUILib_clearScreen();
        MacUILib_printf("Welcome to Snake");
        MacUILib_Delay(100000);
    }

}


void GameMechs::endGameScreen()
{
    if (getExitFlagStatus())
    {
        MacUILib_clearScreen();
        MacUILib_printf("Thank you for playing");
        MacUILib_Delay(99999);
        MacUILib_clearScreen();
    }
}

void GameMechs::loseGameScreen()
{
    if (getLoseFlagStatus())
    MacUILib_clearScreen();
    MacUILib_printf("GAME OVER \n");
    MacUILib_Delay(99999);

    {
        MacUILib_clearScreen();
        MacUILib_printf("+=========================================================================+\n");
        MacUILib_printf("|.........................................................................|\n");
        MacUILib_printf("|..####....####...##...##..######...........####...##..##..######..#####..|\n");
        MacUILib_printf("|.##......##..##..###.###..##..............##..##..##..##..##......##..##.|\n");
        MacUILib_printf("|.##.###..######..##.#.##..####............##..##..##..##..####....#####..|\n");
        MacUILib_printf("|.##..##..##..##..##...##..##..............##..##...####...##......##..##.|\n");
        MacUILib_printf("|..####...##..##..##...##..######...........####.....##....######..##..##.|\n");
        MacUILib_printf("|.........................................................................|\n");
        MacUILib_printf("+=========================================================================+\n");
        MacUILib_Delay(500000);
        MacUILib_Delay(500000);
        MacUILib_Delay(500000);
    }
}