//
//  main.c
//  SequentialList
//
//  Created by Fei Yuan on 2021/11/11.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

///使用顺序存储方式的顺序表即为顺序表
//在编写顺序表的基本操作函数前，有几个注意点：
//
//插入操作中，需考虑顺序表已满的情况，删除、获取操作中，需考虑顺序表为空的情况；
//在各操作中，当涉及到位置 i 时，都应考虑 i 位置不合理的情况；
//插入删除操作中，均应考虑插入或删除位置为表尾（或表尾下一个位置）的情况；

//注意：这里有两个概念 "数组的长度" 和 "顺序表的长度" 需要区分一下。数组的长度是存放顺序表的存储空间的长度，存储分配后这个量是一般是不变的。顺序表的长度是顺序表中数据元素的个数，随着顺序表插入和删除操作的进行，这个量是变化的。


#define TRUE 1
#define FALSE 0
typedef int Status; // Status是函数结果状态，成功返回TRUE,失败返回FALSE
#define INCREATE_SIZE 2
#define INIT_SIZE 2  /* 数组长度 */
typedef int  ElemType; /* "ElemType类型根据实际情况而定， 这里假设为int */
// 顺序表结构定义
typedef struct
{
    ElemType *data;  /* 存放顺序表元素的数组，最大值为MAXSIZE */
    int length; /* 顺序表的当前长度 */
    int count;//数组的长度
}SeqList;

SeqList initList(); // 初始化操作
Status appendList(SeqList *pSeqList, const ElemType e); // 附加元素操作
Status insertList(SeqList *pSeqList, int i, const ElemType e); // 插入元素操作
Status deleteList(SeqList *pSeqList, int i, ElemType *e); // 删除元素操作
Status getElem(SeqList *pSeqList, int i, ElemType *e); // 获取元素操作
int locateElem(SeqList *pSeqList, const ElemType e); // 查找元素位置操作
void traverseList(SeqList *pSeqList); // 遍历顺序表
Status isEmpty(SeqList *pSeqList); // 检测是否为空操作
int getLength(SeqList *pSeqList); // 获取元素个数操作
void clearList(SeqList *pSeqList); // 清空顺序表操作
void destroyList(SeqList *pSeqList); // 销毁顺序表操作


// 初始化操作
SeqList initList(void) {
    SeqList list;
    list.data = (ElemType *)malloc( INIT_SIZE *sizeof(ElemType));
    if (list.data == NULL) {
        exit(-1);
    }
    
    list.length = 0;
    list.count = INIT_SIZE;
    return list;
}

/// 附加元素操作
Status appendList(SeqList *pSeqList, const ElemType e) {
    //判断顺序表长度是否大于等于数组长度，是则抛出异常或动态增加容量
    if (pSeqList->length >= pSeqList->count) {
        pSeqList->data = realloc(pSeqList->data, (pSeqList->count + INCREATE_SIZE) *sizeof(ElemType));
        pSeqList->count = pSeqList->count + INCREATE_SIZE;
    }
    //在表尾后面添加元素
    pSeqList->data[pSeqList->length] = e;
    
    pSeqList->length ++;
    return TRUE;
}

// 插入元素操作
Status insertList(SeqList *pSeqList, int i, const ElemType e) {
    // 判断顺序表是否已满，且插入位置是否合理
    if (pSeqList->length >= pSeqList->count) {
        pSeqList->data = realloc(pSeqList->data, (pSeqList->count + INCREATE_SIZE) *sizeof(ElemType));
        pSeqList->count = pSeqList->count + INCREATE_SIZE;
    }
    
    // 从最后一个元素开始向前遍历到第i个位置，分别将它们都向后移动一个位置
    // 有两种特殊情况不用后移：当第一次在位置0插入元素，或者在表尾的下一个位置插入元素
    if (pSeqList->length != 0 && i != pSeqList->length) {
        //将插入位置及后面元素向后移动一位
        for (int k = pSeqList->length - 1; k>= i; k--) {
            pSeqList->data[k+1] = pSeqList->data[k];
        }
    }
    // 将要插入元素填入位置i处
    pSeqList->data[i] = e;
    pSeqList->length ++;
    return  TRUE;
}

// 删除元素操作
Status deleteList(SeqList *pSeqList, int i, ElemType *e)
{
    // 判断顺序表是否为空，且删除位置是否合理
    if (pSeqList->length == 0 || i < 0 || i > pSeqList->length - 1)
        return FALSE;

    // 取出删除元素
    *e = pSeqList->data[i];

    // 从删除元素的下一个位置开始遍历到最后一个元素位置，分别将它们都向前移动一个位置
    if (i != pSeqList->length - 1) // 【若删除位置在表尾，则不需要前移】
    {
        // 将删除元素的下一个位置及后面元素向前移动一位
        for (int k = i; k < pSeqList->length - 1; k++)
            pSeqList->data[k] = pSeqList->data[k + 1];
    }

    // 表长减1
    pSeqList->length--;

    return TRUE;
}

// 获取元素操作
Status getElem(SeqList *pSeqList, int i, ElemType *e)
{
    // 判断顺序表是否存在，且删除位置是否合理
    if (pSeqList == NULL || i < 0 || i > pSeqList->length - 1)
        return FALSE;

    *e = pSeqList->data[i];

    return TRUE;
}

// 查找元素位置操作
int locateElem(SeqList *pSeqList, const ElemType e)
{
    // 遍历并显示顺序表元素
    for (int i = 0; i < pSeqList->length; i++)
    {
        if (pSeqList->data[i] == e)
            return i;
    }

    return -1;
}

// 遍历操作
void traverseList(SeqList *pSeqList)
{
    for (int i = 0; i < pSeqList->length; i++)
        printf("%d ", pSeqList->data[i]);
    printf("\n");
}

// 检测是否为空操作
Status isEmpty(SeqList *pSeqList)
{
    return pSeqList->length == 0 ? TRUE : FALSE;
}

// 获取元素个数操作
int getLength(SeqList *pSeqList)
{
    return pSeqList->length;
}

// 清空顺序表操作
void clearList(SeqList *pSeqList)
{
    pSeqList->length = 0;
}

// 销毁顺序表操作
void destroyList(SeqList *pSeqList)
{
    free(pSeqList);
    pSeqList = NULL;
}






int main(int argc, const char * argv[]) {
    // insert code here...
    // 初始化顺序表
    SeqList pSeqList = initList();

    // 检测顺序表是否为空
    if (isEmpty(&pSeqList))
        printf("顺序表为空！\n\n");
    else
        printf("顺序表不为空！\n\n");

    // 附加元素0-2到顺序表
    printf("附加元素0-2到顺序表!\n\n");
    for (int i = 0; i<3; i++)
    {
        appendList(&pSeqList, i);
    }
    printf("\n");
    traverseList(&pSeqList);
    return 0;
}
