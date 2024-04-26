# include <stdio.h>
void merge(int arr[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = lb;
    int A[10];
    while (i<=mid && j<=ub)
    {
        if (arr[i] <= arr[j])
        {
            A[k] = arr[i];
            i++;
        }
        else 
        {
            A[k] = arr[j];
            j++;
        }
        k++;
    }
    if (i>mid)
    {
        while (j<=ub)
        {
            A[k] = arr[j];
            k++;
            j++;
        }
    }
    else
    {
        while (i<=mid)
        {
            A[k] = arr[i];
            k++;
            i++;
        }
    }
    for (k = lb; k <= ub; k++)
    {
        arr[k] = A[k];
    }   
}
void MergeSort(int arr[], int lb, int ub)
{
    if (lb < ub)
    {
        int mid = (lb+ub)/2;
        MergeSort(arr, lb, mid);
        MergeSort(arr, mid+1, ub);
        merge(arr, lb, mid, ub);
    }
}
void main()
{
    int array[5] = {1,5,4,3,2};
    MergeSort(array, 0, 4);
    for (int i=0; i<=4; i++)
    {
        printf("%d \n", array[i]);
    }      
}
