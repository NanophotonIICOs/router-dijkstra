#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <error.h>
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/prototypes.h"
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/aStar.h"
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/Heap.h"

int main() {

    pair gridDim;
    gridDim.row = 500;
    gridDim.col = 500;

    int** grid = allocateGrid(gridDim.row, gridDim.col);

    const char* filename = "D:/Desktop/PAR_scripts/router-dijkstra/gridCell.txt"; // File with grid

    int width = gridDim.col;
    int height = gridDim.row;

    readGrid(filename, grid, width, height);

    if (grid == NULL) {
        printf("grid null.\n");
        return 1;
    }
 
    // Source is the left-most bottom-most corner
    pair src;
    src.row = 0;
    src.col = 0;
 
    // Destination is the left-most top-most corner
    pair dest;
    dest.row = 0;
    dest.col = 10;
 
    if(aStar(grid, gridDim, src, dest)!=0)
        printf("Error\n");


    freeGrid(grid, gridDim.row);

    return 0;
}