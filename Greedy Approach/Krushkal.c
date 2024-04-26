#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge
{
    int src, dest, weight;
};

// This can be said as a vertex and each vertex will have one parent
struct Subset
{
    int parent;
};

// Function to find the root of a vertex 
int Find(struct Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = Find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform union of two subsets
void Union(struct Subset subsets[], int x, int y)
{
    int xroot = Find(subsets, x);   // x is root of first tree
    int yroot = Find(subsets, y);  // y is root of other
    subsets[xroot].parent = yroot;    // y or x either can be made parent of other
}

// Kruskal's algorithm to find MST
void Kruskal(struct Edge edges[], int V, int E)
{
    struct Edge result[V]; // Stores the MST
    struct Subset subsets[V];

    // Initially all the subsets are made root of themselves
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
    }

    // Sort edges in ascending order of weight
    for (int i = 0; i < E - 1; ++i)
    {
        for (int j = 0; j < E - i - 1; ++j)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    int e = 0;     // Index for result[]
    int i = 0;     // Index for sorted edges

    while (e < V - 1 && i < E)
    {
        struct Edge nextEdge = edges[i++];

        int x = Find(subsets, nextEdge.src);    // root of source if found
        int y = Find(subsets, nextEdge.dest);   // root of dest is founf

        if (x != y)                 // if root of both are not same then add the vertex and edge in mst
        {
            result[e++] = nextEdge;
            Union(subsets, x, y);        // this is to join the two subtrees
        }
    }

    // Print the MST
    printf("Edges in the MST:\n");
    for (int j = 0; j < e; ++j)
        printf("%d -- %d: %d\n", result[j].src, result[j].dest, result[j].weight);
}

int main()
{
    int V = 4;
    int E = 5;
    struct Edge edges[] = {{0, 1, 10}, {0, 2, 6}, {2, 3, 4}, {3, 1, 15}, {0, 3, 5}};
    Kruskal(edges, V, E);
    return 0;
}