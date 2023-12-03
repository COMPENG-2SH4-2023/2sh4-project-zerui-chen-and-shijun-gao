#ifndef OBJPOS_H
#define OBJPOS_H

class objPos
{
public:
    int x;
    int y;
    char symbol;
    // Newly added member function to determine if it's on the edge of the gamepad
    bool isOnEdge(int maxRows, int maxCols);

    objPos();
    objPos(objPos &o); // copy constructor
    objPos(int xPos, int yPos, char sym);

    void setObjPos(objPos o);
    void setObjPos(int xPos, int yPos, char sym);
    void getObjPos(objPos &returnPos);
    char getSymbol();

    bool isPosEqual(const objPos *refPos);

    char getSymbolIfPosEqual(const objPos *refPos);


};

#endif