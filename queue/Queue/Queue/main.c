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
};

//create a queue of given capacity.
//It initializes size of queue as 0
struct Queue * createQueue(unsigned capacity) {
    struct Queue * queue = (struct Queue * )malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = 0;
    
    queue->array = (int *)malloc(queue->capacity * sizeof(int));
    return queue;
}




//add an item to the queue
//it change rear and size
void enqueue(struct Queue * queue, int item) {
    if ((queue->rear + 1) % queue->capacity == queue->front) {
        //满
        return;
    }
    queue->array[queue->rear % queue->capacity] = item;
    queue->rear++;
    printf("%d enqueued to queue\n", item);
}

//remove an item from queue.It changes front and size
int dequeue(struct Queue * queue) {
    if (queue->front == queue->rear % queue->capacity) {
        //空
        return INT_MIN;
    }
    //front不再直接 +1，而是+1后同capacity进行比较，如果=capacity，则直接跳转到 a[0]
    queue->front = (queue->front + 1) % queue->capacity;
    return queue->front;
}

//get front of queue
int front (struct Queue * queue) {
    if (queue->front == queue->rear % queue->capacity) {
        //空
        return INT_MIN;
    }
    return queue->array[queue->front];
}

//get rear of queue
int rear(struct Queue * queue){
    if (queue->front == queue->rear % queue->capacity) {
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
 
    printf("Front item is %d\n", front(queue));
    printf("Rear item is %d\n", rear(queue));
    return 0;
}
