#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include "Battleship.h"
#include "Structures.h"

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

bool gameStarted;

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void fixShips(int clientIndex, int shipLength)
{
  for(;;)
  {
    if(clientIndex == 0)
    {
      if(placeShip(clientIndex, shipLength, 1, random(3, 11), random(6, 8)))
        break;
    }
    else
    {
      if(placeShip(clientIndex, shipLength, 1, random(18, 30), random(6, 9)))
        break;
    }
  }
}

void setup()
{
  matrix.begin();

  randomSeed(analogRead(A5));

  initiate();

  delay(500);
}

void loop()
{
  if(!gameStarted)
  {
    for(int ship = 5; ship > 1; ship--)
    {
      if(placeShip(0, ship, random(1, 100), random(5, 11), random(6, 9)))
        fixShips(0, ship);
      if(placeShip(1, ship, random(1, 100), random(18, 30), random(6, 9)))
        fixShips(1, ship);
    }

    gameStarted = true;
  }
  
  for(int x = 0; x < 32; x++)
  {
    for(int y = 0; y < 16; y++)
    {
      if(drawGameBoard(x, y))
        matrix.drawPixel(x, y, matrix.Color333(1, 1, 1));
      if(drawScore(0, x, y))
        matrix.drawPixel(x, y, matrix.Color333(0, 1, 0));
      if(drawScore(1, x, y))
        matrix.drawPixel(x, y, matrix.Color333(1, 0, 0));
      if(drawWater(x, y))
        matrix.drawPixel(x, y, matrix.Color333(0, 0, 1));
      if(getFlag(x, y) == 'a')
        matrix.drawPixel(x, y, matrix.Color333(0, 1, 0));
    }
  }

  matrix.drawPixel(random(2, 12), random(2, 12), matrix.Color333(1, 0, 0));

  delay(2000);
}
