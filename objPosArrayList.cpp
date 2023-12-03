#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 200 heap elements
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::objPosArrayList(const objPosArrayList &copyList)
{
    arrayCapacity = copyList.arrayCapacity; // Copy the capacity of the list from the original list
    listSize = copyList.listSize; // Copy the size of the list from the original list

    aList = new objPos[arrayCapacity]; // Create a new array with the same capacity

    // Copy each element from the original list to the new list
    for (int i = 0; i < listSize; i++)
    {
        aList[i] = copyList.aList[i];
    }
}


objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize == arrayCapacity)
    {
        return; // Return if the list is already at maximum capacity
    }

    // Shift existing elements to make space for the new head position
    for (int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i - 1]); // Shift each element one position to the right
    }

    aList[0].setObjPos(thisPos); // Set the new head position at the beginning of the list

    listSize++; // Increment the list size to reflect the addition of a new element
}


void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity)
    {
        return; // If the list is already at maximum capacity, return without insertion
    }

    aList[listSize].setObjPos(thisPos); // Set the provided objPos at the end of the list

    listSize++; // Increment the list size to reflect the addition of a new element
}

void objPosArrayList::removeHead()
{
    if (listSize <= 0)
    {
        return; // If the list is empty or contains no elements, return without removal
    }

    // Shift elements to the left to remove the head element
    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i].setObjPos(aList[i + 1]); // Shift each element one position to the left
    }

    listSize--; // Decrement the list size to reflect the removal of the first element
}


void objPosArrayList::removeTail()
{
    if (listSize <= 0)
    {
        return;
    }

    listSize--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}

void objPosArrayList::purgeList()
{
    listSize = 0;
}