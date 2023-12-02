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
    arrayCapacity = copyList.arrayCapacity;
    listSize = copyList.listSize;
    aList = new objPos[arrayCapacity];
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
    if(listSize == arrayCapacity){
        return;
    }

    for(int i = listSize; i > 0; i--){
        aList[i].setObjPos(aList[i-1]);
    }

    aList[0].setObjPos(thisPos);

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity){
        return;
    }

    aList[listSize].setObjPos(thisPos);

    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize <= 0){
        return;
    }

    for(int i = 0; i < listSize; i ++){
        aList[i].setObjPos(aList[i+1]);
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize <= 0){
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
    returnPos.setObjPos(aList[listSize-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}

void objPosArrayList::purgeList(){
    listSize = 0;
}