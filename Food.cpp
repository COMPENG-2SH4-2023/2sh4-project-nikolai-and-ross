#include "Food.h"

// Default constructor for the food class 

Food::Food(GameMechs *thisGMRef)
{
    objPosArrayList playerBody;
    mainGameRef = thisGMRef;
    foodPos.setObjPos(-1, -1, 'o');
    srand(time(NULL));
    generateFood(playerBody);
}
// Empty destructor as there are no heep elements
Food::~Food()
{

}


void Food::generateFood(objPosArrayList blockOff)
{
    objPos newFood;
    int x_size = mainGameRef->getBoardSizeX();
    int y_size = mainGameRef->getBoardSizeY();
    int noofFoodItems = rand() % 6 + 5; // random number of food items generated each iteration. [5,10]
    char FoodItems[] = {'1', '2', '3', '4', '5', '6', '7', '8', '*', 'X'}; // Possible food choices.  
    bool unique;
    specialFood.purgeList();
    for (int i = 0; i < noofFoodItems; i++)
    {
        int foodIndex = rand() % 10; // Picknig a random choice 
        do
        {
            unique = true;
            newFood.x = rand() % (x_size - 2) + 1;  // generating random coordinates
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
            if (unique) // if the cordinates are unique add to an arraylist of valid fooditems which get printed 
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
