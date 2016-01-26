#include "Battleship.h"

player_s client[2];

char playingField[32][16]; /* Stores all flags for every pixel */

int gameTurn; /* Stores who's turn it is */

unsigned long buttonClock = 0; /* Used for debouncing */

/*
   Function: initiate
   Sets both player's scores to 0
*/
void initiate()
{
  client[0].score = 0;
  client[1].score = 0;
}

/*
   Function: getGameTurn
   Returns who's turn it is

   Returns:
      Client number of who's turn it is
*/
int getGameTurn()
{
  return gameTurn;
}

/*
   Function: placeShips
   Places the ship for the specified player with the specified ship length
   
   Parameters:
      clientIndex  - The client number (0 for end-user, 1 for cpu)
      shipLength   - Holds the ships length in pixels
      placement    - Holds a random value between 1-100 to determine horizontal or vertical
      x            - Holds the X co-ordinate (randomly generated)
      y            - Holds the Y co-ordinate (randomly generated)

   Returns:
      False if ship placement invalid, true otherwise
*/
bool placeShip(int clientIndex, int shipLength, int placement, int x, int y)
{
  /* Randomize whether we want the ship placed vertically or horizontally, we
     will do this by generating a random number and placing the ship vertical if
     the number is odd, horizontal if even. We could choose a random 0 or 1 but
     this adds more random-ness */

  /* If odd, place ship vertically, if even, place ship horizontally */

  bool placeOK;

  if(placement & 1) // If odd, place vertical
  {
    /* Check if we will run out of bounds */
    if(!(y < (12 - shipLength)))
    {
      for(int i = 0; i < shipLength; i++)
      {
        /* If we encounter a ship flag, invalid placement, return false */
        if(getFlag(x, y + i) == 'a')
        {
          placeOK = false;
          break;
        }
        else
          placeOK = true;
      }

      if(placeOK)
      {
        for(int i = 0; i < shipLength; i++)
          playingField[x][y + i] = 'a';
      }
      else
        return false;
    }
    else // Place upwards as down will go out of bounds
    {
      for(int i = 0; i < shipLength; i++)
      {
        /* If we encounter a ship flag, invalid placement, return false */
        if(getFlag(x, y - i) == 'a')
        {
          placeOK = false;
          break;
        }
        else
          placeOK = true;
      }

      if(placeOK)
      {
        for(int i = 0; i < shipLength; i++)
          playingField[x][y - i] = 'a';
      }
      else
        return false;
    }
  }
  else // Place ship horizontally
  {
    /* Check if we will run out of bounds going right */
    if(!(x < (9 - shipLength)))
    {
      for(int i = 0; i < shipLength; i++)
      {
        /* If we encounter a ship flag, invalid placement, return false */ 
        if(getFlag(x + i, y) == 'a')
        {
          placeOK = false;
          break;
        }
        else
          placeOK = true;
      }

      if(placeOK)
      {
        for(int i = 0; i < shipLength; i++)
          playingField[x + i][y] = 'a';
      }
      else
        return false;
    }
    else // Place ship going left as right will run out of bounds
    {
      for(int i = 0; i < shipLength; i++)
      {
        /* If we encounter a ship flag, invalid placement, return false */
        if(getFlag(x - i, y) == 'a')
        {
          placeOK = false;
          break;
        }
        else
          placeOK = true;
      }

      if(placeOK)
      {
        for(int i = 0; i < shipLength; i++)
          playingField[x - i][y] = 'a';
      }
      else
        return false;
    }
  }
}

/*
   Function: setGameTurn
   Sets who's turn it is
   
   Parameters:
      clientIndex  - The client number (0 for end-user, 1 for cpu)
*/
void setGameTurn(int clientIndex)
{
  gameTurn = clientIndex;
}

/*
   Function: setFlag
   Sets the specified co-ordinate to the specified flag
   
   Parameters:
      x            - Holds the X co-ordinate (randomly generated)
      y            - Holds the Y co-ordinate (randomly generated)
      flag         - Char of flag to set
*/
void setFlag(int x, int y, char flag)
{
  playingField[x][y] = flag;
}

/*
   Function: drawGameBoard
   Draws player boundaries and divider
   
   Parameters:
      x            - Holds the X co-ordinate to check for drawing
      y            - Holds the Y co-ordinate to check for drawing

   Returns:
      True if to draw to the coordinate specified via argument, false otherwise.
*/
bool drawGameBoard(int x, int y)
{
  /* If we have X values between 0 and 14, 17 and 31, or 15 or 16, draw */
  if((x > 0 && x < 14) || (x > 17 && x < 31) || (x == 15 || x == 16))
  {
    if(x == 15 || x == 16)
      return true;
      
    if(y > 0 && y < 13)
    {
      return true;
    }
    if(y == 14)
    {
      /* Only draw on Y = 14 if X is not between 8 and 23 */
      if(!(x > 8 && x < 23))
        return true;
    }
  }
  
  return false;
}

/*
   Function: drawWater
   Draws water for both players
   
   Parameters:
      x            - Holds the X co-ordinate to check for drawing
      y            - Holds the Y co-ordinate to check for drawing

   Returns:
      True if to draw to the coordinate specified via argument, false otherwise.
*/
bool drawWater(int x, int y)
{
  /* If x is between 1 and 13, or 18 and 30, and y is between 1 and 12, draw */
  if((x > 1 && x < 13) || (x > 18 && x < 30))
    if(y > 1 && y < 12)
      return true;

  return false;
}

/*
   Function: drawScore
   Draws player scores
   
   Parameters:
      clientIndex  - Client number of player (0 for end-user, 1 for CPU)
      x            - Holds the X co-ordinate to check for drawing
      y            - Holds the Y co-ordinate to check for drawing

   Returns:
      True if to draw to the coordinate specified via argument, false otherwise.
*/
bool drawScore(int clientIndex, int x, int y)
{
  /* If player, draw on the left */
  if((clientIndex == 0) && (x > 9 && x < 13) && (y > 12 && y < 16))
    if(!(x == 11 && y == 14))
      return true;

  /* If cpu, draw on the right */
  if((clientIndex == 1) && (x > 18 && x < 22) && (y > 12 && y < 16))
    if(!(x == 20 && y == 14))
      return true;

  /* Fallback procedure to return false */
  return false;
}

/*
   Function: checkHit
   Check co-ordinate for a hit via flags
   
   Parameters:
      clientIndex  - Client number of player (for scoring, will be implemented later)
      x            - Holds the X co-ordinate to check for drawing
      y            - Holds the Y co-ordinate to check for drawing

   Returns:
      True if flag at X and Y is 'a', false otherwise
*/
bool checkHit(int clientIndex, int x, int y)
{
 if(playingField[x][y] == 'a')
  return true; 
}

/*
   Function: checkButtonPushed
   Checks if a button is pushed using basic debouncing
   
   Parameters:
      state        - State to check for via digitalRead(pin)
      currentClock - Used for debouncing

   Returns:
      True if state is high and the clock is more than the previous clock + 300 milliseconds

   See Also:
      millis() [arduino]
*/
bool checkButtonPushed(int state, int currentClock)
{
  if(state && (currentClock > (buttonClock + 300)))
  {
    buttonClock = currentClock;
    return true;
  }
  else
  {
    return false;
  }
}

/*
   Function: getFlag
   Gets the flag at the specified co-ordinate
   
   Parameters:
      x            - Holds the X co-ordinate to check
      y            - Holds the Y co-ordinate to check

   Returns:
      Character of the flag
*/
char getFlag(int x, int y)
{
  return playingField[x][y];
}

