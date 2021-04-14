#include <stdio.h>
#include <stdlib.h>

#define P(x) (((x)-1) / 2)
#define L(x) (((x)*1) + 1)
#define R(x) (((x)*1) + 2)
#define DEFAULT_CAP 10
#define IMPOSSIBLE -1

typedef struct AL AL;

struct AL
{
    int *arr;
    int size, cap;
};

// AL prototypes
AL *createAL();
void expandAL(AL *list);
void appendAL(AL *list, int value);
void deleteAL(AL *list);
void removeLastAL(AL *list);

// Heap prototypes
void percUp(AL *heap, int index);
void percDown(AL *heap, int index);
void insertHeap(AL *heap, int value);
void removeHeap(AL *heap);
int frontHeap(AL *heap);

int main()
{
    AL *heap = createAL();
    for (int i = 0; i < 20; ++i)
    {
        if (rand() % 100 < 80)
        {
            int value = rand() % 100;
            printf("Inserting %d...\n", value);
            insertHeap(heap, value);
        }
        else
        {
            printf("Removing...\n");
            removeHeap(heap);
        }
        printf("Top of the heap is %d.\n", frontHeap(heap));
    }
    deleteAL(heap);
    return 0;
}

// AL prototypes
AL *createAL()
{
    AL *ret = calloc(1, sizeof(AL));
    ret->size = 0;
    ret->cap = DEFAULT_CAP;
    ret->arr = calloc(ret->cap, sizeof(int));
    return ret;
}

void expandAL(AL *list)
{
    list->arr = realloc(list->arr, (list->cap *= 2) * sizeof(int));
}

void appendAL(AL *list, int value)
{
    if (list->size == list->cap)
    {
        expandAL(list);
    }
    list->arr[list->size++] = value;
}

void deleteAL(AL *list)
{
    free(list->arr);
    free(list);
}

void removeLastAL(AL *list)
{
    list->size--;
}

// Heap prototypes
void percUp(AL *heap, int index)
{
    // Base case : WE ARE ROOT!!!
    if (index == 0)
    {
        return;
    }

    if (heap->arr[index] < heap->arr[P(index)])
    {
        // swap
        int tmp = heap->arr[index];
        heap->arr[index] = heap->arr[P(index)];
        heap->arr[P(index)] = tmp;

        // continue percolation
        percUp(heap, P(index));
    }
}

void percDown(AL *heap, int index)
{
    // Base case : leaf
    if (L(index) >= heap->size)
    {
        return;
    }

    if (R(index) == heap->size)
    {
        // we have a left child
        if (heap->arr[index] > heap->arr[L(index)])
        {
            int tmp = heap->arr[index];
            heap->arr[index] = heap->arr[L(index)];
            heap->arr[L(index)] = tmp;
        }
        return;
    }

    int child = L(index);
    if (heap->arr[R(index)] < heap->arr[L(index)])
    {
        child = R(index);
    }
    if (heap->arr[index] > heap->arr[child])
    {
        // Swap
        int tmp = heap->arr[index];
        heap->arr[index] = heap->arr[child];
        heap->arr[child] = tmp;

        // Continue
        percDown(heap, child);
    }
}

void insertHeap(AL *heap, int value)
{
    appendAL(heap, value);
    percUp(heap, heap->size - 1);
}

void removeHeap(AL *heap)
{
    if (heap->size == 0)
    {
        return;
    }
    // move the last spot into the root
    heap->arr[0] = heap->arr[heap->size - 1];

    removeLastAL(heap);
    percDown(heap, 0);
}

int frontHeap(AL *heap)
{
    if (heap->size == 0)
    {
        return IMPOSSIBLE;
    }

    return heap->arr[0];
}