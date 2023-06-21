#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "aux_a.h"
#include "aStar.h"
#include "Heap.h"
#include <error.h>

int main() {

    pair gridDim;
    gridDim.row = 500;
    gridDim.col = 500;

    int** grid = allocateGrid(gridDim.row, gridDim.col);

    const char* filename = "./gridCell.txt";

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

    // int values[4][10] = {{ 1, 0, 1, 1, 0, 1, 1, 1, 0, 0 },
    //                      { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
    //                      { 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
    //                      { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 }};
    
    // // Copiar los valores a la matriz reservada
    // for (int i = 0; i < gridDim.row; i++) {
    //     for (int j = 0; j < gridDim.col; j++) {
    //         grid[i][j] = values[i][j];
    //     }
    // }


    // const char* filename = "./grid.txt";
    // FILE* file = fopen(filename, "w");
    // if (file == NULL) {
    //     printf("Error: No se pudo abrir el archivo.\n");
    //     return 1;
    // }

    // for (int i = 0; i < gridDim.row; i++) {
    //     for (int j = 0; j < gridDim.col; j++) {
    //         fprintf(file, "%d ", grid[i][j]);
    //     }
    //     fprintf(file, "\n");
    // }

    // fclose(file);