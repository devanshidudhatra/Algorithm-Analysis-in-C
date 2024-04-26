#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// iPair ==> Integer Pair
typedef struct
{
    int first;
    int second;
} iPair;

// Structure to represent adjacency list node
typedef struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode *next;
} AdjListNode;

// Structure to represent adjacency list
typedef struct
{
    AdjListNode *head;
} AdjList;

// Structure to represent graph
typedef struct
{
    int V; // No. of vertices
    AdjList *array;
} Graph;

// Function to create a new adjacency list node
AdjListNode *newAdjListNode(int dest, int weight)
{
    AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
Graph *createGraph(int V)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of
    // array will be V
    graph->array = (AdjList *)malloc(V * sizeof(AdjList));

    // Initialize each adjacency list as empty by
    // making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph *graph, int src, int dest, int weight)
{
    // Add an edge from src to dest
    AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest
    // to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Structure to represent a node in priority queue
typedef struct
{
    int data;
    int priority;
} PriorityNode;

// Structure to represent priority queue
typedef struct
{
    int capacity;
    int size;
    PriorityNode *array;
} PriorityQueue;

// Function to create a new priority queue
PriorityQueue *createPriorityQueue(int capacity)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->array = (PriorityNode *)malloc(capacity * sizeof(PriorityNode));
    return pq;
}

// Function to swap two priority nodes
void swap(PriorityNode *a, PriorityNode *b)
{
    PriorityNode temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify at given index
void minHeapify(PriorityQueue *pq, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pq->size && pq->array[left].priority < pq->array[smallest].priority)
        smallest = left;

    if (right < pq->size && pq->array[right].priority < pq->array[smallest].priority)
        smallest = right;

    if (smallest != idx)
    {
        swap(&pq->array[idx], &pq->array[smallest]);
        minHeapify(pq, smallest);
    }
}

// Function to check if priority queue is empty
int isEmpty(PriorityQueue *pq)
{
    return pq->size == 0;
}

// Function to extract minimum node from priority queue
PriorityNode extractMin(PriorityQueue *pq)
{
    if (isEmpty(pq))
        return (PriorityNode){-1, -1};

    PriorityNode root = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    minHeapify(pq, 0);

    return root;
}

// Function to decrease priority of a given vertex
void decreasePriority(PriorityQueue *pq, int v, int priority)
{
    int i;
    for (i = 0; i < pq->size; i++)
    {
        if (pq->array[i].data == v)
            break;
    }

    pq->array[i].priority = priority;

    // Fix the heap property if it is violated
    while (i && pq->array[i].priority < pq->array[(i - 1) / 2].priority)
    {
        swap(&pq->array[i], &pq->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Prints shortest paths from src to all other vertices
void shortestPath(Graph *graph, int src)
{
    int V = graph->V;                           // Get the number of vertices in graph
    int *dist = (int *)malloc(V * sizeof(int)); // dist values used to pick minimum weight edge in cut

    // pq represents set of vertices not yet included in shortest path tree
    PriorityQueue *pq = createPriorityQueue(V);

    // Initialize dist values to INF and insert all vertices into priority queue
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INF;
        pq->array[v].data = v;
        pq->array[v].priority = dist[v];
    }

    // Make dist value of src vertex as 0 so that it is extracted first
    pq->array[src].priority = dist[src] = 0;
    decreasePriority(pq, src, dist[src]);

    // Initially size of priority queue is V
    pq->size = V;

    // Looping till priority queue becomes empty (or all distances are not finalized)
    while (!isEmpty(pq))
    {
        // Extract the vertex with minimum distance value
        PriorityNode u = extractMin(pq);
        int uIdx = u.data;

        // Traverse through all adjacent vertices of u (the extracted vertex) and update their distance values
        AdjListNode *pCrawl = graph->array[uIdx].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;

            // If shortest distance to v is not finalized yet, and distance to v through u is less than its previously calculated distance
            if (!isEmpty(pq) && dist[v] > dist[uIdx] + pCrawl->weight)
            {
                // Updating distance of v
                dist[v] = dist[uIdx] + pCrawl->weight;
                decreasePriority(pq, v, dist[v]);
            }

            pCrawl = pCrawl->next;
        }
    }

    // Print shortest distances stored in dist[]
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Driver program to test above functions
int main()
{
    // create the graph given in above figure
    int V = 9;
    Graph *graph = createGraph(V);

    // making above shown graph
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    // Function call
    shortestPath(graph, 0);

    return 0;
}
