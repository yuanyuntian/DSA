//
//  main.c
//  queueByArray
//
//  Created by yuanf on 2022/2/20.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define CAPACITY 100

int front,rear,size,array[CAPACITY];

void creatQueue(void) {
    front = rear = size = 0;
}

bool isFull(void) {
    return size == CAPACITY;
}

bool isEmpty(void) {
    return size == 0;
}

void enqueue(int value) {
    if (isFull()) {
        return;
    }
    array[rear] = value;
    rear = (rear + 1)%CAPACITY;
    size++;
}

int dequeue(void) {
    if (isEmpty()) {
        return INT_MIN;
    }
    int item = array[front];
    front = (front + 1) %CAPACITY;
    size --;
    return item;
}

int peek(void) {
    if (isEmpty()) {
        return INT_MIN;
    }
    return array[front];
}

int main(int argc, const char * argv[]) {
    // insert code here...
    creatQueue();
    enqueue(10);
    dequeue();

    enqueue(11);
    enqueue(12);
    enqueue(13);
    enqueue(14);
    
    printf("%d\n", peek());
    dequeue();
    printf("%d\n", peek());

    return 0;
}
