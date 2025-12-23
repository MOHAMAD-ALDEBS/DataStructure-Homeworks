#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} Array;

Array* createArray() {
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->size = 0;
    return arr;
}

void insertAtBegin(Array *arr, int value) {
    if (arr->size >= MAX_SIZE) {
        printf("Array dolu!\n");
        return;
    }
    
    for (int i = arr->size; i > 0; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[0] = value;
    arr->size++;
    printf("%d başa eklendi.\n", value);
}

void insertAtEnd(Array *arr, int value) {
    if (arr->size >= MAX_SIZE) {
        printf("Array dolu!\n");
        return;
    }
    
    arr->data[arr->size] = value;
    arr->size++;
    printf("%d sona eklendi.\n", value);
}

void insertAtPosition(Array *arr, int value, int pos) {
    if (arr->size >= MAX_SIZE) {
        printf("Array dolu!\n");
        return;
    }
    if (pos < 0 || pos > arr->size) {
        printf("Geçersiz pozisyon!\n");
        return;
    }
    
    for (int i = arr->size; i > pos; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[pos] = value;
    arr->size++;
    printf("%d indeks %d'ye eklendi.\n", value, pos);
}

void deleteFromBegin(Array *arr) {
    if (arr->size == 0) {
        printf("Array boş!\n");
        return;
    }
    
    int deleted = arr->data[0];
    for (int i = 0; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    printf("%d baştan silindi.\n", deleted);
}

void deleteFromEnd(Array *arr) {
    if (arr->size == 0) {
        printf("Array boş!\n");
        return;
    }
    
    int deleted = arr->data[arr->size - 1];
    arr->size--;
    printf("%d sondan silindi.\n", deleted);
}

void deleteAtPosition(Array *arr, int pos) {
    if (arr->size == 0) {
        printf("Array boş!\n");
        return;
    }
    if (pos < 0 || pos >= arr->size) {
        printf("Geçersiz pozisyon!\n");
        return;
    }
    
    int deleted = arr->data[pos];
    for (int i = pos; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    printf("%d indeks %d'den silindi.\n", deleted, pos);
}

void deleteByValue(Array *arr, int value) {
    int found = 0;
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            for (int j = i; j < arr->size - 1; j++) {
                arr->data[j] = arr->data[j + 1];
            }
            arr->size--;
            found = 1;
            printf("%d değeri silindi.\n", value);
            break;
        }
    }
    if (!found) {
        printf("%d değeri bulunamadı!\n", value);
    }
}

void display(Array *arr) {
    printf("Array: [");
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) printf(", ");
    }
    printf("] (Boyut: %d)\n", arr->size);
}

int search(Array *arr, int value) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            return i;
        }
    }
    return -1;
}

void freeArray(Array *arr) {
    free(arr);
}

int main() {
    Array *arr = createArray();
    
    insertAtEnd(arr, 10);
    insertAtEnd(arr, 20);
    insertAtEnd(arr, 30);
    display(arr);
    
    insertAtBegin(arr, 5);
    display(arr);
    
    insertAtPosition(arr, 15, 2);
    display(arr);
    
    deleteFromBegin(arr);
    display(arr);
    
    deleteFromEnd(arr);
    display(arr);
    
    deleteAtPosition(arr, 1);
    display(arr);
    
    deleteByValue(arr, 15);
    display(arr);
    
    int pos = search(arr, 20);
    if (pos != -1) {
        printf("20 bulundu, indeks: %d\n", pos);
    }
    
    freeArray(arr);
    return 0;
}