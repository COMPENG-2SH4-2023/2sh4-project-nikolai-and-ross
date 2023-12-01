#include "Food.h"

Food::Food(GameMechs *thisGMRef)
{
    mainGameRef = thisGMRef;
    foodPos.setObjPos(10, 10, 'o');
    srand(time(NULL));
}

Food::~Food()
{
}
void Food::generateFood(objPosArrayList *blockOff)
{
    objPos *FoodPresent = new objPos;
    int x_size = mainGameRef->getBoardSizeX();
    int y_size = mainGameRef->getBoardSizeY();
    bool itemPresent = true;
    // objPos *FoodPresent = new objPos;

    while (itemPresent)
    {
        itemPresent = false;

        for (int i = 0; i < blockOff->getSize(); i++)
        {
            blockOff->getElement(*FoodPresent, i);
            if (foodPos.isPosEqual(FoodPresent))
            {
                itemPresent = true;
                break;
            }
            else
            {
                foodPos.x = rand() % (x_size - 2) + 1;
                foodPos.y = rand() % (y_size - 2) + 1;
            }
        }
    }
    foodPos.symbol = 'A';
}

objPos Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}
