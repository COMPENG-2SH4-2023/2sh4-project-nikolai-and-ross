#include "Player.h"

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef)
{
    // Assign game mechanics and food references
    mainGameMechsRef = thisGMRef; // Reference to the game mechanics
    mainFoodRef = thisFoodRef; // Reference to the food items
    myDir = STOP; // Set player's initial direction as STOP

    // Set up player's initial position
    objPos tempPos; // Create temporary object position
    // Calculate and assign the starting position for the player
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    playerPosList = new objPosArrayList(); // Initialize player position list
    playerPosList->insertHead(tempPos); // Set the initial position as the player's head
}


Player::~Player()
{
    // Deletes the heap member
    delete playerPosList;
}

objPosArrayList Player::getPlayerPos()
{
    return *playerPosList; // Returns the player's starting list position
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    // PPA3 input processing logic
    switch (input)
    {
    // process WASD
    case 'W':
    case 'w':
        if (myDir != DOWN)
            myDir = UP;
        break;
    case 'A':
    case 'a':
        if (myDir != RIGHT)
            myDir = LEFT;
        break;
    case 'S':
    case 's':
        if (myDir != UP)
            myDir = DOWN;
        break;
    case 'D':
    case 'd':
        if (myDir != LEFT)
            myDir = RIGHT;
        break;
    default:
        break;
    }
}

void Player::movePlayer()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead); // Get the current position of the player's head

    // PPA3 Finite State Machine logic to move the player based on the direction
    switch (myDir)
    {
    case UP:
        currHead.y--; // Move the player's head up
        // Check if the player reached the board's upper boundary
        if (currHead.y <= 0)
        {
            currHead.y = mainGameMechsRef->getBoardSizeY() - 2; // Wrap around to the bottom
        }
        break;

    case DOWN:
        currHead.y++; // Move the player's head down
        // Check if the player reached the board's lower boundary
        if (currHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
        {
            currHead.y = 1; // Wrap around to the top
        }
        break;

    case LEFT:
        currHead.x--; // Move the player's head to the left
        // Check if the player reached the board's left boundary
        if (currHead.x <= 0)
        {
            currHead.x = mainGameMechsRef->getBoardSizeX() - 2; // Wrap around to the right
        }
        break;

    case RIGHT:
        currHead.x++; // Move the player's head to the right
        // Check if the player reached the board's right boundary
        if (currHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
        {
            currHead.x = 1; // Wrap around to the left
        }
        break;
    }

    playerPosList->insertHead(currHead); // Update player's position by inserting the new head
    playerPosList->removeTail(); // Remove the last element to maintain player's movement
}


bool Player::checkFoodConsumption(objPos currentFood, objPosArrayList foodList)
{
    bool foodEaten = false; // Initialize flag to track if food is eaten
    objPos headPos;
    objPos tempFood;
    playerPosList->getHeadElement(headPos); // Get the player's current head position

    // Check if the player's score is less than 1
    if (mainGameMechsRef->getScore() < 1)
    {
        // Check if the player's head is at the current food position
        if (headPos.x == currentFood.x && headPos.y == currentFood.y)
        {
            foodEaten = true; // Set flag indicating food has been eaten
        }
    }

    // Loop through the food list to check for food items eaten by the player
    for (int i = 0; i < foodList.getSize(); i++)
    {
        foodList.getElement(tempFood, i); // Get each food item from the list

        // Check if the player's head is at the position of any food item
        if (headPos.x == tempFood.x && headPos.y == tempFood.y)
        {
            foodEaten = true; // Set flag indicating food has been eaten
            break; // Exit loop since food has been found and eaten
        }
    }

    return foodEaten; // Return flag indicating whether food has been eaten or not
}

bool Player::checkSelfCollision()
{
    objPos currentHead;
    bool collision = true; // Initialize collision as true, assuming collision by default
    playerPosList->getHeadElement(currentHead); // Get the player's current head position

    // Iterate through the player's body elements starting from the third element (excluding head)
    for (int i = 2; i < playerPosList->getSize(); i++)
    {
        objPos bodyElement;
        playerPosList->getElement(bodyElement, i); // Get each body element

        // Check if the player's head collides with any part of its own body
        if (currentHead.x == bodyElement.x && currentHead.y == bodyElement.y)
        {
            return collision; // Return true if collision detected
        }
    }

    return !collision; // Return false if no collision is detected
}


void Player::increasePlayerLength()
{
    objPos headPos;
    playerPosList->getTailElement(headPos); // Get the position of the player's tail

    playerPosList->insertTail(headPos); // Extend the player's body by adding a new segment at the tail
}


void Player::updatePlayerState(objPos currentFood, objPosArrayList foodList)
{
    objPosArrayList tempArrayList = getPlayerPos(); // Get the current positions of the player

    // Check if the player consumed any food
    if (checkFoodConsumption(currentFood, foodList))
    {
        foodConsumed(currentFood, foodList); // Process the effects of consumed food
        mainFoodRef->generateFood(tempArrayList); // Generate new food items on the board
    }

    // Check if the player has collided with itself
    if (checkSelfCollision() == true)
    {
        // Set game lose state, display game over screen, and exit the game
        mainGameMechsRef->setLoseTrue(); // Set the game state to indicate loss
        mainGameMechsRef->loseGameScreen(); // Display the game over screen
        mainGameMechsRef->setExitTrue(); // Set the flag to exit the game
        mainGameMechsRef->endGameScreen(); // Display the end game screen
    }
}

void Player::foodConsumed(objPos currentFood, objPosArrayList foodList){
    objPos tempFood;                // Create a temporary objPos to hold food details during iteration
    int scoreNum = 0;               // Initialize the score for the consumed food
    bool purge = false;             // Flag to determine if a player purge is needed
    objPos currHead;                // Holds the current position of the player's head
    playerPosList->getHeadElement(currHead); // Get the player's head position
    int increaseIters = 1;          // Counter to track the number of player body segment increases

    // Iterate through the food list to find the consumed food and process its effect
    for (int i = 0; i < foodList.getSize(); i++){
        foodList.getElement(tempFood, i); // Retrieve each food item from the list

        // Check if the player's head is on a food item
        if(currHead.x == tempFood.x && currHead.y == tempFood.y){
            switch (tempFood.getSymbol()){
                case '1':
                    scoreNum = 1;
                    break;
                case '2':
                    scoreNum = 2;
                    break;
                case '3':
                    scoreNum = 3;
                    break;
                case '4':
                    scoreNum = 4;
                    break;
                case '5':
                    scoreNum = 5;
                    break;
                case '6':
                    scoreNum = 6;
                    break;
                case '7':
                    scoreNum = 7;
                    break;
                case '8':
                    scoreNum = 8;
                    break;
                case '*':
                    scoreNum = 9; // Special case: increment the score and player length
                    increaseIters = 9; // Increase the player's length by 9 segments
                    break;
                case 'X':
                    scoreNum = -10; // Special case: decrease score and initiate player purge
                    purge = true; // Set the flag to purge the player's body
                    break;
                default:
                    scoreNum = 1; // Default score for other food items
                    purge = false; 
                    break;
            }
        }
    }

    // Process the effect of consumed food on the player
    if(purge == true){
        objPos tempHead;
        playerPosList->getHeadElement(tempHead); // Get the player's head position
        playerPosList->purgeList(); // Clear the player's body
        playerPosList->insertHead(tempHead); // Reinsert the head to maintain the player's position
    }
    else{
        int size = playerPosList->getSize();
        // Increase the player's length based on the consumed food type
        if(increaseIters != 1 && size != 1){
            for(int i = 0; i < increaseIters; i ++){
                increasePlayerLength(); // Add segments to the player's body
            }
        }
        else{
            increasePlayerLength(); // Increase player's length by one segment
        }
    }

    mainGameMechsRef->incrementScore(scoreNum); // Update the game score based on the consumed food
}
