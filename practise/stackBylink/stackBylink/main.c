//
//  main.c
//  stackBylink
//
//  Created by yuanf on 2022/2/20.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

struct stackNode {
    int val;
    struct stackNode * next;
};

struct stackNode * top;

void createStack(void) {
    top = NULL;
}


void push(int value) {
    struct stackNode *newNode = (struct stackNode *)malloc(sizeof(struct stackNode *));
    newNode->val = value;
    newNode->next = NULL;
    if (top == NULL) {
        top = newNode;
    }else{
        newNode->next = top;
        top = newNode;
    }
}

int pop(void) {
    if (top == NULL) {
        return INT_MIN;
    }
    int v = top->val;
    top = top->next;
    return v;
}

int peek(void) {
    if (top == NULL) {
        return INT_MIN;
    }
    return top->val;
}

bool isEmpty(void) {
    return top == NULL;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    createStack();
    push(100);
    push(101);
    push(102);
    pop();
    printf("%d", peek());
    return 0;
}
