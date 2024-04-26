#include <stdio.h>
#include <stdlib.h>

// Structure for an item which stores weight and
// corresponding value of Item
struct Item
{
    int profit, weight;
};

struct Item items[100];
int itemCount = 0;

void Sort()
{
    for (int i = 0; i < itemCount; i++)
    {
        for (int j = i + 1; j < itemCount; j++)
        {
            if ((items[i].profit/items[i].weight) > (items[j].profit/items[j].weight))
            {
                struct Item temp;
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

// Main greedy function to solve problem
double fractionalKnapsack(int W, struct Item arr[], int N)
{
    // Sorting Item on basis of ratio
    Sort();
    double finalvalue = 0.0;

    // Looping through all items
    for (int i = 0; i < N; i++)
    {
        // If adding Item won't overflow,
        // add it completely
        if (arr[i].weight <= W)
        {
            W -= arr[i].weight;
            finalvalue += arr[i].profit;
        }

        // If we can't add current Item,
        // add fractional part of it
        else
        {
            finalvalue += arr[i].profit * ((double)W / (double)arr[i].weight);
            break;
        }
    }

    // Returning final value
    return finalvalue;
}

// Driver code
int main()
{
    int W = 50;
    struct Item arr[] = {{60, 10}, {100, 20}, {120, 30}};
    int N = sizeof(arr) / sizeof(arr[0]);

    // Function call
    printf("%lf", fractionalKnapsack(W, arr, N));
    return 0;
}
