#include "Battleship.h"

player_s client[2];

char playingField[32][16];

void initiate()
{
  client[0].score = 0;
  client[1].score = 0;
}

void placeShip(int clientIndex, int shipLength, int placement, int x, int y)
{
  /* Randomize whether we want the ship placed vertically or horizontally, we
     will do this by generating a random number and placing the ship vertical if
     the number is odd, horizontal if even. We could choose a random 0 or 1 but
     this adds more random-ness */

  /* If odd, place ship vertically, if even, place ship horizontally */

  if(placement & 1)
  {
    if(!(y < (12 - shipLength)))
    {
      for(int i = 0; i < shipLength; i++)
      {
        playingField[x][y + i] = 'a';
      }
    }
    else
    {
      for(int i = 0; i < shipLength; i++)
      {
        playingField[x][y - i] = 'a';
      }
    }
  }
}

bool drawGameBoard(int x, int y)
{
  if((x > 0 && x < 13) || (x > 18 && x < 31) || (x == 15 || x == 16))
  {
    if(x == 15 || x == 16)
      return true;
      
    if(y > 0 && y < 13)
    {
      return true;
    }
    if(y == 14)
    {
      if(!(x > 8 && x < 23))
        return true;
    }
  }
  
  return false;
}

bool drawWater(int x, int y)
{
  if((x > 1 && x < 12) || (x > 19 && x < 30))
    if(y > 1 && y < 12)
      return true;

  return false;
}

bool drawScore(int clientIndex, int x, int y)
{
  if((clientIndex == 0) && (x > 9 && x < 13) && (y > 12 && y < 16))
    if(!(x == 11 && y == 14))
      return true;

  if((clientIndex == 1) && (x > 18 && x < 22) && (y > 12 && y < 16))
    if(!(x == 20 && y == 14))
      return true;

  return false;
}

bool checkHit(int clientIndex, int x, int y)
{
 if(playingField[x][y] == 'a')
  return true; 
}

char getFlag(int x, int y)
{
  return playingField[x][y];
}

