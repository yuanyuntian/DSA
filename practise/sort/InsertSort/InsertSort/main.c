//
//  main.c
//  InsertSort
//
//  Created by Fei Yuan on 2022/3/1.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void InsertSort(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int des = arr[i];
        for (int j = i - 1; j >= 0 ; j --) {
            if (arr[j] > des) {
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {100,10,109,20,50};
    InsertSort(a, 5);
    for (int i = 0 ; i < 5; i ++) {
        printf("%d\n",a[i]);
    }
    return 0;
}
