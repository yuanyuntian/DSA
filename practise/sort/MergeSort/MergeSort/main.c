//
//  main.c
//  MergeSort
//
//  Created by Fei Yuan on 2022/3/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void merge(int * arr, int left, int mid, int right, int *tmp) {
    int i= left;
    int j = mid + 1;
    int t = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            tmp[t++] = arr[i++];
        }else{
            tmp[t++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        //将左边剩余元素填充进tmp中
        tmp[t++] = arr[i++];
    }
    
    while (j <= right) {
        //将右序列剩余元素填充进temp中
        tmp[t++] = arr[j++];
    }
    
    t = 0;
    //将tmp中的元素全部拷贝到元素数组中
    while (left <= right) {
        arr[left++] = tmp[t++];
    }
}

void sort(int * arr, int left, int right, int * tmp) {
    if (left < right) {
        int mid = (left + right)/2;
        sort(arr, left, mid, tmp);//左边归并排序，使得左子序有序
        sort(arr, mid + 1, right, tmp);//右边归并排序，使得右子序有序
        merge(arr, left, mid, right, tmp);//将两个有序子数组合并操作
    }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {10,12,9,5,100,76,34};
    int tmp[7];
    sort(a, 0, 7, tmp);
    for (int i = 0 ; i < 7; i ++) {
        printf("%d\n", tmp[i]);
    }
    return 0;
}
