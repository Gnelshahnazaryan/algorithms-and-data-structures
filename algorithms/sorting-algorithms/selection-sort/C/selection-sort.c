#include <stdio.h>

void selectionSort(int[],int size);

int main(){

    int arr[5] = {64,25,12,22,11};

    selectionSort(arr,5);

    for(int i = 0; i < 5; ++i)
    {
        printf("%d ",arr[i]);
    }

    return 0;

}


void selectionSort(int arr[],int size){
    for(int i = 0; i < size - 1; ++i)
    {
        int minIndex = i;
        for(int j = i + 1; j < size; ++j)
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if(i != minIndex)
        {
            int tmp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = tmp;
        }
    }
}