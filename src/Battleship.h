#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdlib.h>
#include "Structures.h"

void initiate();

bool placeShip(int clientIndex, int shipLength, int placement, int x, int y);

bool drawGameBoard(int x, int y);

bool drawWater(int x, int y);

bool drawScore(int clientIndex, int x, int y);

bool checkHit(int clientIndex, int x, int y);

char getFlag(int x, int y);

#endif
