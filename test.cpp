#include <iostream>
#include <vector>

using namespace std;

const uint8_t north = 0, east = 1, south = 2, west = 3;
const int rows = 5;
const int cols = 5;
uint8_t currentCell, targetCell;
uint8_t currentDir, leftDir, rightDir, nextLeftDir, nextDir, nextRightDir;
uint8_t distanceFromTarget = 1;
short cellDirectionAddition[4] = { -rows, 1, rows, -1 };
uint8_t readingCellLoc, readingCellDistance, readingCellScore, minNeighbourDistance, targetRelativeDirection, targetScore, neighbourCellLoc;

// Simplified PathArray structure
struct Cell {
    uint8_t visited = 0;  // To track the number of visits (for Tremaux algorithm)
    bool walls[4] = { false, false, false, false };  // Walls for each direction (N, E, S, W)
};

Cell maze[rows * cols];

// Function to get a neighboring cell's location based on direction
uint8_t getNeighbourLocation(uint8_t location, uint8_t direction) {
    return location + cellDirectionAddition[direction];
}

// Function to check if a wall exists
bool wallExists(uint8_t location, uint8_t direction) {
    return maze[location].walls[direction];
}

// Mark a wall between current and neighboring cell
void markWall(uint8_t location, uint8_t direction) {
    maze[location].walls[direction] = true;
}

// Simulate the robot turning
void turnLeft() {
    currentDir = (currentDir + 3) % 4;
}

void turnRight() {
    currentDir = (currentDir + 1) % 4;
}

// Move the robot forward
void moveForward() {
    currentCell = getNeighbourLocation(currentCell, currentDir);
}

// Check if the current cell is a dead-end
bool isDeadEnd(uint8_t location) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (wallExists(location, i)) count++;
    }
    return count == 3;
}

// Check if the current cell is a junction
bool isJunction(uint8_t location) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (wallExists(location, i)) count++;
    }
    return count < 2;
}

// Get the absolute direction to the target
uint8_t getTargetAbsoluteDirection(uint8_t target) {
    int diff = target - currentCell;
    if (diff == -rows) return north;
    if (diff == 1) return east;
    if (diff == rows) return south;
    if (diff == -1) return west;
    return 0;
}

// Get the relative direction from current cell to target
uint8_t getTargetRelativeDirection(uint8_t target) {
    return (getTargetAbsoluteDirection(target) + 4 - currentDir) % 4;
}

// Update direction variables (left, right, etc.) based on relative direction
void updateDirection(uint8_t *dir, uint8_t targetRelativeDirection) {
    *dir = targetRelativeDirection;
}

// Tremaux Algorithm Implementation
void treamux() {
    if (isDeadEnd(currentCell)) {
        maze[currentCell].visited = 2;  // Mark dead-end
        targetRelativeDirection = south;  // Backtrack
    } 
    else if (isJunction(currentCell)) {
        if (maze[currentCell].visited == 0) {
            maze[currentCell].visited = 1;  // First visit to the junction
            for (int i = 0; i < 4; i++) {
                if (!wallExists(currentCell, i)) {
                    uint8_t neighbor = getNeighbourLocation(currentCell, i);
                    if (maze[neighbor].visited == 0) {
                        targetCell = neighbor;
                        break;
                    }
                }
            }
        } 
        else if (maze[currentCell].visited == 1 && maze[getNeighbourLocation(currentCell, (currentDir + 2) % 4)].visited == 1) {
            // Backtrack from junction when there is no unvisited path
            targetRelativeDirection = south;
        } 
        else {
            // Find the neighbor with the fewest visits
            uint8_t minVisitedValue = 255;
            for (int i = 0; i < 4; i++) {
                if (!wallExists(currentCell, i)) {
                    uint8_t neighbor = getNeighbourLocation(currentCell, i);
                    if (maze[neighbor].visited < minVisitedValue) {
                        minVisitedValue = maze[neighbor].visited;
                        targetCell = neighbor;
                    }
                }
            }
        }
    } 
    else {
        // Regular movement, increase visit count
        maze[currentCell].visited++;
    }
}

// Move the robot toward the target cell
void goToTargetCell() {
    uint8_t targetRelativeDirection = getTargetRelativeDirection(targetCell);
    if (targetRelativeDirection == north) {
        // No need to turn, already facing north
    } else if (targetRelativeDirection == east) {
        turnRight();
    } else if (targetRelativeDirection == south) {
        turnRight();
        turnRight();
    } else if (targetRelativeDirection == west) {
        turnLeft();
    }
    moveForward();  // Move the robot forward
}

// Initialize the maze, starting cell, and direction
void initialize() {
    currentCell = 0;  // Start at top-left corner (0,0)
    currentDir = north;  // Facing north
    targetCell = currentCell;
    // Setup walls (example maze structure)
    maze[1].walls[east] = true;
    maze[2].walls[west] = true;
    maze[7].walls[east] = true;
    maze[8].walls[west] = true;
}

// Display the current state of the maze
void printMazeState() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int index = r * cols + c;
            if (index == currentCell) {
                cout << " R ";  // Robot's current position
            } else if (maze[index].visited > 0) {
                cout << " . ";  // Visited cell
            } else {
                cout << "   ";  // Unvisited cell
            }
        }
        cout << endl;
    }
}

int main() {
    initialize();
    while (currentCell != rows * cols - 1) {  // Loop until the robot reaches the end
        printMazeState();  // Show the maze before each move
        treamux();
        goToTargetCell();  // Move towards the target cell
    }
    cout << "Maze solved!" << endl;
    return 0;
}
