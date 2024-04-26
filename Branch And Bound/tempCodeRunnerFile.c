#include <stdio.h>
#include <limits.h>

#define MAX_CITY 10

int graph[MAX_CITY][MAX_CITY];
int visited[MAX_CITY];
int min_cost = INT_MAX;

// Function to check if all cities are visited
int isVisited(int n) {
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

// Function to calculate lower bound using Minimum Spanning Tree heuristic
int tspRec(int curr_city, int count, int cost, int n) {
	int minimum_cost = 0;
    // If all cities are visited and return to starting city
    if (count == n && graph[curr_city][0]) {
        min_cost = minimum(min_cost, cost + graph[curr_city][0]);
        return 1;
    }

    // If limit is exceeded, prune
    if (cost + minCost(curr_city, n) >= min_cost) {
        return 0;
    }

    // Mark current city as visited
    visited[curr_city] = 1;

    // Try visiting all unvisited cities
    for (int next_city = 0; next_city < n; next_city++) {
        if (visited[next_city] == 0 && graph[curr_city][next_city]) {
            tspRec(next_city, count + 1, cost + graph[curr_city][next_city], n);
        }
    }

    // Backtrack
    visited[curr_city] = 0;

    return 0;
}

// Function to find minimum cost
int minCost(int city, int n) {
    int minimum = INT_MAX, i;

    // Find minimum value in row
    for (int i = 0; i < n; i++) {
        if (graph[city][i] && visited[i] == 0) {
            minimum = minimum(minimum, graph[city][i]);
        }
    }

    // Add remaining available edges
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            minimum += minCost(i, n);
        }
    }

    return minimum;
}

// Function to solve TSP using Branch and Bound
void tsp(int n) {
    int cost = 0;

    // Mark starting city as visited
    visited[0] = 1;

    tspRec(0, 1, cost, n);

    printf("Minimum cost: %d\n", min_cost);
}

int main() {
    int n;

    printf("Enter the number of cities: ");
    scanf("%d", &n);

    printf("Enter the cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    tsp(n);

    return 0;
}
