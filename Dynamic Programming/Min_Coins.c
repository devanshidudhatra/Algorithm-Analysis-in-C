#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Utility function for solving the minimum coins problem
int minCoinsUtil(int coins[], int m, int V, int* dp)
{
	// Base case: If target value V is 0, no coins are
	// needed
	if (V == 0)
		return 0;

	// If subproblem is already solved, return the result
	// from DP table
	if (dp[V] != -1)
		return dp[V];

	int res = INT_MAX;

	// Iterate over all coins and recursively solve for
	// subproblems
	for (int i = 0; i < m; i++) {
		if (coins[i] <= V) {
			// Recursive call to solve for remaining value V
			// - coins[i]
			int sub_res
				= minCoinsUtil(coins, m, V - coins[i], dp);

			// If the subproblem has a valid solution and
			// the total number of coins is smaller than the
			// current result, update the result
			if (sub_res != INT_MAX && sub_res + 1 < res)
				res = sub_res + 1;
		}
	}

	// Save the result in the DP table
	dp[V] = res;

	return res;
}

// Function to find the minimum number of coins needed to
// make a target value
int minCoins(int coins[], int m, int V)
{
	// Create a DP table to store results of subproblems
	int* dp = (int *)malloc((V + 1) * sizeof(int));
	for (int i = 0; i <= V; i++)
        dp[i] = -1; // Initialize DP table with -1

	// Call the utility function to solve the problem
	int result = minCoinsUtil(coins, m, V, dp);
    free(dp);
	return result;
}

// Driver code
int main()
{
	int coins[] = { 9, 6, 5, 1 };
	int m = sizeof(coins) / sizeof(coins[0]);
	int V = 11;

	int res = minCoins(coins, m, V);
	if (res == INT_MAX)
		res = -1;

	// Find the minimum number of coins required
	printf("Minimum coins required is %d\n", res);

	return 0;
}
