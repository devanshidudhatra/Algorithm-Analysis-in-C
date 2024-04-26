#include<stdio.h>

int Partition(int arr[], int lb, int ub) {
    int pivot = arr[ub];
    int i = (lb - 1);

    for (int j = lb; j <= ub - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // swap arr[i+1] and arr[ub] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[ub];
    arr[ub] = temp;

    return i + 1;
}

void QuickSort(int arr[], int lb, int ub) {
    int loc;
    if (lb < ub) {
        loc = Partition(arr, lb, ub);
        QuickSort(arr, lb, loc - 1);
        QuickSort(arr, loc + 1, ub);
    }
}

int main() 
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    QuickSort(arr, 0, n - 1);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d \n", arr[i]);
    }

    return 0;
}
