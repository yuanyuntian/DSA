//
//  main.c
//  HeapSort
//
//  Created by Fei Yuan on 2022/3/3.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//https://www.cnblogs.com/chengxiao/p/6129630.html

//大顶堆：arr[i] >= arr[2i+1] && arr[i] >= arr[2i+2]
//小顶堆：arr[i] <= arr[2i+1] && arr[i] <= arr[2i+2]

//a.将无需序列构建成一个堆，根据升序降序需求选择大顶堆或小顶堆;
//b.将堆顶元素与末尾元素交换，将最大元素"沉"到数组末端;
//c.重新调整结构，使其满足堆定义，然后继续交换堆顶元素与当前末尾元素，反复执行调整+交换步骤，直到整个序列有序。


/*调整位置i的元素到合适的位置
父节点 (m - 1)/2
左孩子节点2 * m + 1
右孩子节点2 * m + 2
*/

void swap(int * arr, int i, int j) {
    int tmp;
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void printArr(int * arr, int size) {
    if (arr == NULL) {
        return;
    }
    int  i = 0;
    while (i < size) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//构造大根堆（通过新插入的数上升）
void heapInsert(int * arr,int size) {
    for (int i = 0; i < size; i++) {
        //当前插入的索引
        int currentIndex = i;
        //父结点索引
        int fatherIndex = (currentIndex - 1) / 2;
        //如果当前插入的值大于其父结点的值,则交换值，并且将索引指向父结点
        //然后继续和上面的父结点值比较，直到不大于父结点，则退出循环
        while (arr[currentIndex] > arr[fatherIndex]) {
            //交换当前结点与父结点的值
            swap(arr, currentIndex, fatherIndex);
            //将当前索引指向父索引
            currentIndex = fatherIndex;
            //重新计算当前索引的父索引
            fatherIndex = (currentIndex - 1) / 2;
        }
    }
}

//将剩余的数构造成大根堆（通过顶端的数下降）
void heapify(int * arr, int index, int size) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    while (left < size) {
        int largestIndex;
        //判断孩子中较大的值的索引（要确保右孩子在size范围之内）
        if (arr[left] < arr[right] && right < size) {
            largestIndex = right;
        } else {
            largestIndex = left;
        }
        //比较父结点的值与孩子中较大的值，并确定最大值的索引
        if (arr[index] > arr[largestIndex]) {
            largestIndex = index;
        }
        //如果父结点索引是最大值的索引，那已经是大根堆了，则退出循环
        if (index == largestIndex) {
            break;
        }
        //父结点不是最大值，与孩子中较大的值交换
        swap(arr, largestIndex, index);
        //将索引指向孩子中较大的值的索引
        index = largestIndex;
        //重新计算交换之后的孩子的索引
        left = 2 * index + 1;
        right = 2 * index + 2;
    }
}


void heapSort(int * arr, int size) {
    //构造大根堆
    heapInsert(arr, size);
    while (size > 1) {
        //固定最大值
        swap(arr, 0, size - 1);
        size--;
        //构造大根堆
        heapify(arr, 0, size);
    }
}






int main(int argc, const char * argv[]) {
    // insert code here...
    int a [] = {3,2,10,19,5,6,20,100,2,7};
    heapSort(a,10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}
