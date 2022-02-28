//
//  main.c
//  SelectionSort
//
//  Created by Fei Yuan on 2022/2/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int findMin(int * sub, int size) {
    int min = sub[0];
    int index_min = 0;
    for (int i  = 0; i < size; i ++) {
        if (sub[i] < min) {
            index_min = i;
            min = sub[i];
        }
    }
//    for (int i = 0 ; i < size; i ++) {
//        printf("%d\n",*(sub + i));
//    }
    return index_min;
}

void selectionSort(int * arr, int size) {
    for (int i = 0 ; i < size; i ++) {
        int min = findMin(arr + i, size - i);
        int tmp = arr[i];
        int last = arr[min];
        arr[i] = last;
        arr[min] = tmp;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {100,10,109,2,87,110};
    selectionSort(a, 6);
    for (int i = 0 ; i < 6; i ++) {
        printf("%d\n",a[i]);
    }
    return 0;
}
