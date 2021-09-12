
#include<stdio.h>

int A [] = { 3 ,8 ,1 ,2, 0, -1, 4, 5, 6, 7};
//int A [] = { 50, 25,92, 16,76,30,43,54,19};


int partition(int *A, int low, int high) {
    int left = low, right = high;
    int pivot = A[low];
    int temp = 0 ;

    while(left < right) {
        while(A[left]<=pivot) 
            left++;

        while(A[right]>pivot)
            right--;

        if(left < right) {
             temp = A[left];
            A[left]=A[right];
            A[right] = temp;
        }
        
    }
    A[low] = A[right];
    A[right] = pivot;
    return right;

}
        

void qsort(int *A, int low, int high) {
    int pivot = 0;
    if(high > low) {
        pivot = partition(A, low, high);
        qsort(A, low, pivot-1);
        qsort(A, pivot+1, high);
    }

}

void display(int *A, int len) {
    for(int i=0; i<len; i++) {
        printf("%d \t", A[i]);
    }
    printf("\n");
}

int main() {
    int len  = sizeof(A)/sizeof(A[0]);
    printf("Array before sort \n");
    display(A, len);

    printf("length of array %d \n", len);
    qsort(A, 0, len - 1);

    printf("Array after sort \n");
    display(A, len);
    return 0;
}
