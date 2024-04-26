#include <stdio.h>
#include <stdlib.h>

struct Graph 
{
    int V; // Number of vertices
    int E; // Number of edges
    struct Edge* edge; // Array of edges
};

struct Edge
{
    int src;    // Source vertex
    int dest;   // Destination vertex
    int weight; // Weight of the edge
};

// This can be said as a vertex and each vertex will have one parent
struct subset
{
    int parent;
};

// Function to find the root of the subset
int Find(struct subset subsets[], int i)        // Here we make array of subsets as we can have many vertices
{
    if (subsets[i].parent != i)                // If element is not root itself
        subsets[i].parent = Find(subsets, subsets[i].parent);   // find the root by recursion
    return subsets[i].parent;                   // Subset of i is fixed
}

// Function to do the union of two disjoint trees
void Union(struct subset subsets[], int x, int y)
{
    int xroot = Find(subsets, x);        // x is root of first tree
    int yroot = Find(subsets, y);       // y is root of other
    subsets[yroot].parent = xroot;      // x is made parent of y and y's all subsets
}

// Function to print the MST
void printMST(struct Edge result[], int e)       // e is the number of edges that are kept
{
    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < e; ++i)
    {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}

// Comparison function for qsort to sort the edges based on their weights
int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// Kruskal's Minimum Spanning Tree algorithm
void KruskalMST(struct Graph* graph)
{
    int V = graph->V;        // Number of vertices
    struct Edge result[V];   // result should contain all the vertices
    int e = 0; // Index variable for result[]
    int i = 0; // Index variable for sorted edges

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    // Allocate memory for subsets
    struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));

    // Initialize subsets
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
    }

    while (e < V - 1 && i < graph->E)
    {
        struct Edge next_edge = graph->edge[i++];

        int x = Find(subsets, next_edge.src);
        int y = Find(subsets, next_edge.dest);

        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the constructed MST
    printMST(result, e);

    // Clean up memory
    free(subsets);
}

int main()
{
    int V = 4; // Number of vertices
    int E = 5; // Number of edges

    // Create a graph
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));

    // Edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    // Edge 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    // Edge 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    // Edge 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    // Edge 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    KruskalMST(graph);

    return 0;
}