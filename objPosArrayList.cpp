#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    int arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Insert the element in the header
    if (sizeList < ARRAY_MAX_CAP)
    {
        for (int i = sizeList; i > 0; --i)
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
        sizeList++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Insert the element at the end
    if (sizeList < ARRAY_MAX_CAP)
    {
        aList[sizeList] = thisPos;
        sizeList++;
    }
}

void objPosArrayList::removeHead()
{
    // Remove the header element
    if (sizeList > 0)
    {
        for (int i = 0; i < sizeList - 1; ++i)
        {
            aList[i] = aList[i + 1];
        }
        sizeList--;
    }
}

void objPosArrayList::removeTail()
{
    // Remove trailing elements
    if (sizeList > 0)
    {
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    // Get the value of the header element, write to returnPos
    if (sizeList > 0)
    {
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    // Get the value of the trailing element, write to returnPos
    if (sizeList > 0)
    {
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    // Get the value of the element at the specified index and write it to returnPos.
    if (index >= 0 && index < sizeList)
    {
        returnPos = aList[index];
    }
}