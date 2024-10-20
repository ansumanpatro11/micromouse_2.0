#include "globals.h"
#include "treamux.h"
#include "Api.h"
// const uint8_t rows = 5, cols = 5;
const uint8_t rows = 16, cols = 16;

bool flag = 0;

struct cell PathArray[rows * cols]; // Define PathArray

// uint8_t targetCellsGoal[1] = {12},targetCellStart[1] = {20}, startCell = 20, startDir = 0;

// uint8_t targetCellsGoal = 18, targetCellStart = 20, startCell = 20, startDir = 0;
uint8_t targetCellsGoal = 223, targetCellStart = 239, startCell = 240, startDir = 0;

int sensorValue[4];

void setup() {
  Serial.begin(19200);

  log("Starting....");
  initialise();
}


void loop() {

    if(currentCell != targetCellsGoal) {
      updateWalls();
      treamux();
      
      log(String(currentCell));
      // updateTargetCell();
      goToTargetCell();
     }
    else{
      stop();
    }

}
