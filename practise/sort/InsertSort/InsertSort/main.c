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
    int pre,current;
    for (int i = 1; i < size; i++) {
        pre = i - 1;
        current = arr[i];
        while (pre >= 0 && arr[pre] > current) {
            arr[pre + 1] = arr[pre];
            pre --;
        }
        arr[pre + 1] = current;
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
