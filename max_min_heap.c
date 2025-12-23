#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int capacity;
    int size;
} Heap;

Heap* createHeap(int capacity) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (int *)malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

int parent(int i) { return (i - 1) / 2; }
int leftChild(int i) { return 2 * i + 1; }
int rightChild(int i) { return 2 * i + 2; }

void swapMaxHeap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapifyDown(Heap *heap, int i) {
    int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);
    
    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;
    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;
    
    if (largest != i) {
        swapMaxHeap(&heap->data[i], &heap->data[largest]);
        maxHeapifyDown(heap, largest);
    }
}

void maxHeapifyUp(Heap *heap, int i) {
    while (i > 0 && heap->data[parent(i)] < heap->data[i]) {
        swapMaxHeap(&heap->data[i], &heap->data[parent(i)]);
        i = parent(i);
    }
}

void minHeapifyDown(Heap *heap, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);
    
    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;
    
    if (smallest != i) {
        swapMaxHeap(&heap->data[i], &heap->data[smallest]);
        minHeapifyDown(heap, smallest);
    }
}

void minHeapifyUp(Heap *heap, int i) {
    while (i > 0 && heap->data[parent(i)] > heap->data[i]) {
        swapMaxHeap(&heap->data[i], &heap->data[parent(i)]);
        i = parent(i);
    }
}

void insertMaxHeap(Heap *heap, int value) {
    if (heap->size >= heap->capacity) return;
    heap->data[heap->size] = value;
    maxHeapifyUp(heap, heap->size);
    heap->size++;
}

void insertMinHeap(Heap *heap, int value) {
    if (heap->size >= heap->capacity) return;
    heap->data[heap->size] = value;
    minHeapifyUp(heap, heap->size);
    heap->size++;
}

int extractMaxHeap(Heap *heap) {
    if (heap->size == 0) return -1;
    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    maxHeapifyDown(heap, 0);
    return max;
}

int extractMinHeap(Heap *heap) {
    if (heap->size == 0) return -1;
    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapifyDown(heap, 0);
    return min;
}

void displayHeap(Heap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main() {
    printf("=== MAX HEAP ===\n");
    Heap *maxHeap = createHeap(10);
    
    int values[] = {10, 20, 15, 40, 50, 30};
    for (int i = 0; i < 6; i++) {
        insertMaxHeap(maxHeap, values[i]);
    }
    
    printf("Max Heap: ");
    displayHeap(maxHeap);
    printf("En büyük eleman: %d\n", extractMaxHeap(maxHeap));
    printf("Sonrası: ");
    displayHeap(maxHeap);
    
    printf("\n=== MIN HEAP ===\n");
    Heap *minHeap = createHeap(10);
    
    for (int i = 0; i < 6; i++) {
        insertMinHeap(minHeap, values[i]);
    }
    
    printf("Min Heap: ");
    displayHeap(minHeap);
    printf("En küçük eleman: %d\n", extractMinHeap(minHeap));
    printf("Sonrası: ");
    displayHeap(minHeap);
    
    free(maxHeap->data);
    free(maxHeap);
    free(minHeap->data);
    free(minHeap);
    
    return 0;
}