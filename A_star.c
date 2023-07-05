#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <error.h>
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/prototypes.h"
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/aStar.h"
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/Heap.h"
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/grid.h"

int main(int argc, char **argv) {

    printf("\nA-star initialized\n");

    if (argc != 7) {
        printf("Uso: ./grid_maker.exe <width> <length> <src.row> <src.col> <dest.row> <dest.col>\n");
        return 1;
    }

    int width;
    int height;
    pair src, dest;

    sscanf(argv[1], "%d", &width);
    sscanf(argv[2], "%d", &height);
    sscanf(argv[3], "%d", &src.row);
    sscanf(argv[4], "%d", &src.col);
    sscanf(argv[5], "%d", &dest.row);
    sscanf(argv[6], "%d", &dest.col);

    pair gridDim;
    gridDim.col = width;
    gridDim.row = height;

    int** grid = allocateGrid(gridDim.row, gridDim.col);

    const char* filename = "D:/Desktop/PAR_scripts/router-dijkstra/gridCell.txt"; // File with grid

    // int width = gridDim.col;
    // int height = gridDim.row;

    readGrid(filename, grid, gridDim.col, gridDim.row);

    if (grid == NULL) {
        printf("grid null.\n");
        return 1;
    }
 
    // Source is the left-most bottom-most corner
    // pair src;
    // src.row = 0;
    // src.col = 0;
 
    // Destination is the left-most top-most corner
    // pair dest;
    // dest.row = 1250;
    // dest.col = 10;
    // dest.row = 0;
    // dest.col = 10;
 
    if(aStar(grid, gridDim, src, dest)!=0)
        printf("Error\n");


    freeGrid(grid, gridDim.row);

    return 0;
}