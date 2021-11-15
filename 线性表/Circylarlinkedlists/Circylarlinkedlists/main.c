//
//  main.c
//  Circylarlinkedlists
//
//  Created by Fei Yuan on 2021/11/11.
//

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int Status; // Status是函数结果状态，成功返回TRUE,失败返回FALSE

typedef int ElemType;
/* 线性表的循环链表存储结构 */
typedef struct node
{
    ElemType data;
    struct node *next;
}Node, LinkList;



/// 初始化链表操作
void initList(LinkList **pList){
    *pList = (LinkList *)malloc(sizeof(Node));
    if (!pList) {
        return;
    }
    (*pList)->data = 0;
    // 因为是循环链表，所以尾指针指向头节点
    (*pList)->next = *pList;
}

//Pointer to last node in the list
Node * last = NULL;

//insert a node int the starting of the list
void insertAtFront() {
    //store the number to be inserted
    int data;
    
    //Initialize a new node
    Node *tmp = (Node *)malloc(sizeof(Node));
    
    //Input data
    printf("\nEnter data to be inserted:\n");
    scanf("%d",&data);
    
    //if the new node is the only node in the list
    if (last == NULL) {
        tmp->data = data;
        tmp->next = tmp;
        last = tmp;
    }else{
        //last node contains the reference of the new node and new node contains the reference of the privious first node
        tmp->data = data;
        tmp->next  = last->next;
        //last node now hsa reference of the new node tmp
        last->next = tmp;
    }
}

///遍历链表操作
void traverseList(void) {
    //if list is empty
    if (last == NULL){
        printf("\nlist is empty\n");
    }else{
        Node * tmp = last->next;
        do {
            printf("\nData= %d", tmp->data);
            tmp = tmp->next;
        } while (tmp != last->next);
    }
}


///在i后插入元素
Status insertList(LinkList *pList, int i, ElemType e) {
    
    Node * p = pList->next;
    int j = 0;
    while (p != pList && j < i - 1) {
        //利用循环找到待插入位置的前驱
        j ++;
        p = p->next;
    }
    
    if (p == pList) {
        return FALSE;
    }
    
    Node * q = (Node *)malloc(sizeof(Node));
    q->data = e;
    
    q->next = p->next;
    p->next = q;
    return TRUE;
}

int getLength(LinkList * plist) {
    Node * cur = plist;
    int length = 0;
    while (cur->next != plist) {
        cur = cur ->next;
        length ++;
    }
    return length;
}





int main(int argc, const char * argv[]) {
    // insert code here...
    insertAtFront();
    insertAtFront();
    insertAtFront();
    insertAtFront();
    insertAtFront();
    traverseList();
    return 0;
}
