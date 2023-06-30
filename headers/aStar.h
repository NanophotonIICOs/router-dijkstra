#ifndef astar_h
#define astar_h

// Función para validar celdas
int cell_val (pair cell, pair gridDim){
    if (cell.row>=0 && cell.row<gridDim.row && cell.col>=0 && cell.col<gridDim.col)
        return YES;
    else
        return NO;
}

// Función para validar grid
int cell_block(int** grid, pair cell){
    if (grid[cell.row][cell.col] == 1)
        return NO;
    else
        return YES;
}

int dest_check(pair cell, pair dest){
    if (cell.row == dest.row && cell.col == dest.col)
        return YES;
    else
        return NO;
}

int h_val(pair cell, pair dest){
    return fabs((cell.row - dest.row) + (cell.col - dest.col));
}

void tracePath(cell** cellDetails, pair gridDim, pair dest) {
    const char* filename = "D:/Desktop/PAR_scripts/router-dijkstra/path.txt";  // Nombre del archivo de salida

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo. (aStar.h/tracePath)\n");
        return;
    }
    
    int row = dest.row;
    int col = dest.col;

    int pathLength = 0;
    int path[gridDim.row * gridDim.col][2];

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        path[pathLength][0] = row;
        path[pathLength][1] = col;
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
        pathLength++;
    }

    path[pathLength][0] = row;
    path[pathLength][1] = col;
    pathLength++;

    printf("Path length: %d\n", pathLength);
    // printf("The Path is ");
    for (int i = pathLength - 1; i >= 0; i--) {
        // printf("-> (%d,%d) ", path[i][0], path[i][1]);
        fprintf(file, "%d, %d\n", path[i][0], path[i][1]);
    }
    // printf("\n\n");
    fclose(file);
}

int aStar(int** grid, pair gridDim, pair src, pair dest){
    if (cell_val(src, gridDim)==NO){
        printf("Invalid source!\n");
        return 1;
    }

    if (cell_val(dest, gridDim)==NO){
        printf("Invalid destination!\n");
        return 1;
    }

    if (cell_block(grid, src)==YES){
        printf("Source is blocked!\n");
        return 1;
    }

    if (cell_block(grid, dest)==YES){
        printf("Destination is blocked!\n");
        return 1;
    }

    int **closedList;
    closedList = (int **)calloc(gridDim.row, sizeof(int *));
    if (closedList == NULL) {
        printf("Error: No se pudo asignar memoria para las filas closedList\n");
        return 1;
    }
    for (int i = 0; i < gridDim.row; i++) {
        closedList[i] = (int *)calloc(gridDim.col, sizeof(int));
        if (closedList[i] == NULL) {
            printf("Error: No se pudo asignar memoria para las columnas closedList\n");
            return 1;
        }
    }

    cell **cellDetails;
    cellDetails = (cell **)malloc(gridDim.row * sizeof(cell *));
    if (cellDetails == NULL) {
        printf("Error: No se pudo asignar memoria para las filas closedList\n");
        return 1;
    }
    for (int i = 0; i < gridDim.row; i++) {
        cellDetails[i] = (cell *)malloc(gridDim.col * sizeof(cell));
        if (cellDetails[i] == NULL) {
            printf("Error: No se pudo asignar memoria para las columnas closedList\n");
            return 1;
        }
    }

    // Inicializar valores de grafo grid
    for(int i = 0; i < gridDim.row; i++){
        for(int j = 0; j < gridDim.col; j++){
            cellDetails[i][j].f = INT_MAX;
            cellDetails[i][j].g = INT_MAX;
            cellDetails[i][j].h = INT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Inicializar celda source
    cellDetails[src.row][src.col].f = 0;
    cellDetails[src.row][src.col].g = 0;
    cellDetails[src.row][src.col].h = 0;
    cellDetails[src.row][src.col].parent_i = src.row;
    cellDetails[src.row][src.col].parent_j = src.col;

    heap minheap;
    minheap = newHeapCap(100);
    heap_element elem;
    pair cell_a, cell_b;
    int ns, eo;

    int f = 0;
    insertHeap(&minheap, f, src.row, src.col);

    printf("Inicio de busqueda\n");
    while(minheap.n>0){
        elem = deleteMin(&minheap);
        cell_b.row = elem.cell.row;
        cell_b.col = elem.cell.col;
        closedList[elem.cell.row][elem.cell.col] = YES;

        // printf("\n Norte:\n");
        // Norte
        ns = -1;
        eo = 0;
        cell_a.row = cell_b.row + ns; // Celda norte
        cell_a.col = cell_b.col + eo; // Celda norte
        if(processCell(cell_a, cell_b, src, dest, gridDim, grid, closedList, cellDetails, &minheap))
            break;

        // printf("\n Sur:\n");
        // Sur
        ns = 1;
        eo = 0;
        cell_a.row = cell_b.row + ns; // Celda norte
        cell_a.col = cell_b.col + eo; // Celda norte
        if(processCell(cell_a, cell_b, src, dest, gridDim, grid, closedList, cellDetails, &minheap))
            break;

        // printf("\n Este:\n");
        // Este
        ns = 0;
        eo = 1;
        cell_a.row = cell_b.row + ns; // Celda norte
        cell_a.col = cell_b.col + eo; // Celda norte
        if(processCell(cell_a, cell_b, src, dest, gridDim, grid, closedList, cellDetails, &minheap))
            break;

        // printf("\n Oeste:\n");
        // Oeste
        ns = 0;
        eo = -1;
        cell_a.row = cell_b.row + ns; // Celda norte
        cell_a.col = cell_b.col + eo; // Celda norte
        if(processCell(cell_a, cell_b, src, dest, gridDim, grid, closedList, cellDetails, &minheap))
            break;
    }

    printf("Fin de busqueda\n");
    printf("minHeap length: %d\n", minheap.n);
    // printf("minHeap /f (x, y)/: ");
    // printHeap(&minheap);

    freeClosedList(closedList, gridDim.row);
    freeCellDetails(cellDetails, gridDim.row);

    return 0;
}

int processCell(pair cell_a, pair cell_b, pair src, pair dest, pair gridDim, int** grid, int** closedList, cell** cellDetails, heap* minheap) {
    if(cell_val (cell_a, gridDim)){
        // printf("Celda cell_a valida\n"); // DEBUG
        if (dest_check(cell_a, dest)) {
            // printf("Si es destino\n"); // DEBUG
            cellDetails[cell_a.row][cell_a.col].parent_i = cell_b.row;
            cellDetails[cell_a.row][cell_a.col].parent_j = cell_b.col;
            tracePath(cellDetails, gridDim, dest);
            return 1;
        } else if (closedList[cell_a.row][cell_a.col] == NO && cell_block(grid, cell_a) == NO) {
            // printf("No es destino\n"); // DEBUG
            // printf("No esta cerrada\n"); // DEBUG
            // printf("No esta bloqueada\n"); // DEBUG
            int gNew = cellDetails[cell_b.row][cell_b.col].g + 1;
            int hNew = h_val(cell_a, dest);
            int fNew = gNew + hNew;
            // printf("%d + %d = %d\n", gNew, hNew, fNew); // DEBUG

            if (cellDetails[cell_a.row][cell_a.col].f == INT_MAX || cellDetails[cell_a.row][cell_a.col].f > fNew) {
                insertHeap(minheap, fNew, cell_a.row, cell_a.col);
                cellDetails[cell_a.row][cell_a.col].f = fNew;
                cellDetails[cell_a.row][cell_a.col].g = gNew;
                cellDetails[cell_a.row][cell_a.col].h = hNew;
                cellDetails[cell_a.row][cell_a.col].parent_i = cell_b.row;
                cellDetails[cell_a.row][cell_a.col].parent_j = cell_b.col;
            }
        } else {
            // printf("Celda cerrada o bloqueada\n"); // DEBUG
        }
    } else {
    // printf("no valida\n"); // DEBUG
    }
    return 0;
}

int** allocateGrid(int row, int col) {
    int** grid;
    grid = (int**)malloc(row * sizeof(int*));
    if (grid == NULL) {
        printf("Error: No se pudo asignar memoria para las filas\n");
        return NULL;
    }
    for (int i = 0; i < row; i++) {
        grid[i] = (int*)malloc(col * sizeof(int));
        if (grid[i] == NULL) {
            printf("Error: No se pudo asignar memoria para las columnas\n");
            return NULL;
        }
    }
    return grid;
}

void freeGrid(int** grid, int row) {
    for (int i = 0; i < row; i++) {
        free(grid[i]);
    }
    free(grid);
}

void freeClosedList(int** closedList, int rows) {
    for (int i = 0; i < rows; i++) {
        free(closedList[i]);
    }
    free(closedList);
}

void freeCellDetails(cell** cellDetails, int rows) {
    for (int i = 0; i < rows; i++) {
        free(cellDetails[i]);
    }
    free(cellDetails);
}

void readGrid(const char* filename, int** grid, int width, int height) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Errno %d \n", errno);
        printf("It's null (aStar.h/readGrid)\n");
        exit(1);
    } else {
        printf("Grid file open.\n");
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (fscanf(file, "%d", &grid[i][j]) != 1) {
                printf("Error al leer el valor en la posición (%d, %d).\n", i, j);
                fclose(file);
                return;
            }
        }
    }

    printf("Grid creada\n");
    fclose(file);
}


#endif