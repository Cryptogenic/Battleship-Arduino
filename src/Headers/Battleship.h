#ifndef BATTLESHIP_H
#define BATTLESHIP_H

//#include <stdlib.h>
#include "Structures.h"

void initate();

void setupGame();

game_s drawScreenTest(game_s game);

game_s drawGameBoard(game_s game);

void placePlayerShips();

void placeEnemyShips();

void placeShip(int clientIndex, int shipLength);

#endif
