#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 500
#define HEIGHT 500

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

typedef struct {
    int **grid;
    int width;
    int height;
} Grid;

void initializeGrid(Grid *grid, int width, int height) {
    grid->width = width;
    grid->height = height;

    grid->grid = (int **)malloc(sizeof(int *) * grid->height);
    for (int i = 0; i < grid->height; i++) {
        grid->grid[i] = (int *)malloc(sizeof(int) * grid->width);
        for (int j = 0; j < grid->width; j++) {
            grid->grid[i][j] = 1; // Todo el espacio disponible para routear
        }
    }
}

void insertMacro(Grid *grid, Rectangle rectangle) {
    for (int i = rectangle.y1; i <= rectangle.y2; i++) {
        for (int j = rectangle.x1; j <= rectangle.x2; j++) {
            if (i >= 0 && i < grid->height && j >= 0 && j < grid->width) {
                grid->grid[i][j] = 0; // Bloquear celdas en el area de m1
            }
        }
    }
}

void printGrid(Grid *grid) {
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            printf("%d ", grid->grid[i][j]);
        }
        printf("\n");
    }
}

void saveGrid(const char* filename, const Grid* grid) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo para guardar la grid.\n");
        return;
    }

    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            int cell = grid->grid[y][x];
            fprintf(file, "%d ", cell);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void freeGrid(Grid *grid) {
    for (int i = 0; i < grid->height; i++) {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

int main() {

    Grid grid;
    initializeGrid(&grid, WIDTH, HEIGHT);

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

    freeGrid(&grid);

    return 0;
}
