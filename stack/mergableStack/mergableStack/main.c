//
//  main.c
//  mergableStack
//
//  Created by Fei Yuan on 2021/11/24.
//

#include <stdio.h>
#include <stdlib.h>

struct Node  {
    int data;
    struct Node * next;
};

struct Stack {
    struct Node * head;
    struct Node * tail;
};

struct Node * newNode(int data) {
    struct Node * node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return  node;
}

void push(struct Stack **root, int data){
    struct Node * node = newNode(data);
    struct Stack * head = *root;
    if (head->head == NULL) {
        head->head = node;
        head->tail = node;
    }else{
        node->next = head->head;
        head->head = node;
    }
    printf("%d pushed to stack\n", data);
}

//pop an item from stack
int pop(struct Stack **root) {
    int res;
    struct sNode * top;
    struct Stack * head = *root;

    //if stack is empty then error
    if (head->head == NULL) {
        exit(0);
    }else{
        struct Node * tmp = head->head;
        res = tmp->data;
        head->head = head->head->next;
        free(tmp);
    }
    return res;
}

void merge(struct Stack ** ms1, struct Stack ** ms2) {
    struct Stack * head1 = *ms1;
    struct Stack * head2 = *ms2;

    if (head2->head == NULL) {
        return;
    }else{
        if (head1->head == NULL) {
            head1->head = head2->head;
            head1->tail = head2->tail;
        }else{
            head1->tail->next = head2->head;
            head1->tail = head2->tail;
        }
    }
}

void display(struct Stack ** s) {
    struct Stack * head = *s;
    while (head->head) {
        printf("%d pushed to stack\n", head->head->data);
        head->head = head->head->next;
    }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    struct Stack* q1 = (struct Stack*)malloc(sizeof(struct Stack));
    q1->head = NULL;
    q1->tail = NULL;
    push(&q1, 10);
    push(&q1, 11);
    push(&q1, 12);

    struct Stack* q2 = (struct Stack*)malloc(sizeof(struct Stack));
    q2->head = NULL;
    q2->tail = NULL;
    push(&q2, 20);
    push(&q2, 21);
    push(&q2, 22);
    
    
    merge(&q1, &q2);
    display(&q1);
    return 0;
}
