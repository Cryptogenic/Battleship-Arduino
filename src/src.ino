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

const int fireButtonPin = 1;
const int leftButtonPin = 10;
const int rightButtonPin = 11;
const int upButtonPin = 12;
const int downButtonPin = 13;

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

  pinMode(fireButtonPin, OUTPUT);
  pinMode(leftButtonPin, OUTPUT);
  pinMode(rightButtonPin, OUTPUT);
  pinMode(upButtonPin, OUTPUT);
  pinMode(downButtonPin, OUTPUT);

  randomSeed(analogRead(A5));

  initiate();

  delay(500);
}

void loop()
{
  delay(75);
  
  if(!gameStarted)
  {
    if(!placeShip(0, 5, random(1, 100), random(5, 11), random(6, 9)))
      fixShips(0, 5);
    if(!placeShip(0, 4, random(1, 100), random(5, 11), random(6, 9)))
      fixShips(0, 4);
    if(!placeShip(0, 3, random(1, 100), random(5, 11), random(6, 9)))
      fixShips(0, 3);
    if(!placeShip(0, 3, random(1, 100), random(5, 11), random(6, 9)))
      fixShips(0, 3);
    if(!placeShip(0, 2, random(1, 100), random(5, 11), random(6, 9)))
      fixShips(0, 2);

    if(!placeShip(1, 5, random(1, 100), random(22, 28), random(6, 9)))
      fixShips(1, 5);
    if(!placeShip(1, 4, random(1, 100), random(22, 28), random(6, 9)))
      fixShips(1, 4);
    if(!placeShip(1, 3, random(1, 100), random(22, 28), random(6, 9)))
      fixShips(1, 3);
    if(!placeShip(1, 3, random(1, 100), random(22, 28), random(6, 9)))
      fixShips(1, 3);
    if(!placeShip(1, 2, random(1, 100), random(22, 28), random(6, 9)))
      fixShips(1, 2);
 
    gameStarted = true;
  }
  else
  {
    if(checkButtonPushed(digitalRead(fireButtonPin), millis()))
    {
      matrix.drawPixel(0, random(2, 12), matrix.Color333(1, 0, 0));
    }
    if(!checkButtonPushed(digitalRead(fireButtonPin), millis()))
    {
      matrix.drawPixel(0, 0, matrix.Color333(0, 0, 0));
    }
    if(checkButtonPushed(digitalRead(leftButtonPin), millis()))
    {
      matrix.drawPixel(0, random(2, 12), matrix.Color333(1, 0, 0));
    }
    if(!checkButtonPushed(digitalRead(leftButtonPin), millis()))
    {
      matrix.drawPixel(0, 0, matrix.Color333(0, 0, 0));
    }
    if(checkButtonPushed(digitalRead(rightButtonPin), millis()))
    {
      matrix.drawPixel(0, random(2, 12), matrix.Color333(1, 0, 0));
    }
    if(!checkButtonPushed(digitalRead(rightButtonPin), millis()))
    {
      matrix.drawPixel(0, 0, matrix.Color333(0, 0, 0));
    }
    if(checkButtonPushed(digitalRead(upButtonPin), millis()))
    {
      matrix.drawPixel(0, random(2, 12), matrix.Color333(1, 0, 0));
    }
    if(!checkButtonPushed(digitalRead(upButtonPin), millis()))
    {
      matrix.drawPixel(0, 0, matrix.Color333(0, 0, 0));
    }
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
}
