#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
} Element;

typedef struct {
    Element *data;
    int capacity;
    int count;
    int rows;
    int cols;
} SparseMatrix;

SparseMatrix* createSparseMatrix(int rows, int cols) {
    SparseMatrix *matrix = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->capacity = rows * cols;
    matrix->count = 0;
    matrix->data = (Element *)malloc(sizeof(Element) * matrix->capacity);
    return matrix;
}

void insertElement(SparseMatrix *matrix, int row, int col, int value) {
    if (value == 0) return;
    if (matrix->count >= matrix->capacity) {
        matrix->capacity *= 2;
        matrix->data = (Element *)realloc(matrix->data, sizeof(Element) * matrix->capacity);
    }
    matrix->data[matrix->count].row = row;
    matrix->data[matrix->count].col = col;
    matrix->data[matrix->count].value = value;
    matrix->count++;
}

void displaySparseMatrix(SparseMatrix *matrix) {
    printf("\nSparse Matrix (Row, Col, Value):\n");
    for (int i = 0; i < matrix->count; i++) {
        printf("(%d, %d, %d)\n", matrix->data[i].row, matrix->data[i].col, matrix->data[i].value);
    }
}

void displayDenseMatrix(SparseMatrix *matrix) {
    printf("\nDense Matrix:\n");
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            int value = 0;
            for (int k = 0; k < matrix->count; k++) {
                if (matrix->data[k].row == i && matrix->data[k].col == j) {
                    value = matrix->data[k].value;
                    break;
                }
            }
            printf("%d ", value);
        }
        printf("\n");
    }
}

void freeSparseMatrix(SparseMatrix *matrix) {
    free(matrix->data);
    free(matrix);
}

int main() {
    SparseMatrix *matrix = createSparseMatrix(5, 5);
    
    insertElement(matrix, 0, 1, 2);
    insertElement(matrix, 1, 2, 3);
    insertElement(matrix, 2, 0, 4);
    insertElement(matrix, 3, 4, 5);
    insertElement(matrix, 4, 3, 6);
    
    displaySparseMatrix(matrix);
    displayDenseMatrix(matrix);
    
    freeSparseMatrix(matrix);
    return 0;
}