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

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  matrix.begin();

  initiate();

  for(int x = 0; x < 32; x++)
  {
    for(int y = 0; y < 16; y++)
    {
      if(checkHit(0, x, y))
        matrix.drawPixel(x, y, matrix.Color333(0, 1, 0));
      else
        matrix.drawPixel(x, y, matrix.Color333(0, 0, 1));
      matrix.drawPixel(4, 11, matrix.Color333(1, 0, 0));
    }
  }

  delay(500);
}

void loop() {

}
