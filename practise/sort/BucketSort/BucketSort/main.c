//
//  main.c
//  BucketSort
//
//  Created by yuanf on 2022/3/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
void bucketSort(int * arr, int size, int max) {
    int i,j;
    int bucket[max];
    memset(bucket, 0, (max + 1) * sizeof(int));
    for (i = 0; i < size; i++) {
        bucket[arr[i]]++;
    }
    
    for (i = 0, j = 0; i <= max; i ++) {
        while (bucket[i]-- > 0) {
            arr[j++] = i;
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    int a[] = {10,10,20,50,100,60,40};
    bucketSort(a, 7, 100);
    for (int i = 0 ; i < 7; i ++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
