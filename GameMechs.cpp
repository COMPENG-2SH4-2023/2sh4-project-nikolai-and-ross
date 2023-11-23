#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    gameBoard = new int *[boardSizeX];
    score = 0;
    loseFlag = false;
    exitFlag = false;
    input = NULL;
}

GameMechs::GameMechs(int boardX, int boardY)
{

    boardSizeX = boardX;
    boardSizeY = boardY;
    gameBoard = new int *[boardSizeX]
    score = 0;
    loseFlag = false;
    exitFlag = false;
    input = GameMechs.getInput();
    for (i = 0; i < boardSizeX; i++)
    {
        for (j = 0; j < boardSizeY; j++)
        {
            if (i == 0 || i == boardSizeX - 1 || j == 0 || j == boardSizeY - 1)
            {
                gameBoard[i][j]="#";
            }
            else
                gameBoard[i][j] = ' ';
        }
    }
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    	for (int i = 0; i < boardSizeX; i++)
	{
		delete[] gameBoard[i];
	}

	delete[] gameBoard;
}
void GameMechs::generateGameboard()
{
    for (i = 0; i < boardSizeX; i++)
    {
        for (j = 0; j < boardSizeY; j++)
        {
            if (i == 0 || i == boardSizeX - 1 || j == 0 || j == boardSizeY - 1)
            {
                gameBoard[i][j]="#";
            }
            else
                gameBoard[i][j] = ' ';
        }
    }
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
    return inpput; 
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

void GameMechs::setLoseTrue()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input
}

void GameMechs::clearInput()
{
    fflush(stdin);
    input = 0;
    
}

int GameMechs::getScore;
{
    return score;
}

void GameMechs::incrementScore;
{
    score++;
    return score;
}

