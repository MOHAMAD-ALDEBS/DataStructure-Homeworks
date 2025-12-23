#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_QUEUE 100
#define MAX_STACK 100

typedef struct {
    int adj[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

typedef struct {
    int items[MAX_QUEUE];
    int front, rear;
} Queue;

typedef struct {
    int items[MAX_STACK];
    int top;
} Stack;

Graph* createGraph(int vertices) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->numVertices = vertices;
    memset(g->adj, 0, sizeof(g->adj));
    return g;
}

void addEdge(Graph *g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

Queue* createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_QUEUE - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (q->front == -1 || q->front > q->rear) return -1;
    return q->items[q->front++];
}

int isQueueEmpty(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

Stack* createStack() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

void pushStack(Stack *s, int value) {
    if (s->top == MAX_STACK - 1) return;
    s->items[++s->top] = value;
}

int popStack(Stack *s) {
    if (s->top == -1) return -1;
    return s->items[s->top--];
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

void dfsRecursive(Graph *g, int vertex, int *visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adj[vertex][i] && !visited[i]) {
            dfsRecursive(g, i, visited);
        }
    }
}

void dfsIterative(Graph *g, int start) {
    int visited[MAX_VERTICES] = {0};
    Stack *s = createStack();
    
    pushStack(s, start);
    visited[start] = 1;
    
    while (!isStackEmpty(s)) {
        int vertex = popStack(s);
        printf("%d ", vertex);
        
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adj[vertex][i] && !visited[i]) {
                visited[i] = 1;
                pushStack(s, i);
            }
        }
    }
    
    free(s);
}

void bfs(Graph *g, int start) {
    int visited[MAX_VERTICES] = {0};
    Queue *q = createQueue();
    
    visited[start] = 1;
    enqueue(q, start);
    
    while (!isQueueEmpty(q)) {
        int vertex = dequeue(q);
        printf("%d ", vertex);
        
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adj[vertex][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(q, i);
            }
        }
    }
    
    free(q);
}

void displayGraph(Graph *g) {
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < g->numVertices; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

void freeGraph(Graph *g) {
    free(g);
}

int main() {
    Graph *g = createGraph(7);
    
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 2, 5);
    addEdge(g, 2, 6);
    
    displayGraph(g);
    
    printf("\n=== DFS (Recursive) ===\n");
    int visited[MAX_VERTICES] = {0};
    printf("DFS: ");
    dfsRecursive(g, 0, visited);
    printf("\n");
    
    printf("\n=== DFS (Iterative) ===\n");
    printf("DFS: ");
    dfsIterative(g, 0);
    printf("\n");
    
    printf("\n=== BFS ===\n");
    printf("BFS: ");
    bfs(g, 0);
    printf("\n");
    
    freeGraph(g);
    return 0;
}