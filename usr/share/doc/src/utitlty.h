#ifndef UTILITY_H
#define UTILITY_H
#include<../../my-learnig-path-/data_structure/mini_heap.h>


typedef struct {
    int row,col;
    int scr;
    int size;
    int capacity;
}Heap;
int createHeap(Heap* heap,int v);
int insert(Heap* heap,int row,int col,int src);
void swap(int* a,int* b);
void heapify(Heap* heap,int i);
int extractMin(Heap* heap);




#endif // UTILITY_H
