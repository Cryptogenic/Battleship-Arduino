#include "Headers/Battleship.h"

player_s client[2];
bool gameStarted;

void initate()
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

game_s drawScreenTest(game_s game)
{
  game.gameBoard[4][4] = FLAG_GRID_WHITE;

  game.gameBoard[5][5] = FLAG_GRID_WHITE;
}

game_s drawGameBoard(game_s game)
{
  // do nothing
}

void placePlayerShips()
{
  placeShip(0, 4); // Aircraft carrier, 5 spaces - 1
  placeShip(0, 3); // Battleship, 4 spaces - 1
  placeShip(0, 2); // Submarine, 3 spaces - 1
  placeShip(0, 2); // Destroyer, 3 spaces - 1
  placeShip(0, 1); // Patrol Boat, 2 spaces - 1
}

void placeEnemyShips()
{
  placeShip(1, 4); // Aircraft carrier, 5 spaces - 1
  placeShip(1, 3); // Battleship, 4 spaces - 1
  placeShip(1, 2); // Submarine, 3 spaces - 1
  placeShip(1, 2); // Destroyer, 3 spaces - 1
  placeShip(1, 1); // Patrol Boat, 2 spaces - 1
}

void placeShip(int clientIndex, int shipLength)
{
  /* Randomize whether we want the ship placed vertically or horizontally, we
     will do this by generating a random number and placing the ship vertical if
     the number is odd, horizontal if even. We could choose a random 0 or 1 but
     this adds more random-ness */

  /* If odd, place ship vertically, if even, place ship horizontally */
  int randInt;
  int x;
  int y;

  //randInt = rand() % 100 + 1; // Generate a random number between 1-100
  randInt = 2;

  //x = rand() % 8;
  //y = rand() % 8;
  x = 5;
  y = 6;

  for(int shipSpace = 0; shipSpace < shipLength; shipSpace++)
  {
    if(randInt & 1)
    {
      /* If shipSpace is 0, place random point */
      if(shipSpace == 0 && client[clientIndex].grid[x][y] == FLAG_EMPTY)
      {
        client[clientIndex].grid[x][y] = FLAG_SHIP_OK;
      }
      else /* Use point generated at shipSpace = 0 and apply Y transformations */
      {
        if(client[clientIndex].grid[x][y + shipSpace] == FLAG_EMPTY && (y + shipLength - shipSpace) < 8)
          client[clientIndex].grid[x][y + shipSpace] = FLAG_SHIP_OK;
        else if(client[clientIndex].grid[x][y - shipSpace]  == FLAG_EMPTY && (y - shipLength - shipSpace) > 0)
          client[clientIndex].grid[x][y - shipSpace] = FLAG_SHIP_OK;
      }
    }
    else
    {
      /* If shipSpace is 0, place random point */
      if(shipSpace == 0 && client[clientIndex].grid[x][y] == FLAG_EMPTY)
      {
        client[clientIndex].grid[x][y] = FLAG_SHIP_OK;
      }
      else /* Use point generated at shipSpace = 0 and apply Y transformations */
      {
        if(client[clientIndex].grid[x + shipSpace][y] == FLAG_EMPTY && (x + shipLength - shipSpace) < 8)
          client[clientIndex].grid[x + shipSpace][y] = FLAG_SHIP_OK;
        else if(client[clientIndex].grid[x - shipSpace][y] == FLAG_EMPTY && (x - shipLength - shipSpace) > 0)
          client[clientIndex].grid[x - shipSpace][y] = FLAG_SHIP_OK;
      }
    }
  }
}
