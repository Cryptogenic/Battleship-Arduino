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
};

/* Enumeration structures for flags for ship coordinates as well as buttons for
   button monitoring for player input */

enum ShipFlags
{
  FLAG_EMPTY = 1,
  FLAG_SHIP_OK = 2,
  FLAG_SHIP_HIT = 3
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
