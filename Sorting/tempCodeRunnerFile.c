#include<stdio.h>

void SelectionSort(int arr[] , int n){
    int i , j , min;
    for (i=0 ; i<n ; i++){
        min = i;
        for(j=i+1 ; j<n ; j++){
            if (arr[j]<arr[min]){
                min = j;
            }
            if(min != i ){
                int temp;
                temp = arr[min];
                arr[min] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

int main(){
    int arr = {3,9,2,5,6,1,8};
    int len = sizeof(arr)/sizeof(int);
    SelectionSort(arr[],len);
    printf("Sorted Array is : ");
    for(int i = 0 ; i<len ; i++){
        printf("%d " , arr[i]);
    }
    printf("\n");
    return 0;
}