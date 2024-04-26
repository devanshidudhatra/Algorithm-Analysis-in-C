#include <stdio.h>
#include <stdlib.h>

// Function to get the number of ways
long getNumberOfWays(long N, long *Coins, int numCoins)
{
    // Create the ways array to 1 plus the amount
    // to stop overflow
    long *ways = (long *)malloc((N + 1) * sizeof(long));

    // Set the first way to 1 because it's 0 and
    // there is 1 way to make 0 with 0 coins
    ways[0] = 1;

    // Go through all of the coins
    for (int i = 0; i < numCoins; i++)
    {
        // Make a comparison to each index value
        // of ways with the coin value.
        for (int j = 0; j <= N; j++)
        {
            if (Coins[i] <= j)
            {
                // Update the ways array
                ways[j] += ways[(j - Coins[i])];
            }
        }
    }

    // Return the value at the Nth position
    // of the ways array.
    long result = ways[N];
    free(ways);
    return result;
}

void printArray(long *coins, int numCoins)
{
    for (int i = 0; i < numCoins; i++)
        printf("%ld\n", coins[i]);
}

// Driver Code
int main()
{
    long Coins[] = {1, 5, 10};
    int numCoins = sizeof(Coins) / sizeof(Coins[0]);

    printf("The Coins Array:\n");
    printArray(Coins, numCoins);

    printf("Solution:\n");
    printf("%ld\n", getNumberOfWays(12, Coins, numCoins));
    return 0;
}
