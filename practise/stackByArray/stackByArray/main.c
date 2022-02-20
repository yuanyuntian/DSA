//
//  main.c
//  stackByArray
//
//  Created by yuanf on 2022/2/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define CAPACITY  1000
int stack[CAPACITY];
int top = -1;

bool push(int value) {
    if (top >= CAPACITY) {
        return false;
    }
    stack[++top] = value;
    return true;
}

int pop(void) {
    if (top < 0) {
        return 0;
    }
    int e = stack[top--];
    return e;
}

int peek(void) {
    if (top < 0) {
        return 0;
    }
    int e = stack[top];
    return e;
}

bool isEmpty(void) {
    return top < 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
