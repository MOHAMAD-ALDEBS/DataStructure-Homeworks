#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} CircularLinkedList;

CircularLinkedList* createList() {
    CircularLinkedList *list = (CircularLinkedList *)malloc(sizeof(CircularLinkedList));
    list->head = NULL;
    return list;
}

Node* createNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insertAtBegin(CircularLinkedList *list, int data) {
    Node *node = createNode(data);
    if (list->head == NULL) {
        list->head = node;
        node->next = node;
    } else {
        Node *current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        node->next = list->head;
        current->next = node;
        list->head = node;
    }
}

void insertAtEnd(CircularLinkedList *list, int data) {
    Node *node = createNode(data);
    if (list->head == NULL) {
        list->head = node;
        node->next = node;
    } else {
        Node *current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = node;
        node->next = list->head;
    }
}

void insertAtPosition(CircularLinkedList *list, int data, int pos) {
    Node *node = createNode(data);
    if (pos == 0 || list->head == NULL) {
        insertAtBegin(list, data);
        return;
    }
    
    Node *current = list->head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
        if (current == list->head) break;
    }
    
    node->next = current->next;
    current->next = node;
}

void deleteAtBegin(CircularLinkedList *list) {
    if (list->head == NULL) return;
    
    if (list->head->next == list->head) {
        free(list->head);
        list->head = NULL;
    } else {
        Node *current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        Node *temp = list->head;
        list->head = list->head->next;
        current->next = list->head;
        free(temp);
    }
}

void deleteAtEnd(CircularLinkedList *list) {
    if (list->head == NULL) return;
    
    if (list->head->next == list->head) {
        free(list->head);
        list->head = NULL;
    } else {
        Node *current = list->head;
        while (current->next->next != list->head) {
            current = current->next;
        }
        Node *temp = current->next;
        current->next = list->head;
        free(temp);
    }
}

void deleteAtPosition(CircularLinkedList *list, int pos) {
    if (list->head == NULL) return;
    if (pos == 0) {
        deleteAtBegin(list);
        return;
    }
    
    Node *current = list->head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
        if (current == list->head) break;
    }
    
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
}

void traversal(CircularLinkedList *list) {
    if (list->head == NULL) {
        printf("Liste boş!\n");
        return;
    }
    
    printf("Traversal: ");
    Node *current = list->head;
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("head(%d)\n", list->head->data);
}

void freeList(CircularLinkedList *list) {
    if (list->head == NULL) return;
    
    Node *current = list->head;
    while (current->next != list->head) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(current);
    free(list);
}

int main() {
    CircularLinkedList *list = createList();
    
    insertAtEnd(list, 10);
    insertAtEnd(list, 20);
    insertAtEnd(list, 30);
    traversal(list);
    
    insertAtBegin(list, 5);
    traversal(list);
    
    insertAtPosition(list, 15, 2);
    traversal(list);
    
    deleteAtBegin(list);
    traversal(list);
    
    deleteAtEnd(list);
    traversal(list);
    
    deleteAtPosition(list, 1);
    traversal(list);
    
    freeList(list);
    return 0;
}