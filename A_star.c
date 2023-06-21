#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <error.h>
#include "./headers/prototypes.h"
#include "./headers/aStar.h"
#include "./headers/Heap.h"

int main() {

    pair gridDim;
    gridDim.row = 500;
    gridDim.col = 500;

    int** grid = allocateGrid(gridDim.row, gridDim.col);

    const char* filename = "./gridCells.txt"; // File with grid

    int width = gridDim.row;
    int height = gridDim.col;

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