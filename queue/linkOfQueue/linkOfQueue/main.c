//
//  main.c
//  linkOfQueue
//
//  Created by Fei Yuan on 2021/11/25.
//

#include <stdio.h>
#include <stdlib.h>

//linked list(LL) node to store a queue entry
struct Node {
    int key;
    struct Node * next;
};

// queue, front stores the front node of LL and rear
//stores the last node of LL
struct Queue {
    struct Node * front, *rear;
};

//create a new linked list node
struct Node * newNode(int k) {
    struct Node* tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->key = k;
    tmp->next = NULL;
    return tmp;
};

//create an empty queue
struct Queue * createQueue(void){
    struct Queue * q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enQueue(struct Queue * q, int k) {
    //create
    struct Node * tmp = newNode(k);
    
    if (q->rear == NULL) {
        q->front = q->rear = tmp;
        return;
    }
    //add new node at the end of queue and change rear
    q->rear->next = tmp;
    q->rear = tmp;
}

// remove a key from given queue q
void deQueue(struct Queue * q) {
    //if empty
    if (q->front == NULL) {
        return;
    }
    
    //store previous front and move front one node ahead
    struct Node * tmp  = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(tmp);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    struct Queue* q = createQueue();
    enQueue(q, 10);
    enQueue(q, 20);
    deQueue(q);
    deQueue(q);
    enQueue(q, 30);
    enQueue(q, 40);
    enQueue(q, 50);
    deQueue(q);
    printf("Queue Front : %d \n", q->front->key);
    printf("Queue Rear : %d", q->rear->key);
    return 0;
}
