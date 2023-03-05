//
//  main.c
//  BubbleSort
//
//  Created by Fei Yuan on 2022/2/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void BubbleSort(int * arr, int size) {
    for (int i = 0 ; i < size; i ++) {
        for (int j = 0; j < size  - i - 1; j ++) {
            if(arr[j] > arr[j + 1]) {
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {10,11,2,13,90,5};
    BubbleSort(a, 6);
    for (int i = 0 ; i < 6; i ++) {
        printf("%d\n",a[i]);
    }
    return 0;
}
