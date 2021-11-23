//
//  main.c
//  middleOfstack
//
//  Created by Fei Yuan on 2021/11/23.
//

#include <stdio.h>
#include <stdlib.h>


//设计一个stack，对中间元素进行操作，时间复杂度是O(1)
//push() 添加栈顶元素
//pop()移除栈顶元素
//findMiddle()返回中间元素
//deleteMiddle()删除中间元素
//stack可以用数组和链表来实现，但是我们要去查找和删除元素必须满足O(1)，而且还要求移除元素，显然数组不能满足
//single linked list在两个方向上移除中间元素基本上不可能
//好的办事就是用Double Linked List(dll),我们能够通过中间指针操作delete，时间复杂度O(1),也能前后移动中间元素

//A Double linked list Node
struct DLLNode {
    struct DLLNode * prev;
    int data;
    struct DLLNode * next;
};

/* Representation of the stack data structure that supports
   findMiddle() in O(1) time.  The Stack is implemented
   using Doubly Linked List. It maintains pointer to head
   node, pointer to middle node and count of nodes */

struct myStack {
    struct DLLNode * head;
    struct DLLNode * mid;
    int count;
};

//create the stack data structure
struct myStack * createMyStack() {
    struct myStack * ms = (struct myStack *)malloc(sizeof(struct myStack));
    ms->count = 0;
    return ms;
}

//push an element to the stack

void push(struct myStack * ms, int new_data) {
    //allocate DLLNode and put in data
    struct DLLNode * new_DLLNode = (struct DLLNode *)malloc(sizeof(struct DLLNode));
    new_DLLNode->data = new_data;
    ms->count += 1;
    new_DLLNode->prev = NULL;
    new_DLLNode->next = ms->head;

    //change mid pointer in two cases
    //1.Linked list is empty
    //2.Number of nodes in linked list is odd
    if (ms->count == 1) {
        ms->mid = new_DLLNode;
    }else{
        ms->head->prev = new_DLLNode;
        if (ms->count & 1) {//Update mid if ms->count is odd
            ms->mid = ms->mid->prev;
        }
    }
    //move head to point to the new DLLNode
    ms->head = new_DLLNode;
}

//pop an element from stack
int pop(struct myStack * ms) {
    //stack underflow
    if (ms->count == 0) {
        return -1;
    }
    
    struct DLLNode * head = ms->head;
    int item = head->data;
    ms->head = head->next;
    
    //if linked list don't become empty, update prev of new head as null
    if (ms->head != NULL) {
        ms->head->prev = NULL;
    }
    
    ms->count -= 1;
    
    //update the mid pointer when we have even number oif elements in the stack,i,e move down the mid pointer
    if (!((ms->count)&1)) {
        ms->mid = ms->mid->next;
    }
    free(head);
    return item;
}

//find middle of the stack
int findMiddle(struct myStack *ms) {
    if (ms->count == 0) {
        return -1;
    }
    return ms->mid->data;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    /* Let us create a stack using push() operation*/
    struct myStack* ms = createMyStack();
    push(ms, 11);
    push(ms, 22);
//    push(ms, 33);
//    push(ms, 44);
//    push(ms, 55);
//    push(ms, 66);
//    push(ms, 77);
 
//    printf("Item popped is %d\n", pop(ms));
//    printf("Item popped is %d\n", pop(ms));
    printf("Middle Element is %d\n", findMiddle(ms));
    return 0;
}
