#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/prototypes.h"
#include "D:/Desktop/PAR_scripts/router-dijkstra/headers/grid.h"

int main(int argc, char **argv) {

    printf("\nGrid Maker initialized\n");

    if (argc != 3) {
        printf("Uso: ./grid_maker.exe <width> <length>\n");
        return 1;
    }

    int width;
    int height;

    sscanf(argv[1], "%d", &width);
    sscanf(argv[2], "%d", &height);

    printf("width: %d, height: %d\n", width, height);

    Grid grid;
    initializeGrid(&grid, width, height);

    FILE *file = fopen("D:/Desktop/PAR_scripts/router-dijkstra/amis_cells/cell_inv.txt", "r"); // File containing the macros
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo de las celdas.\n");
        return 1;
    }

    char line[100];
    char *celda = "inv1_b"; // Cell to search
    char macro[100];

    while (fgets(line, sizeof(line), file)) {
        sprintf(macro, "MACRO: %s", celda);
        if (strstr(line, macro) != NULL) {
            printf(macro); // DEBUG
        } else if (strstr(line, "RECT") != NULL) {
            // printf("Rect\n"); // DEBUG
            int rectNumber, flag;
            float x1, y1, x2, y2;
            sscanf(line, "RECT %d, %d: %f, %f - %f, %f", &rectNumber, &flag, &x1, &y1, &x2, &y2);

            // Multiply coordinates by 100 to represent them as integers
            Rectangle rectangle = {(int)(x1 * 100), (int)(y1 * 100), (int)(x2 * 100), (int)(y2 * 100)}; // El primer punto tiene que ser menor
            // Rectangle rectangle = {(int)(x1), (int)(y1), (int)(x2), (int)(y2)}; // DEBUG
            insertMacro(&grid, rectangle);
        } else if (strstr(line, "END") != NULL) {
            // Reached END line, stop reading
            break;
        }
    }

    fclose(file);

    // printGrid(&grid); // DEBUG
    saveGrid("D:/Desktop/PAR_scripts/router-dijkstra/gridCell.txt", &grid);

    freeGrid_(&grid);

    return 0;
}
