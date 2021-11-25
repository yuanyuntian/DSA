//
//  main.c
//  LRUOfQueue
//
//  Created by Fei Yuan on 2021/11/25.
//

#include <stdio.h>
#include <stdlib.h>

//A queue Node
typedef struct Node{
    struct Node * prev, * next;
    unsigned pageNumber;//the page number stored in this Node
}Node;

//A queue(A FIFO collection of Queue Nodes)
typedef struct  Queue{
    unsigned count;//number of filled frames
    unsigned numberOfFrames;//total number of frames
    Node * front, * rear;
}Queue;

//a hash that collection of pointers to Queue Nodes
typedef struct Hash{
    int capacity;//how many pages can be there
    Node ** array;//a array of queue nodes
}Hash;

//create a new queue Node.The queue node
//the queue node will store the given pageNumber
Node * newNode(unsigned pageNumber) {
    //allocate memory and assign pageNumber
    Node * tmp = (Node *)malloc(sizeof(Node));
    tmp->pageNumber = pageNumber;
    
    //initialize prev and next as NULL
    tmp->prev = tmp->next = NULL;
    return tmp;
}

//create an empty queue
//the queue can have at most numberOfFrames nodes
Queue * createQueue(int numberOfFrames) {
    Queue * queue = (Queue *)malloc(sizeof(Queue));
    
    //the queue is empty
    queue->count = 0;
    queue->front = queue->rear = NULL;
    
    //number of frames that can be stored in memory
    queue->numberOfFrames = numberOfFrames;
    return queue;
}

//create an empty hash of given capacity
Hash * createHash(int capacity) {
    //allocate memory for hash
    Hash * hash = (Hash *)malloc(sizeof(Hash));
    hash->capacity = capacity;
    
    //create an array of pointers for refering queue nodes
    hash->array = (Node**)malloc(hash->capacity *sizeof(Node *));
    
    //initialize all hash entries as empty
    int i;
    for (i = 0; i < hash->capacity; ++i) {
        hash->array[i] = NULL;
    }
    return  hash;
}

// check if there is slot available in memory
int AreAllFramesFull(Queue * queue) {
    return queue->count == queue->numberOfFrames;
}

//check if queue is empty
int isQueueEmpty(Queue * queue) {
    return queue->rear == NULL;
}

//delete a frame from queue
void deQueue(Queue * q) {
    if (isQueueEmpty(q)) {
        return;
    }
    
    //if this is the only node in list, then change front
    if (q->front == q->rear) {
        q->front = NULL;
    }
    
    //change rear and remove the previous rear
    Node * tmp = q->rear;
    q->rear = q->rear->prev;
    
    if (q->rear) {
        q->rear->next = NULL;
    }
    
    free(tmp);
    //decrement the number of full frames by 1
    q->count --;
}

//add a page with given pagenumber to both queue and hash
void Enqueue(Queue *q, Hash * hash, unsigned pageNumber) {
    
    //if all framse are full, remove the page at the rear
    if (AreAllFramesFull(q)) {
        //remove page from hash
        hash->array[q->rear->pageNumber] = NULL;
        deQueue(q);
    }
    
    //create a new node with given page number
    //and and the new node to the front of queue
    Node * tmp = newNode(pageNumber);
    tmp->next = q->front;
    
    //if queue is empty, change both front and rear pointers
    if (isQueueEmpty(q)) {
        q->rear = q->front = tmp;
    }else{
        //change the front
        q->front->prev = tmp;
        q->front = tmp;
    }
    
    // add page entry to hash also
    hash->array[pageNumber] = tmp;
    
    //increment number of full frames
    q->count ++;
}

// This function is called when a page with given 'pageNumber' is referenced
// from cache (or memory). There are two cases:
// 1. Frame is not there in memory, we bring it in memory and add to the front
// of queue
// 2. Frame is there in memory, we move the frame to front of queue
void ReferencePage(Queue * queue, Hash * hash, unsigned pageNumbier) {
    Node * rePage = hash->array[pageNumbier];
    
    //the page is not in cache, bring it
    if (rePage == NULL) {
        Enqueue(queue, hash, pageNumbier);
    }else if (rePage != queue->front) {
        //page is there and not at front, change pointer
        //unlink requested page from its current location in queue
        rePage->prev->next = rePage->next;
        if (rePage->next) {
            rePage->next->prev = rePage->prev;
        }
        
        //if the requested page is rear ,then change rear as this node will be moved to front
        if (rePage == queue->rear) {
            queue->rear = rePage->prev;
            queue->rear->next = NULL;
        }
        // Put the requested page before current front
        rePage->next = queue->front;
        rePage->prev = NULL;
 
        // Change prev of current front
        rePage->next->prev = rePage;
 
        // Change front to the requested page
        queue->front = rePage;
    }
    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // Let cache can hold 4 pages
    Queue* q = createQueue(4);
 
    // Let 10 different pages can be requested (pages to be
    // referenced are numbered from 0 to 9
    Hash* hash = createHash(10);
 
    // Let us refer pages 1, 2, 3, 1, 4, 5
    ReferencePage(q, hash, 1);
    ReferencePage(q, hash, 2);
    ReferencePage(q, hash, 3);
    ReferencePage(q, hash, 1);
    ReferencePage(q, hash, 4);
    ReferencePage(q, hash, 5);
 
    // Let us print cache frames after the above referenced pages
    printf("%d ", q->front->pageNumber);
    printf("%d ", q->front->next->pageNumber);
    printf("%d ", q->front->next->next->pageNumber);
    printf("%d ", q->front->next->next->next->pageNumber);
    return 0;
}
