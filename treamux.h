#ifndef treamux_h
#define treamux_h
#include "Api.h"

void turn(int angle, int speed);
int moveForward(int blocks);

#define linearise(row, col) (row* cols + col)
#define delineariseRow(location) (location / cols)
#define delineariseCol(location) (location % cols)

// Wall macros
#define distance(loc1, loc2) (absolute(delineariseRow(loc1) - delineariseRow(loc2)) + absolute(delineariseCol(loc1) - delineariseCol(loc2)))
#define wallExists(location, direction) (PathArray[location].neighbours & (1 << direction))
#define markWall(location, direction) (PathArray[location].neighbours |= 1 << direction)

// Neighbour macros
#define getNeighbourLocation(location, direction) ((uint8_t)((short)location + cellDirectionAddition[direction]))  // Calculates the location of neighbour
#define getNeighbourDistanceIfAccessible(location, direction) (PathArray[getNeighbourLocation(location, direction)].PathArray)
#define getNeighbourDistance(location, direction) (wallExists(location, direction) ? 255 : getNeighbourDistanceIfAccessible(location, direction))

// Direction macros
#define updateDirection(currentDirection, turn) *currentDirection = (*currentDirection + turn) % 4  // Updates the passed direction



void treamux();
void updateTargetCell();
void goToTargetCell();
void updateWalls();
void initialise();

#endif