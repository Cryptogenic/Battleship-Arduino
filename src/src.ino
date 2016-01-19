#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  matrix.begin();
  
  // draw a pixel in solid white
  matrix.drawPixel(5, 4, matrix.Color333(7, 7, 7)); 
  matrix.drawPixel(6, 4, matrix.Color333(7, 7, 7)); 
  matrix.drawPixel(5, 5, matrix.Color333(7, 7, 7));
  matrix.drawPixel(6, 5, matrix.Color333(7, 7, 7));
   
  delay(500);
}

void loop() {

}
