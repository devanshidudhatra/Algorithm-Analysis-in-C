#include <stdio.h>
#include <stdlib.h>
#include<math.h>

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int Left[n1], Right[n2];

    for (int i = 0; i < n1; i++) {
        Left[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        Right[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (Left[i] >= Right[j]) {
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int total_cost(int arr[], int n){
    double total = 0.0;
    int current_month = 1;
    for(int i=0 ; i< n ; i++){
        double rate = arr[i];
        total += 100 * rate* current_month;
        current_month++;
    }
    printf("Total cost : $%.2f\n" , total);
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int no_of_lic;
    printf("Enter the number of licenses : ");
    scanf("%d", &no_of_lic);

    int growth_rate[no_of_lic];

    printf("Enter the growth rate for each license: \n");
    for (int i = 0; i < no_of_lic; i++) {
        printf("Enter growth rate of %d : " , i+1);
        scanf("%d", &growth_rate[i]);
    }

    merge_sort(growth_rate, 0, no_of_lic - 1);

    printf("Order to buy licenses (decreasing growth rate): ");
    print_array(growth_rate, no_of_lic);

    int min_cost;
    total_cost(growth_rate, no_of_lic);
    
    return 0;
}
