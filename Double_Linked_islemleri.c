#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} DoubleLinkedList;

DoubleLinkedList* createList() {
    DoubleLinkedList *list = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node* createNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insertAtBegin(DoubleLinkedList *list, int data) {
    Node *node = createNode(data);
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

void insertAtEnd(DoubleLinkedList *list, int data) {
    Node *node = createNode(data);
    if (list->tail == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
}

void insertAtPosition(DoubleLinkedList *list, int data, int pos) {
    Node *node = createNode(data);
    if (pos == 0) {
        insertAtBegin(list, data);
        return;
    }
    
    Node *current = list->head;
    for (int i = 0; i < pos - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) return;
    
    node->next = current->next;
    node->prev = current;
    
    if (current->next != NULL) {
        current->next->prev = node;
    } else {
        list->tail = node;
    }
    current->next = node;
}

void deleteFromBegin(DoubleLinkedList *list) {
    if (list->head == NULL) return;
    Node *temp = list->head;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    free(temp);
}

void deleteFromEnd(DoubleLinkedList *list) {
    if (list->tail == NULL) return;
    Node *temp = list->tail;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    free(temp);
}

void deleteAtPosition(DoubleLinkedList *list, int pos) {
    if (list->head == NULL) return;
    if (pos == 0) {
        deleteFromBegin(list);
        return;
    }
    
    Node *current = list->head;
    for (int i = 0; i < pos && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) return;
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;
    }
    current->prev->next = current->next;
    free(current);
}

void traversalForward(DoubleLinkedList *list) {
    printf("İleri Traversal: ");
    Node *current = list->head;
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void traversalBackward(DoubleLinkedList *list) {
    printf("Geri Traversal: ");
    Node *current = list->tail;
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

void freeList(DoubleLinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    DoubleLinkedList *list = createList();
    
    insertAtEnd(list, 10);
    insertAtEnd(list, 20);
    insertAtEnd(list, 30);
    traversalForward(list);
    
    insertAtBegin(list, 5);
    traversalForward(list);
    
    insertAtPosition(list, 15, 2);
    traversalForward(list);
    traversalBackward(list);
    
    deleteFromBegin(list);
    traversalForward(list);
    
    deleteFromEnd(list);
    traversalForward(list);
    
    deleteAtPosition(list, 1);
    traversalForward(list);
    
    freeList(list);
    return 0;
}