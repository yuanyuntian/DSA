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

//to add a new node at the end of the list
void addatlast(void) {
    //store number to be inserted
    int data;
    
    //Initialize a new node
    Node * tmp = (Node*)malloc(sizeof(Node));
    
    //Input data
    printf("\nEnter data to be inserted:\n");
    scanf("%d",&data);
    
    //If the new node is the only node in the list
    if (last == NULL) {
        tmp->data = data;
        tmp->next = last;
        last = tmp;
    }else{
        // the new node will be the last node and will
        //contain the reference of head node
        tmp->data = data;
        tmp->next = last->next;
        last->next = tmp;
        last = tmp;
    }
}

//delete the first element of the list
void deletefirst(void) {
    Node * tmp;
    if (last == NULL) {
        printf("\nList is empty \n");
    }else{
        tmp = last->next;
        last->next = tmp->next;
        free(tmp);
    }
}

//delete the last node in the list
void deletelast(void) {
    Node * tmp;
    if (last == NULL) {
        printf("\nList is empty \n");
    }
    
    tmp = last->next;
    
    //Traverse the list till the second last node
    while (tmp->next != last) {
        tmp = tmp->next;
    }
    
    // Second last node now contains
    // the reference of the first
    // node in the list
    tmp->next = last->next;
    last = tmp;
}

//delete an element at a specified index in the list
void deleteAtIndex(void) {
    // Stores the index at which
    // the element is to be deleted
    int pos, i = 1;
    Node * tmp, * position;
    tmp = last->next;
    
    //if list is empty
    if (last == NULL) {
        printf("\nList is empty.\n");
    }else{
        // Input Data
        printf("\nEnter index : ");
        scanf("%d", &pos);

        // Traverse till the node to
        // be deleted is reached
        while (i <= pos - 1) {
            tmp = tmp->next;
            i++;
        }
        
        // After the loop ends, temp
        // points at a node just before
        // the node to be deleted
 
        // Reassigning links

        position = tmp->next;
        tmp->next = position->next;
        
        free(position);
    }
}

//insert after any specified element
void insertafter(void) {
    //store data and element after which new node is to
    //to be inserted
    int data, value;
    
    //Initialize a new node
    Node *tmp, *n;
    
    //Input data
    printf("\nEnter number after which you want to enter number:\n");
    scanf("%d", &value);
    tmp = last->next;
    do {
        //Element after which node is to be inserted is found
        if (tmp->data == value) {
            n = (Node*)malloc(sizeof(Node));
            //Input Data
            printf("\nEnter data to be"
                   " inserted : \n");
            scanf("%d", &data);
            n->data = data;
            n->next = tmp->next;
            tmp->next = n;
            
            //if tmp is the last node
            //so now n will become the last node
            if (tmp == last) {
                last = n;
            }
            break;
        }else{
            tmp = tmp->next;
        }
    } while (tmp != last->next);
}

///遍历链表操作
void traverseList(void) {
    //if list is empty
    if (last == NULL){
        printf("\nlist is empty\n");
    }else{
        Node * tmp = last->next;
        do {
            printf("\nData= %d\n", tmp->data);
            tmp = tmp->next;
        } while (tmp != last->next);
    }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    insertAtFront();
    insertAtFront();
    traverseList();
    insertafter();
    traverseList();
    return 0;
}
