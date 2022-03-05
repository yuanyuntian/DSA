//
//  main.c
//  countSort
//
//  Created by yuanf on 2022/3/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
int * countSort(int * arr, int size) {
    
    //找出数组最大值
    int max = arr[0];
    int min = arr[0];

    for (int i = 1; i < size ; i ++) {
        if (arr[i] > max) {
            max = arr[i];
        }else{
            min = arr[i];
        }
    }
    
    for (int i = 1; i < size ; i ++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    
    int count = max - min + 1;
    
    //构造计数数组countArr
    int * countArr = (int *)calloc(count, sizeof(int));
    for (int j = 0; j < size; j ++) {
        countArr[arr[j] - min]++;
    }
    //构造结果数组
    int * resultArr = (int *)calloc(size, sizeof(int));
    
    int index = 0;
    for (int i = 0; i < count; i ++) {
        while (countArr[i] > 0) {
            resultArr[index ++] = i + min;
            countArr[i]--;
        }
    }
    return resultArr;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int a[] = {20,30,10,3,6,90,30};
    int * r = countSort(a, 7);
    for (int i = 0; i < 7; i ++) {
        printf("%d ", r[i]);
    }
    printf("\n");
    return 0;
}
