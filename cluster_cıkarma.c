#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_QUEUE 100

typedef struct {
    int adj[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

typedef struct {
    int items[MAX_QUEUE];
    int front, rear;
} Queue;

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

void bfsCluster(Graph *g, int start, int *visited, int *cluster, int *clusterSize) {
    Queue *q = createQueue();
    visited[start] = 1;
    enqueue(q, start);
    cluster[*clusterSize] = start;
    (*clusterSize)++;
    
    while (!isQueueEmpty(q)) {
        int u = dequeue(q);
        
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adj[u][v] && !visited[v]) {
                visited[v] = 1;
                enqueue(q, v);
                cluster[*clusterSize] = v;
                (*clusterSize)++;
            }
        }
    }
    free(q);
}

void findClusters(Graph *g) {
    int visited[MAX_VERTICES] = {0};
    int clusterCount = 0;
    
    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) {
            int cluster[MAX_VERTICES] = {0};
            int clusterSize = 0;
            
            bfsCluster(g, i, visited, cluster, &clusterSize);
            
            printf("Cluster %d: ", clusterCount + 1);
            for (int j = 0; j < clusterSize; j++) {
                printf("%d ", cluster[j]);
            }
            printf("(Boyut: %d)\n", clusterSize);
            
            clusterCount++;
        }
    }
    printf("\nToplam Cluster Sayısı: %d\n", clusterCount);
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
    Graph *g = createGraph(8);
    
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 3, 4);
    addEdge(g, 5, 6);
    addEdge(g, 6, 7);
    
    displayGraph(g);
    
    printf("\n=== Clusters Bulunuyor ===\n");
    findClusters(g);
    
    freeGraph(g);
    return 0;
}