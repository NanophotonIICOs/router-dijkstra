#include <stdio.h>
#include <stdlib.h>

int main() {

    int width = 500;
    int height = 540;

    char grid[100];
    char star[100];
    char router[100];

    sprintf(grid, "D:/Desktop/PAR_scripts/router-dijkstra/grid_maker.exe %d %d", width, height);
    sprintf(star, "D:/Desktop/PAR_scripts/router-dijkstra/A_star.exe %d %d 5 5 9 10", width, height);
    sprintf(router, "D:/Desktop/PAR_scripts/router-dijkstra/router.exe %d %d", width, height);

    system(grid);
    system(star);
    system(router);

    return 0;
}