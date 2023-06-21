#ifndef aux_h
#define aux_h

// #define COL 10
// #define ROW 4
#define YES 1
#define NO 0

struct _cell{
    int parent_i, parent_j;
    int f, g, h;
};
typedef struct _cell cell;

struct _pair{
    int row;
    int col;
};
typedef struct _pair pair;

typedef struct{
    int elem;
    pair cell;
} heap_element;

typedef struct{
    heap_element *heap_elem;
    size_t cap;
    size_t n;
} heap;

size_t power2Cap(size_t cap);
heap newHeapCap(size_t cap);
void heapifyUp(heap *h, size_t pos);
void heapiFyDown(heap *h, size_t pos);
heap_element deleteMin(heap *h);
void insertHeap(heap *h, int e, int row, int col);
void printHeap(heap *h);

int cell_val (pair cell, pair gridDim);
int cell_block(int** grid, pair cell);
int dest_check(pair cell, pair dest);
int h_val(pair cell, pair dest);
void tracePath(cell** cellDetails, pair gridDim, pair dest);
int aStar(int** grid, pair gridDim, pair src, pair dest);

int processCell(pair cell_a, pair cell_b, pair src, pair dest, pair gridDim, int** grid, int** closedList, cell** cellDetails, heap* minheap);
void freeClosedList(int** closedList, int rows);
void freeCellDetails(cell** cellDetails, int rows);

void readGrid(const char* filename, int** grid, int width, int height);


#endif