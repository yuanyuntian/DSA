//
//  main.c
//  shell
//
//  Created by yuanf on 2022/3/1.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void shellSort(int * arr, int size) {
    for (int gap = size/2; gap > 0; gap = gap / 2) {
        for (int i = gap; i < size; i ++) {
            int j = i;
            int current = arr[i];
            while (j - gap >= 0 && current < arr[j - gap]) {
                arr[j] = arr[j - gap];
                j = j - gap;
            }
            arr[j] = current;
        }
    }

}

int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {10,3,11,18,5,13,100,200,1,22,35};
    shellSort(a, 11);
    for (int i = 0; i < 11; i ++) {
        printf("%d\n",a[i]);
    }
    return 0;
}
