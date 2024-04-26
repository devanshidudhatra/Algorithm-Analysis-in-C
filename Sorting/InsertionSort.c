#include<stdio.h>

void InsertionSort(int arr[] , int n){
    for(int i=0 ; i<n ; i++){
        int sort = arr[i];
        int j = i-1;
        while(j>=0 && arr[j] > sort)
        {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = sort;
    }
}

int main(){
    int arr[] = {3,9,2,5,6,1,8};
    int len = sizeof(arr)/sizeof(int);
    InsertionSort(arr,len);
    printf("Sorted Array is : ");
    for(int i = 0 ; i<len ; i++){
        printf("%d " , arr[i]);
    }
    printf("\n");
    return 0;
}