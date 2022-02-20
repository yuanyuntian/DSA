//
//  main.c
//  queueBylink
//
//  Created by yuanf on 2022/2/20.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>


struct queueNode {
    int val;
    struct queueNode * next;
};

struct queueNode * front;
struct queueNode * rear;


void enqueue(int value) {
    struct queueNode * newNode = (struct queueNode *)malloc(sizeof(struct queueNode *));
    newNode->val = value;
    newNode->next = NULL;
    
    if (rear == NULL) {//empty
        rear = front = newNode;
    }
    rear->next = newNode;
    rear = newNode;
}

int dequeue(void) {
    if (front == NULL) {
        return  INT_MIN;
    }
    struct queueNode * f = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;;
    }
    return f->val;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    return 0;
}
