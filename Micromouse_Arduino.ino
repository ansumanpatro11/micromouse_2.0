#include "globals.h"
#include "treamux.h"
#include "Api.h"
const uint8_t rows = 16, cols = 16;

bool flag = 0;
struct cell floodArray[rows * cols];

// uint8_t targetCellsGoal[1] = {12},targetCellStart[1] = {20}, startCell = 20, startDir = 0;

uint8_t targetCellsGoal = 15, targetCellStart = 248, startCell = 248, startDir = 0;

int sensorValue[4];

void setup() {
  Serial.begin(19200);

  // log("Starting....");
  initialise();
}


void loop() {



    if(currentCell != targetCellsGoal) {
      updateWalls();
      treamux();
      updateTargetCell();
      goToTargetCell();
     }
    else{
      stop();
    }

    





}