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

/* Stores the digital pin numbers used on the arduino for player interfacing */

const int fireButtonPin = 1;
const int leftButtonPin = 10;
const int rightButtonPin = 11;
const int upButtonPin = 12;
const int downButtonPin = 13;

/* Holds the (X, Y) co-ordinate to be cleared for the cursor */

int clearX = 19;
int clearY = 11;

/* Holds the (X, Y) co-ordinate to draw for the cursor */

int prevX = 19;
int prevY = 11;

/* Holds the (X, Y) co-ordinate for the enemy shot to draw */

int enemyX = 2;
int enemyY = 11;

bool fireShot;
bool gameStarted;

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

/*
   Function: fixShips
   Calls ship placement in an infinite loop until we get a correct placement
   Parameters:
      clientIndex  - The client number (0 for end-user, 1 for cpu)
      shipLength   - Holds the ships length in pixels
   See Also:
      placeShip(int clientIndex, int shipLength, int placement, int x, int y); [Battleship.cpp]
*/
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

/*
   Function: setup
   Sets up pin modes, generates a random seed, and initializes the game
*/
void setup()
{
  matrix.begin(); // initiates required library for outputting to matrix

  pinMode(fireButtonPin, OUTPUT);
  pinMode(leftButtonPin, OUTPUT);
  pinMode(rightButtonPin, OUTPUT);
  pinMode(upButtonPin, OUTPUT);
  pinMode(downButtonPin, OUTPUT);

  randomSeed(analogRead(A5)); // A5 is not connected and will therefore generate random noise

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

/*
   Function: loop
   Places ships and listens for button presses and acts accordingly
   See Also:
      placeShip(int clientIndex, int shipLength, int placement, int x, int y); [Battleship.cpp]
      checkButtonPushed(int state, int currentClock); [Battleship.cpp]
*/
void loop()
{
  delay(75); // Save the CPU some stress

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
    /* If it is the player's turn, check for button presses and proceed */
    if(getGameTurn() == 0)
    {
      if(checkButtonPushed(digitalRead(fireButtonPin), millis()))
      {
        fireShot = true;
        setGameTurn(1); // Set to CPU's turn
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
      /* Pick a random co-ordinate on the player's grid and fire */
      enemyX = random(2, 12);
      enemyY = random(2, 12);

      setGameTurn(0); // Set back to player's turn
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

      if(getFlag(x, y) == 'a') // 'a' flag -> valid ship (healthy)
        matrix.drawPixel(x, y, matrix.Color333(0, 1, 0));
      if(getFlag(x, y) == 'm') // 'm' flag -> missed shot
        matrix.drawPixel(x, y, matrix.Color333(2, 1, 0));
    }
  }
}
