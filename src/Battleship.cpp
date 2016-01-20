#include "Battleship.h"

player_s client[2];
bool gameStarted;

char playingField[32][16];

void initiate()
{
  client[0].score = 0;
  client[1].score = 0;

  if(!gameStarted)
  {
    setupGame();
  }

  gameStarted = true;
}

void setupGame()
{
  placePlayerShips();
  placeEnemyShips();
}

void placePlayerShips()
{
  placeShip(0, 4); // Aircraft carrier, 5 spaces - 1
  //placeShip(0, 3); // Battleship, 4 spaces - 1
  //placeShip(0, 2); // Submarine, 3 spaces - 1
  //placeShip(0, 2); // Destroyer, 3 spaces - 1
  //placeShip(0, 1); // Patrol Boat, 2 spaces - 1
}

void placeEnemyShips()
{
  //placeShip(1, 4); // Aircraft carrier, 5 spaces - 1
  //placeShip(1, 3); // Battleship, 4 spaces - 1
  //placeShip(1, 2); // Submarine, 3 spaces - 1
  //placeShip(1, 2); // Destroyer, 3 spaces - 1
  //placeShip(1, 1); // Patrol Boat, 2 spaces - 1
}

void placeShip(int clientIndex, int shipLength)
{
  /* Randomize whether we want the ship placed vertically or horizontally, we
     will do this by generating a random number and placing the ship vertical if
     the number is odd, horizontal if even. We could choose a random 0 or 1 but
     this adds more random-ness */

  /* If odd, place ship vertically, if even, place ship horizontally */
  int x = 4;
  int y = 10;

  for(int i = 0; i < 5; i++)
  {
    playingField[x][y + i] = 'a';
  }

  x = 8;
  y = 2;

  for(int i = 0; i < 3; i++)
  {
    playingField[x + i][y] = 'a';
  }
}

bool checkHit(int clientIndex, int x, int y)
{
 if(playingField[x][y] == 'a')
  return true; 
}
