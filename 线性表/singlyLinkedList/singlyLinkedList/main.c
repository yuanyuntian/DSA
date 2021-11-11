//
//  main.c
//  singlyLinkedList
//
//  Created by Fei Yuan on 2021/11/11.
//

#include <stdio.h>
#include<stdlib.h>



//单链表：使用链式存储结构的线性表。单链表中的数据是以结点来表示的，每个结点的构成：数据域（数据元素的映像） + 指针域（指示后继元素存储位置）。如果单链表不做特别说明，一般指的是动态单链表。

#define TRUE 1

#define ERROR 0

typedef int ElemType;
typedef int Status; // Status是函数结果状态，成功返回TRUE,失败返回FALSE

///线性表的单链表存储结构
typedef struct node {
    ElemType data;
    struct node * next;
}Node, LinkList;

void initList(LinkList ** pList);///初始化单链表

Status insertList(LinkList *pList, int i, const ElemType e);//插入元素

Status deleteList(LinkList * pList, int i, ElemType * e);//删除元素

Status getElem(LinkList * pList, int i, ElemType *e);//获取元素

Status insertListHead(LinkList * pList, const ElemType e);//// 头部后插入元素操作

Status insertListTail(LinkList *pList, const ElemType e); // 尾部后插入元素操作

Status clearList(LinkList *pList); // 清空链表操作

void traverseList(LinkList *pList); // 遍历链表操作



/// 初始化单链表
/// @param pList <#pList description#>
void initList(LinkList ** pList) {
    *pList = (LinkList *)malloc(sizeof(Node));
    if (!pList) {
        return;
    }
    (*pList)->data = 0;
    (*pList)->next = NULL;
}



/// 插入元素
/// @param pList <#pList description#>
/// @param i <#i description#>
/// @param e <#e description#>
Status insertList(LinkList *pList, int i, const ElemType e) {
    if (!pList) {
        return ERROR;
    }
    
    //找到i位置所在的前一个结点
    if (i < 1) {
        return ERROR;
    }
    
    //找到i位置所在的前一个结点
    Node * front = pList;
    int j = 1;
    while (front!= NULL && j < i) {
        front = front->next;
        j++;
    }
    
    if (front == NULL) {
        return ERROR;
    }

    Node * tmp = (Node *)malloc(sizeof(Node));
    if (!tmp) {
        return  ERROR;
    }
    tmp->data = e;
    
    //插入节点
    tmp->next = front->next;
    front->next = tmp;
    return  TRUE;
}

///删除元素
Status deleteList(LinkList * pList, int i, ElemType * e) {
    if (!pList) {
        return  ERROR;
    }
    
    //只能删除位置1以及以后的结点
    if (i < 1) {
        return ERROR;
    }
    
    //找到i位置所在的前一个结点
    Node * front = pList;
    int j = 1;
    while (front!= NULL && j < i) {
        front = front->next;
        j++;
    }
    
    if (front == NULL) {
        return ERROR;
    }
    // 提前保存要删除的结点
    Node *temp = front->next;
    *e = temp->data;
    
    //删除节点
    front->next = front->next->next;
    
    //delete
    free(temp);
    temp = NULL;
    return TRUE;
}

///获取元素
Status getElem(LinkList * pList, int i, ElemType *e) {
    if (!pList) {
        return  ERROR;
    }
    
    //只能删除位置1以及以后的结点
    if (i < 1) {
        return ERROR;
    }
    
    //找到i位置所在的前一个结点
    Node * front = pList;
    int j = 1;
    while (front!= NULL && j <= i) {
        front = front->next;
        j++;
    }
    
    if (front == NULL) {
        return ERROR;
    }
    *e = front->data;
    return TRUE;
}

/// 头部后插入元素操作
Status insertListHead(LinkList * pList, const ElemType e) {
    Node *head;
    Node *temp;
    
    if (!pList) {
        return  ERROR;
    }
    
    //让head指向链表头结点
    head = pList;
    
    // 创建存放插入元素的结点
    temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("malloc error!\n");
        return ERROR;
    }
    temp->data = e;
    temp->next = head->next;
    head->next = temp;
    return TRUE;
}

/// 尾部后插入元素操作
Status insertListTail(LinkList *pList, const ElemType e) {
    Node *cur;
    Node *temp;
    
    if (!pList) {
        return  ERROR;
    }
    
    // 找到链表尾节点
    cur = pList;
    while (cur->next) {
        cur = cur->next;
    }
    
    // 创建存放插入元素的结点
    temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        printf("malloc error!\n");
        return ERROR;
    }
    temp->data = e;

    
    // 尾结点后插入结点
    temp->next = cur->next;
    cur->next = temp;
    return TRUE;
}

/// 清空链表操作
Status clearList(LinkList *pList) {
    Node *cur; // 当前结点
    Node *temp; // 事先保存下一结点，防止释放当前结点后导致“掉链”
    
    if (!pList) {
        return  ERROR;
    }
    cur = pList->next; // 指向第一个结点
    while (cur) {
        temp = cur->next; // 事先保存下一结点，防止释放当前结点后导致“掉链”
        free(cur); // 释放当前结点
        cur = temp; // 将下一结点赋给当前结点p
    }
    pList->next = NULL;//头结点指针域指向空
    return TRUE;
}

/// 遍历链表操作
void traverseList(LinkList *pList) {
    if (!pList) {
        return ;
    }
    
    Node *cur = pList->next;

    while (cur) {
        printf("%d ",cur->data);
        cur = cur->next;
    }
    printf("\n");
}



int main(int argc, const char * argv[]) {
    // insert code here...
    LinkList *pList;

    // 初始化链表
    initList(&pList);
    
    // 插入结点
    insertList(pList, 1, 0);
    printf("在位置1插入元素0\n");
    insertList(pList, 2, 1);
    printf("在位置2插入元素1\n");
    insertList(pList, 3, 2);
    printf("在位置3插入元素2\n");
    insertList(pList, 4, 3);
    printf("在位置4插入元素3\n");
    traverseList(pList);
    
    
    // 删除结点
    int val;
    deleteList(pList, 2, &val);
    printf("删除位置2的结点，删除结点的数据为： %d\n", val);
    printf("\n");
    
    // 头部后插入元素
    insertListHead(pList, 5);
    printf("头部后插入元素5\n\n");
    
    traverseList(pList);

    // 尾部后插入元素
    insertListTail(pList, 8);
    printf("尾部后插入元素8\n\n");
    traverseList(pList);

    // 销毁链表
    clearList(pList);
    printf("销毁链表\n\n");
    
    
    return 0;
}
