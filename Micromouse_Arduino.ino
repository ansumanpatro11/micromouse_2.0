#include "globals.h"
#include "treamux.h"
#include "Api.h"
const uint8_t rows = 5, cols = 5;

bool flag = 0;

struct cell PathArray[rows * cols]; // Define PathArray


// uint8_t targetCellsGoal[1] = {12},targetCellStart[1] = {20}, startCell = 20, startDir = 0;

uint8_t targetCellsGoal = 17, targetCellStart = 248, startCell = 20, startDir = 0;

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
