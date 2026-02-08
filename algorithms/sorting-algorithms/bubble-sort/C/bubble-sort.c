#include <stdio.h>


void bubbleSort(int[],int);

int main(){

    int arr[5] = {5,4,3,2,1};
    bubbleSort(arr,5);

    for(int i = 0; i < 5; ++i)
    {
        printf("%d ",arr[i]);
    }
}


void bubbleSort(int arr[],int size)
{
    int flag = 1;

    for(int i = 0; i < size - 1; ++i)
    {
        flag = 1;
        for(int j = 0; j < size - 1 - i; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = 0;
                
            }
        }
    
        if(flag){
            return;
        }

    }
}