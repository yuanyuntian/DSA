//
//  main.c
//  priorityQueue
//
//  Created by Fei Yuan on 2022/2/21.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

struct PriorityQueue {
    int val;
    int priority;
    struct PriorityQueue *next;
};

struct PriorityQueue * head = NULL;

bool isEmpty(void) {
    return head == NULL;
}

//priority 大的排在最前面
void push(int value, int priority) {
    
    struct PriorityQueue *newNode = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue *));
    newNode->val = value;
    newNode->priority = priority;
    
    if (head == NULL) {
        head = newNode;
        return;
    }
    
    struct PriorityQueue * cur = head;
    if (head->priority < priority) {
        newNode->next = head;
        head = newNode;
    }else{
        while (cur->next != NULL && cur->next->priority > priority) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

struct PriorityQueue * peek(void) {
    return  head;
}

struct PriorityQueue * pop(void) {
    if (head == NULL) {
        return NULL;
    }
    struct PriorityQueue *node = head;
    head = head->next;
    return node;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    push(100, 10);
    push(101, 11);
    push(102, 12);
    push(103, 13);

    printf("%d", peek()->val);
    return 0;
}
