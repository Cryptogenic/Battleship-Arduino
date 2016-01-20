#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include "Headers/Battleship.h"
#include "Headers/Structures.h"

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

game_s game;

void setup() {
  matrix.begin();

  initiate();

  for(int x = 0; x < 32; x++)
  {
    for(int y = 0; y < 16; y++)
    {
      if(game.gameBoard[x][y] == FLAG_GRID_WHITE)
        matrix.drawPixel(x, y, matrix.Color333(7, 7, 7));
    }
  }

  delay(500);
}

void loop() {

}
