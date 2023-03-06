//
//  main.c
//  QuickSort
//
//  Created by CQ on 2023/3/6.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void swap(int * arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


// 使用 Lomuto 分区方案进行分区
int partition(int a[], int start, int end)
{
    // 从数组中选择最右边的元素作为枢轴
    int pivot = a[end];
 
    // 小于主元的元素将被推到 `pIndex` 的左侧
    // 超过轴的元素将被推到 `pIndex` 的右侧
    // 相等的元素可以去任何方向
    int pIndex = start;
 
    // 每次我们找到一个小于或等于枢轴的元素，`pIndex`
    // 递增，并且该元素将放置在枢轴之前。
    for (int i = start; i < end; i++)
    {
        if (a[i] <= pivot)
        {
            swap(a, i, pIndex);
            pIndex++;
        }
    }
 
    // 将 `pIndex` 与枢轴交换
    swap(a, pIndex, end);

    // 返回 `pIndex`(枢轴元素的索引)
    return pIndex;
}
 
// 快速排序例程
void quicksort(int a[], int start, int end)
{
    // 基本条件
    if (start >= end) {
        return;
    }
 
    // 跨枢轴重新排列元素
    int pivot = partition(a, start, end);
 
    // 在包含小于主元的元素的亚阵列上递归
    quicksort(a, start, pivot - 1);
 
    // 在包含大于枢轴的元素的亚阵列上递归
    quicksort(a, pivot + 1, end);
}

//void quickSort(int *arr, int left, int right) {
//    if(left < right) {
//        int key = arr[left];
//        int i = left;
//        int j = right;
//        while (i < j) {
//            while (i < j && arr[j] > key) {
//                j --;
//            }
//            if(i < j) {
//                arr[i] = arr[j];
//                i++;
//            }
//
//            while (i < j && arr[i] < key) {
//                i ++;
//            }
//
//            if(i < j) {
//                arr[j] = arr[i];
//                j --;
//            }
//        }
//        arr[i] = key;
//        quickSort(arr, left, i - 1);
//        quickSort(arr, i + 1, right);
//    }
//}

int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {10,12,9,5,100,76,34};
    int tmp[7];
    quicksort(a, 0, 6);
    for (int i = 0 ; i < 7; i ++) {
        printf("%d\n", a[i]);
    }
    return 0;
}
