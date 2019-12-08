# Santa's Workshop

## Summary

"Santa's Workshop" is a 2D scrolling platformer, inspired by classic games such as Mario. The player is represented by a dot which is able to move and jump around the map. The map is made out of horizontal platforms.

## Story

While working hard to make presents for Christmas, the elves were careless and misplaced some toys in the workshop.
Your objective is to jump around and collect all the presents before Santa has to depart to deliver the presents.

Each level is a different room of Santa's Workshop, each more intricate than the previous one. And because Christmas is fast approaching, you will start with less time in later levels.

## Design

This section describes how this game satisfies the project's requirements.

### Hardware

#### Display / Output

- The game menu and messages are displayed on an **LCD display**.

- The map is displayed on a scrolling **8x8 LED matrix** driven by a **MAX7219 driver**

- The driver is chained to another one which drives a **four digit 7-segment display**,
  which will be used to display the **time remaining** in the level.

- **Buzzer** is used to generate simple tones when player collects a present, when time runs out, etc.

#### Input

- Primary input is through the **joystick**. The player can **move** around **left** and **right** and can **press** the joystick to **jump**.

- Possibly add a **switch** for turning game on or off.

### Scoring

- Player's **score** depends on **how many presents they collect**.
  Also, any extra time left is added with a multiplier to the score.

- The high score is _saved_ along with the player's name in the **EEPROM**.
  When the game ends, the player is shown their final score,
  and they can write their name and it gets saved with the score.

- Each level has a **limited time** in which the player must collect the presents.
  The player does not lose health points, but if they fall they **lose precious time**.

- **Multiple levels**: When the player finishes a level they unlock the next level which is harder.
  Each level is stored **in flash memory** as a 64x32 bit array (256 bytes).
  The locations of the presents are stored in arrays as x,y-coordinate pairs.
