#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdlib.h>
#include "Structures.h"

void initiate();

int getGameTurn();

bool placeShip(int clientIndex, int shipLength, int placement, int x, int y);

void setGameTurn(int clientIndex);

void setFlag(int x, int y, char flag);

bool drawGameBoard(int x, int y);

bool drawWater(int x, int y);

bool drawScore(int clientIndex, int x, int y);

bool drawCursor(int x, int y);

bool checkHit(int clientIndex, int x, int y);

bool checkButtonPushed(int state, int currentClock);

char getFlag(int x, int y);

#endif
