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

void setup()
{
  matrix.begin();

  randomSeed(analogRead(A0));

  initiate();

  delay(500);
}

void loop()
{
  if(!gameStarted)
  {
    placeShip(0, 5, 1, random(2, 12), random(2, 12));
    placeShip(0, 4, 1, random(2, 12), random(2, 12));
    placeShip(0, 3, 1, random(2, 12), random(2, 12));
    placeShip(0, 3, 1, random(2, 12), random(2, 12));
    placeShip(0, 2, 1, random(2, 12), random(2, 12));

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
