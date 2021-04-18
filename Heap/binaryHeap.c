/* 
sourced from https://www.geeksforgeeks.org/binary-heap/ for practice

A binary  heap is a tree with the following properties:
1. complete tree(all levels completely filled,  last level left 
   justified). makes binary heaps suitable to be stored in arrays
2. Binary heap is either min heap or max heap. In min heap, root 
   must be min among all nodes(recursively). In max heap, root > all 
   children(recursively).

Of Note:
    arr[(i - 1) / 2] returns parent node of ith node
    arr[(2 * i) + 1] returns the left child of ith node
    arr[(2 * i) + 2] returns the right child of ith node

Applications:
    - Heap sort:  uses binheap to sort an array in O(nlog(n)) time
    - Prio Q
    - Graph Algos: Esp. useful in Dijkstra's Algo and Prim's Min Span
    - Solving many generalized problems:
        a. k'th largest element in an array.
        b. Sort an almost sorted array
        c. merge k sorted arrays(unions are easy with binheap)

Operations on minHeap:
    - getMin(): returns the root element of min heap. Time Comp = O(1)
    - extractMin(): Remove the min from minHeap. Time Comp = O(log(n))
            Needs to heapify() resulting tree after removal to maintain.
    - decreaseKey(): decrases value of key. Time Comp = O(log(n)). If 
            adjusted value > parent value, fix tree. Otherwise, leave.
    - insert(): Time Comp = O(log(n)). Added at end of tree. then heapify()
            to fix the tree.
    - delete(): Time Comp = O(log(n)). Replace the key to be deleted 
            with min 
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Heap Heap;

struct Heap
{
    int *srcArr;
    int cap;
    int size;
};

void swap(int *x, int *y);
int parent(Heap *heap, int index);
int left(Heap *heap, int index);
int right(Heap *heap, int index);
int extractMin(Heap *heap);
void decreaseKey(Heap *heap, int value, int newValue);
int getMin(Heap *heap);
void deleteKey(Heap *heap, int value);
void insertKey(Heap *heap, int newValue);
Heap *createHeap(int cap);
void heapify(Heap *heap, int value);

int main()
{
    Heap *heap = createHeap(20);
    insertKey(heap, 3);
    insertKey(heap, 2);
    deleteKey(heap, 1);
    insertKey(heap, 15);
    insertKey(heap, 5);
    insertKey(heap, 4);
    insertKey(heap, 45);

    printf("%d ", extractMin(heap));
    printf("%d ", getMin(heap));
    decreaseKey(heap, 2, 1);
    printf("%d", getMin(heap));
    return 0;
}

Heap *createHeap(int cap)
{
    Heap *ret = malloc(1 * sizeof(Heap));
    ret->srcArr = calloc(cap, sizeof(int));
    ret->cap = cap;
    ret->size = 0;

    return ret;
}

void swap(int *x, int *y)
{
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

int parent(Heap *heap, int index)
{
    return (index - 1) / 2;
}

int left(Heap *heap, int index)
{
    return (2 * index) + 1;
}

int right(Heap *heap, int index)
{
    return (2 * index) + 2;
}

int extractMin(Heap *heap)
{
    if (heap->size <= 0)
        return INT_MAX;
    if (heap->size == 1)
    {
        heap->size--;
        return heap->srcArr[0];
    }

    // Store the min value, and remove it from heap
    int root = heap->srcArr[0];
    heap->srcArr[0] = heap->srcArr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

void decreaseKey(Heap *heap, int value, int newValue)
{
    heap->srcArr[value] = newValue;
    while (value != 0 && heap->srcArr[parent(heap, value)] > heap->srcArr[value])
    {
        swap(&heap->srcArr[value], &heap->srcArr[parent(heap, value)]);
        value = parent(heap, value);
    }
}

int getMin(Heap *heap)
{
    return heap->srcArr[0];
}

void deleteKey(Heap *heap, int value)
{
    decreaseKey(heap, value, INT_MIN);
    extractMin(heap);
}

void insertKey(Heap *heap, int newValue)
{
    if (heap->size == heap->cap)
    {
        printf("\nOverflow: could not insertKey\n");
        return;
    }

    // First insert the new key at the end
    heap->size++;
    int i = heap->size - 1;
    heap->srcArr[i] = newValue;

    // Fix the min heap property if it is violated
    while (i != 0 && heap->srcArr[parent(heap, i)] > heap->srcArr[i])
    {
        swap(&heap->srcArr[i], &heap->srcArr[parent(heap, i)]);
        i = parent(heap, i);
    }
}

void heapify(Heap *heap, int index)
{
    int leftChild = left(heap, index);
    int rightChild = right(heap, index);

    int smallest = index;

    if (leftChild < heap->size && heap->srcArr[leftChild] < heap->srcArr[index])
    {
        smallest = leftChild;
    }
    if (rightChild < heap->size && heap->srcArr[rightChild] < heap->srcArr[smallest])
    {
        smallest = rightChild;
    }
    if (smallest != index)
    {
        swap(&heap->srcArr[index], &heap->srcArr[smallest]);
        heapify(heap, smallest);
    }
}