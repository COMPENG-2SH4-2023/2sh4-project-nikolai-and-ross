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

void GameMechs::incrementScore(int n)
{
    score += n;
}

void GameMechs::LoadingScreen()
{
    int i = 0;
    while (i < 5)
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
        MacUILib_Delay(500000);
        MacUILib_printf("+========================================================================================+\n");
        MacUILib_printf("|........................................................................................|\n");
        MacUILib_printf("|.######..##..##...####...##..##..##..##..........##..##...####...##..##.                |\n");
        MacUILib_printf("|...##....##..##..##..##..###.##..##.##............####...##..##..##..##.                |\n");
        MacUILib_printf("|...##....######..######..##.###..####..............##....##..##..##..##.                |\n");
        MacUILib_printf("|...##....##..##..##..##..##..##..##.##.............##....##..##..##..##.                |\n");
        MacUILib_printf("|...##....##..##..##..##..##..##..##..##............##.....####....####..                |\n");
        MacUILib_printf("|........................................................................                |\n");
        MacUILib_printf("|.######...####...#####...........#####...##.......####...##..##..######..##..##...####..|\n");
        MacUILib_printf("|.##......##..##..##..##..........##..##..##......##..##...####.....##....###.##..##.....|\n");
        MacUILib_printf("|.####....##..##..#####...........#####...##......######....##......##....##.###..##.###.|\n");
        MacUILib_printf("|.##......##..##..##..##..........##......##......##..##....##......##....##..##..##..##.|\n");
        MacUILib_printf("|.##.......####...##..##..........##......######..##..##....##....######..##..##...####..|\n");
        MacUILib_printf("|........................................................................................|\n");
        MacUILib_printf("+========================================================================================+\n");
        // ASCII Art generated https://www.asciiart.eu/text-to-ascii-art
        MacUILib_Delay(500000);
        MacUILib_Delay(500000);
        MacUILib_Delay(500000);
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