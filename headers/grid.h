#ifndef grid_h
#define grid_h

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

void freeGrid_(Grid *grid) {
    for (int i = 0; i < grid->height; i++) {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

#endif