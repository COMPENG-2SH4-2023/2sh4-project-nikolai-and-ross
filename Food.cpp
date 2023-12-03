#include "Food.h"

Food::Food(GameMechs *thisGMRef)
{
    mainGameRef = thisGMRef;
    foodPos.setObjPos(15, 10, 'o');
    srand(time(NULL));
}

Food::~Food()
{
}
void Food::generateFood(objPosArrayList blockOff)
{
    objPos newFood;
    int x_size = mainGameRef->getBoardSizeX();
    int y_size = mainGameRef->getBoardSizeY();
    int noofFoodItems = rand() % 8 + 3;
    char FoodItems[] = {'g', 'J', 'Y', 'v', 'K', 's', 'i', 'n', 'E', 'X'};
    bool unique;
    specialFood.purgeList();
    for (int i = 0; i < noofFoodItems; i++)
    {
        int foodIndex = rand() % 10;
        do
        {
            unique = true;
            newFood.x = rand() % (x_size - 2) + 1;
            newFood.y = rand() % (y_size - 2) + 1;
            newFood.symbol = FoodItems[foodIndex];
            for (int i = 0; i < blockOff.getSize(); i++)
            {
                objPos tempPos;
                blockOff.getElement(tempPos, i);
                if (foodPos.isPosEqual(&newFood))
                {
                    unique = false;
                    break;
                }
            }
            if (unique)
            {
                // foodPos = newFood;
                // specialFood.removeHead();
                specialFood.insertHead(newFood);
                break;
            }
        } while (true);
    }
    // specialFood.removeTail();
}
objPos Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}

objPosArrayList Food::getFoodPosList()
{

    return specialFood;
}
