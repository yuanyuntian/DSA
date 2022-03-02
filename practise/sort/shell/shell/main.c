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
    int i ,j,gap, ret;
    for (gap = size/2; gap > 0; gap /= 2) {
        for (i = gap; i < size; i ++) {
            ret = arr[i];
            for (j = i - gap; j >= 0 && ret < arr[j]; j -= gap) {
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = ret;
        }
    }

}

int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {10,3,11,18,5,13};
    shellSort(a, 6);
    for (int i = 0; i < 6; i ++) {
        printf("%d\n",a[i]);
    }
    return 0;
}
