#ifndef STRUCTURES_H
#define STRUCTURES_H

/* Player structure holds all information for the given player including the
   next turn, score, and all the ship positions and their flags (int arrays
   hold coordinates (x, y) and the value is it's flag). Flags and values can be
   found in the "Flag" enumeration structure in the bottom of Structures.h */

struct player_s
{
  bool nextTurn;
  int score;
  int grid[8][8];
};

struct game_s
{
  int gameBoard[32][16];
};

/* Enumeration structures for flags for ship coordinates as well as buttons for
   button monitoring for player input */

enum GridFlags
{
  FLAG_GRID_RED,
  FLAG_GRID_GREEN,
  FLAG_GRID_BLUE,
  FLAG_GRID_WHITE,
  FLAG_GRID_BLACK
};

enum ShipFlags
{
  FLAG_EMPTY,
  FLAG_SHIP_OK,
  FLAG_SHIP_HIT
};

enum Buttons
{
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_KEFT,
  BUTTON_RIGHT,
  BUTTON_FIRE
};

#endif
