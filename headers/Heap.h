#ifndef heap_h
#define heap_h

size_t power2Cap(size_t cap){
    return 128;
}

//Function to create a new heap
heap newHeapCap(size_t cap){
    heap el_heap;
    el_heap.cap = power2Cap(cap) - 1;
    el_heap.heap_elem = malloc(sizeof(heap_element)*(el_heap.cap+1));
    if(el_heap.heap_elem == NULL){
        fprintf(stderr, "Error al reservar memoria para el heap.\n");
        exit(1);
    }
    el_heap.heap_elem[0].elem = 0;
    for(size_t i = 1; i <= el_heap.cap; i++){
        el_heap.heap_elem[i].elem = INT_MAX;
        el_heap.heap_elem[i].cell.row = 0;
        el_heap.heap_elem[i].cell.col = 0;
    }
    el_heap.n = 0;
    return el_heap;
}

static inline size_t parent(size_t pos){
    return pos >> 1;
}

static inline size_t left_child(size_t pos){
    return pos << 1;
}

static inline size_t right_child(size_t pos){
    return (pos << 1) + 1;
}

//Function to heapify up the heap
void heapifyUp(heap *h, size_t pos){
    size_t my_parent = parent(pos); //Parent of the element
    while(h->heap_elem[pos].elem < h->heap_elem[my_parent].elem){
        heap_element aux = h->heap_elem[pos]; //Auxiliar element
        h->heap_elem[pos] = h->heap_elem[my_parent]; //Swap the elements
        h->heap_elem[my_parent] = aux; //Swap the elements
        pos = my_parent; //Update the position
        my_parent = parent(pos); //Update the parent
    }
}

//Function to heapify down the heap
void heapiFyDown(heap *h, size_t pos){
    while(1){
        if(left_child(pos) > h->cap)
            return;
        size_t left = left_child(pos);
        size_t right = right_child(pos);
        size_t el_menor = h->heap_elem[left].elem < h->heap_elem[right].elem ? left : right;
        if(h->heap_elem[pos].elem > h->heap_elem[el_menor].elem){
            heap_element aux = h->heap_elem[pos];
            h->heap_elem[pos] = h->heap_elem[el_menor];
            h->heap_elem[el_menor] = aux;
            pos = el_menor;
        }
        else
            return;
    }
}

//Function to delete the minimum element in the heap
heap_element deleteMin(heap *h){
    heap_element returnValue = h->heap_elem[1];
    h->heap_elem[1] = h->heap_elem[h->n];
    h->heap_elem[h->n].elem = INT_MAX;
    heapiFyDown(h, 1);
    h->n--;
    return returnValue;
}

//Function to insert an element in the heap
void insertHeap(heap *h, int e, int row, int col){
    if(h->n >= h->cap){
        size_t newCap = ((h->cap + 1) << 1) - 1;
        h->heap_elem = realloc(h->heap_elem, sizeof(heap_element)*(newCap + 1));
        if(h->heap_elem == NULL){
            fprintf(stderr, "No se pudo aumentar el heap\n");
            exit(1);
        }
        h->cap = newCap;
        for(size_t i = h->n + 1; i < h->cap + 1; i++){
            h->heap_elem[i].elem = INT_MAX;
        }
    }
    h->heap_elem[h->n + 1].elem = e;
    h->heap_elem[h->n + 1].cell.row = row;
    h->heap_elem[h->n + 1].cell.col = col;
    h->n++;
    heapifyUp(h, h->n);
}

//Function to print the heap
void printHeap(heap *h){
    for(size_t i = 1; i < h->n+1; i++)
        printf(" /%d (%d, %d)/ ", h->heap_elem[i].elem, h->heap_elem[i].cell.row, h->heap_elem[i].cell.col);
    printf("\n");
}


#endif