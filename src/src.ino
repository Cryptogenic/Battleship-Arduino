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

int clearX = 19;
int clearY = 11;

int prevX = 19;
int prevY = 11;

int enemyX = 2;
int enemyY = 11;

bool fireShot;
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
  
  /* Draw the entire screen according to functions in Battleship.cpp */
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
    }
  }

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

    if(!placeShip(1, 5, random(1, 100), random(23, 28), random(6, 9)))
      fixShips(1, 5);
    if(!placeShip(1, 4, random(1, 100), random(23, 28), random(6, 9)))
      fixShips(1, 4);
    if(!placeShip(1, 3, random(1, 100), random(23, 28), random(6, 9)))
      fixShips(1, 3);
    if(!placeShip(1, 3, random(1, 100), random(23, 28), random(6, 9)))
      fixShips(1, 3);
    if(!placeShip(1, 2, random(1, 100), random(23, 28), random(6, 9)))
      fixShips(1, 2);
 
    gameStarted = true;
  }
  else
  { 
    if(getGameTurn() == 0)
    {
      if(checkButtonPushed(digitalRead(fireButtonPin), millis()))
      {
        fireShot = true;
        setGameTurn(1);
      }
      if(checkButtonPushed(digitalRead(leftButtonPin), millis()))
      {
        if((prevX - 1) > 17)
        {
          prevX -= 1;
        }
      }
      if(checkButtonPushed(digitalRead(rightButtonPin), millis()))
      {
        if((prevX + 1) < 30)
        {
          prevX += 1;
        }
      }
      if(checkButtonPushed(digitalRead(upButtonPin), millis()))
      {
        if((prevY - 1) > 2)
        {
          prevY -= 1;
        }
      }
    }
    else
    {
      enemyX = random(2, 12);
      enemyY = random(2, 12);

      setGameTurn(0);
    }
  }

  /* Draw the entire screen according to functions in Battleship.cpp */
  for(int x = 0; x < 32; x++)
  {
    for(int y = 0; y < 16; y++)
    {
      if(getGameTurn() == 0)
      {
        if(fireShot)
        {
          setFlag(prevX, prevY, 'm');

          fireShot = false;
        }
        else
        {
          matrix.drawPixel(clearX, clearY, matrix.Color333(0, 0, 1));
          matrix.drawPixel(prevX, prevY, matrix.Color333(1, 1, 0));

          clearX = prevX;
          clearY = prevY;
        }
      }
      else
      {
        matrix.drawPixel(enemyX, enemyY, matrix.Color333(2, 1, 0));
      }

      if(getFlag(x, y) == 'a')
        matrix.drawPixel(x, y, matrix.Color333(0, 1, 0));
      if(getFlag(x, y) == 'm')
        matrix.drawPixel(x, y, matrix.Color333(2, 1, 0));
    }
  }
}
