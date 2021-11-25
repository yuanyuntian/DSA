//
//  main.c
//  Queue
//
//  Created by Fei Yuan on 2021/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent a queue
struct Queue {
    int front,rear;
    unsigned capacity;
    int * array;
    int size;
};

//create a queue of given capacity.
//It initializes size of queue as 0
struct Queue * createQueue(unsigned capacity) {
    struct Queue * queue = (struct Queue * )malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->rear = -1;
    queue->front = 0;
    queue->size = 0;
    queue->array = (int *)malloc(queue->capacity * sizeof(int));
    return queue;
}

//queue is full when size becomes equal to the capacity
int isFull(struct Queue * queue) {
    return (queue->size == queue->capacity);
}

//queue is empty when size is 0
int isEmpty(struct Queue * queue) {
    return (queue->size == 0);
}


//add an item to the queue
//it change rear and size
void enqueue(struct Queue * queue, int item) {
    if (isFull(queue)) {
        //满
        return;
    }
    queue->rear++;
    queue->rear %= queue->capacity;
    queue->size++;
    queue->array[queue->rear] = item;
    printf("%d enqueued to queue\n", item);
}

//remove an item from queue.It changes front and size
int dequeue(struct Queue * queue) {
    if (isEmpty(queue)) {
        //空
        return INT_MIN;
    }
    int tmp = queue->array[queue->front];
    queue->front++;
    queue->front %= queue->capacity;
    queue->size--;
    return tmp;
}

//get front of queue
int front (struct Queue * queue) {
    if (isEmpty(queue)) {
        //空
        return INT_MIN;
    }
    return queue->array[queue->front];
}

//get rear of queue
int rear(struct Queue * queue){
    if (isEmpty(queue)) {
        //空
        return INT_MIN;
    }
    return queue->array[queue->rear];
}



int main(int argc, const char * argv[]) {
    // insert code here...
    struct Queue* queue = createQueue(4);
     
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
 
    printf("%d dequeued from queue\n\n",
           dequeue(queue));
    
    printf("%d dequeued from queue\n\n",
           dequeue(queue));
    
    printf("%d dequeued from queue\n\n",
           dequeue(queue));
    
    printf("%d dequeued from queue\n\n",
           dequeue(queue));
    
    enqueue(queue, 11);
    enqueue(queue, 12);
    enqueue(queue, 13);
    enqueue(queue, 14);
    enqueue(queue, 15);
    enqueue(queue, 16);
    
 
    printf("Front item is %d\n", front(queue));
    printf("Rear item is %d\n", rear(queue));
    return 0;
}
