//
//  main.c
//  QueueOfStack
//
//  Created by Fei Yuan on 2021/11/23.
//

#include <stdio.h>
#include <stdlib.h>

//structure of a stack node
struct sNode {
    int data;
    struct sNode * next;
};

//push an item to stack
void push(struct sNode ** top_ref, int new_data);

//pop an item from stack
int pop(struct sNode ** top_ref);

//structure of queue having two stacks
struct queue {
    struct sNode * stack1;
    struct sNode * stack2;
};

//enqueue an item to queue
void enQueue(struct queue * q, int x) {
    push(&q->stack1, x);
}

//deQueue an item from queue
int deQueue(struct queue *q) {
    int x;
    //if both stacks are empty then error
    if (q->stack1 == NULL && q->stack2 == NULL) {
        printf("Q is empty");
        exit(0);
    }
    
    //move element s from stack1 to stack 2 only if stack2 is empty
    if (q->stack2 == NULL) {
        while (q->stack1 != NULL) {
            x = pop(&q->stack1);
            push(&q->stack2, x);
        }
    }
    x = pop(&q->stack2);
    return x;
}

//push an item to stack
void push(struct sNode ** top_ref, int new_data) {
    //allocate node
    struct sNode *new_node = (struct sNode *)malloc(sizeof(struct sNode));
    if (new_node == NULL) {
        exit(0);
    }
    
    //put in the data
    new_node->data = new_data;
    
    //link the old list off the new node
    new_node->next = (*top_ref);
    
    //move the head to point to the new node
    (*top_ref) = new_node;
}

//pop an item from stack
int pop(struct sNode ** top_ref) {
    int res;
    struct sNode * top;
    
    //if stack is empty then error
    if (*top_ref == NULL) {
        exit(0);
    }else{
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
