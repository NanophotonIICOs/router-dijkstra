#include <stdio.h>
#include <stdlib.h>

int main() {

    int width = 500;
    int height = 1350;
    int src_row = 0;
    int src_col = 0;
    int dest_row = 670;
    int dest_col = 5;

    char grid[100];
    char star[100];
    char router[100];

    sprintf(grid, "D:/Desktop/PAR_scripts/router-dijkstra/grid_maker.exe %d %d", width, height);
    sprintf(star, "D:/Desktop/PAR_scripts/router-dijkstra/A_star.exe %d %d %d %d %d %d", width, height, src_row, src_col, dest_row, dest_col);
    sprintf(router, "D:/Desktop/PAR_scripts/router-dijkstra/router.exe %d %d", width, height);

    system(grid);
    system(star);
    system(router);

    return 0;
}