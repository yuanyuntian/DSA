//
//  main.c
//  InsertSort
//
//  Created by yuanf on 2022/3/1.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void InsertionSort(int *arr, int size) {
    
    int i ,j, ret;
    for (i = 1; i < size; i ++) {
        ret = arr[i];
        for (j = i - 1; j >= 0 && ret < arr[j]; j --) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = ret;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {10,3,11,18,5,13};
    InsertionSort(a, 6);
    for (int i = 0; i < 6; i ++) {
        printf("%d\n",a[i]);
    }
    return 0;
}
