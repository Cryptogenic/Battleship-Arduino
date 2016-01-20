#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdlib.h>
#include "Structures.h"

void initiate();

void setupGame();

void placePlayerShips();

void placeEnemyShips();

void placeShip(int clientIndex, int shipLength);

bool checkHit(int clientIndex, int x, int y);

#endif
