//
//  main.c
//  SelectionSort
//
//  Created by Fei Yuan on 2022/2/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void selectionSort(int * arr, int size) {
    for (int i = 0 ; i < size; i ++) {
        int min = i;
        for (int j = i + 1; j < size; j ++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        int tmp = arr[i];
        arr[i] = arr[min];
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
