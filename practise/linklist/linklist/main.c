//
//  main.c
//  linklist
//
//  Created by yuanf on 2022/2/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct linklist {
    int val;
    struct linklist * next;
};

struct linklist* head;
struct linklist* tail;
int size;


void createlinklist(void);
void insert(int position, int value);
void delete(int value);
int search(int value);
int update(int oldValue, int newValue);


void createlinklist(void) {
    head = NULL;
    tail = NULL;
    size = 0;
}

void insert(int position, int value) {
    if (position < 0) {
        return;
    }
    
    struct linklist * newNode = (struct linklist *)malloc(sizeof(struct linklist *));
    newNode->val = value;
    newNode->next = NULL;
    
    if (position == 0) {
        //头插法
        newNode->next = head;
        head = newNode;
        if (tail == NULL) {
            tail = newNode;
        }
        size ++;
    }else if (position == size) {
        //尾插法
        tail->next = newNode;
        tail = newNode;
    }else{
        //中间插法
        struct linklist * prev = head;
        for (int i = 0; i < position - 1; i ++) {
            prev = prev->next;
        }
        struct linklist * next = prev->next;
        newNode->next = next;
        prev->next = newNode;
        size ++;
    }
}

void delete(int value) {
    //头结点
    if (head != NULL && head->val == value) {
        head = head->next;
        size--;
        if (size == 0) {
            tail = NULL;
        }
    }else{
        struct linklist * prev = head;
        struct linklist * cur = head;
        while (prev != NULL && cur != NULL) {
            if (cur->val == value) {
                if (cur == tail) {
                    tail = prev;
                }
                prev->next = cur->next;
                size --;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }
}

int search(int value) {
    struct linklist * cur = head;
    for (int index = 0; cur != NULL; index ++) {
        if (cur->val == value) {
            return  index;
        }else{
            cur = cur->next;
        }
    }
    return -1;
}

int update(int oldValue, int newValue) {
    struct linklist * cur = head;
    for (int index = 0; cur != NULL; index ++) {
        if (cur->val == oldValue) {
            cur->val = newValue;
            return  index;
        }else{
            cur = cur->next;
        }
    }
    return -1;
}

void display(void) {
    struct linklist * cur = head;
    for (int i = 0; cur != NULL; i++) {
        printf("%d\n", cur->val);
        cur = cur->next;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...

    createlinklist();
    insert(0, 10);
    insert(0, 11);
    insert(0, 12);
    insert(0, 13);
    insert(0, 14);
    
    delete(13);

    display();
    return 0;
}
