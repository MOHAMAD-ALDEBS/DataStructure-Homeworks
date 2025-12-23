#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int data[MAX_NODES];
    int size;
} BinaryTree;

BinaryTree* createTree() {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->size = 0;
    return tree;
}

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

void insert(BinaryTree *tree, int value) {
    if (tree->size >= MAX_NODES) {
        printf("Ağaç dolu!\n");
        return;
    }
    tree->data[tree->size] = value;
    tree->size++;
    printf("%d eklendi.\n", value);
}

void display(BinaryTree *tree) {
    printf("\nLevel Order (Array): ");
    for (int i = 0; i < tree->size; i++) {
        printf("%d ", tree->data[i]);
    }
    printf("\n");
}

void inorderTraversal(BinaryTree *tree, int index) {
    if (index >= tree->size) return;
    
    inorderTraversal(tree, leftChild(index));
    printf("%d ", tree->data[index]);
    inorderTraversal(tree, rightChild(index));
}

void preorderTraversal(BinaryTree *tree, int index) {
    if (index >= tree->size) return;
    
    printf("%d ", tree->data[index]);
    preorderTraversal(tree, leftChild(index));
    preorderTraversal(tree, rightChild(index));
}

void postorderTraversal(BinaryTree *tree, int index) {
    if (index >= tree->size) return;
    
    postorderTraversal(tree, leftChild(index));
    postorderTraversal(tree, rightChild(index));
    printf("%d ", tree->data[index]);
}

void levelOrderTraversal(BinaryTree *tree) {
    printf("\nLevel Order Traversal: ");
    for (int i = 0; i < tree->size; i++) {
        printf("%d ", tree->data[i]);
    }
    printf("\n");
}

void printTree(BinaryTree *tree, int index, int space) {
    if (index >= tree->size) return;
    
    space += 4;
    
    printTree(tree, rightChild(index), space);
    
    printf("\n");
    for (int i = 4; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", tree->data[index]);
    
    printTree(tree, leftChild(index), space);
}

int findNode(BinaryTree *tree, int value) {
    for (int i = 0; i < tree->size; i++) {
        if (tree->data[i] == value) {
            return i;
        }
    }
    return -1;
}

void displayNodeInfo(BinaryTree *tree, int value) {
    int index = findNode(tree, value);
    if (index == -1) {
        printf("%d bulunamadı!\n", value);
        return;
    }
    
    printf("\nNode %d Bilgisi:\n", value);
    printf("İndeks: %d\n", index);
    
    if (index > 0) {
        printf("Ebeveyn: %d (indeks %d)\n", tree->data[parent(index)], parent(index));
    }
    
    if (leftChild(index) < tree->size) {
        printf("Sol Çocuk: %d (indeks %d)\n", tree->data[leftChild(index)], leftChild(index));
    }
    
    if (rightChild(index) < tree->size) {
        printf("Sağ Çocuk: %d (indeks %d)\n", tree->data[rightChild(index)], rightChild(index));
    }
}

void freeTree(BinaryTree *tree) {
    free(tree);
}

int main() {
    BinaryTree *tree = createTree();
    
    printf("=== Binary Tree Oluşturma ===\n");
    insert(tree, 1);
    insert(tree, 2);
    insert(tree, 3);
    insert(tree, 4);
    insert(tree, 5);
    insert(tree, 6);
    insert(tree, 7);
    
    display(tree);
    
    printf("\n=== Ağaç Yapısı ===\n");
    printTree(tree, 0, 0);
    
    printf("\n=== Traversal İşlemleri ===\n");
    printf("Inorder: ");
    inorderTraversal(tree, 0);
    printf("\n");
    
    printf("Preorder: ");
    preorderTraversal(tree, 0);
    printf("\n");
    
    printf("Postorder: ");
    postorderTraversal(tree, 0);
    printf("\n");
    
    levelOrderTraversal(tree);
    
    displayNodeInfo(tree, 4);
    displayNodeInfo(tree, 2);
    displayNodeInfo(tree, 7);
    
    freeTree(tree);
    return 0;
}