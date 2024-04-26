#include <stdio.h>

// Function to find the peak entry in a unimodal array
int find_peak_entry(int A[], int n) {
    int left = 0;
    int right = n - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (A[mid] < A[mid + 1])
            left = mid + 1;
        else
            right = mid;
    }
    
    return left;
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int A[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int peak_entry = find_peak_entry(A, n);
    printf("Peak entry: %d\n", peak_entry + 1);

    return 0;
}
