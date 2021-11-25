//
//  main.c
//  priorityOfQueue
//
//  Created by Fei Yuan on 2021/11/25.
//

#include <stdio.h>
#include <stdlib.h>

//Node
typedef struct Node{
    int data;
    
    //lower values indiccate highter priority
    int priority;
    struct Node * next;
}Node;

//create A new Node
Node * newNode(int d, int p) {
    Node * tmp = (Node *)malloc(sizeof(Node));
    tmp->data = d;
    tmp->priority = p;
    tmp->next = NULL;
    return tmp;
}

//return the value at head
int peek(Node ** head) {
    return (*head)->data;
}

//remove the element with the highest priority from the list
void pop(Node ** head) {
    Node * tmp = *head;
    (*head) = (*head)->next;
    free(tmp);
}

//push according to priority
void push(Node **head, int d, int p) {
    Node * start = (*head);
    
    //create new Node
    Node * tmp = newNode(d, p);
    
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p) {
        //insert new node before head
        tmp->next = *head;
        *head = tmp;
    }else{
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL && start->next->priority < p) {
            start = start->next;
        }
        
        // Either at the ends of the list
        // or at required position
        tmp->next = start->next;
        start->next = tmp;
    }
}

// Function to check is list is empty
int isEmpty(Node** head)
{
    return (*head) == NULL;
}


int main(int argc, const char * argv[]) {
    // Create a Priority Queue
        // 7->4->5->6
    Node* pq = newNode(4, 1);
    push(&pq, 5, 2);
    push(&pq, 6, 3);
    push(&pq, 7, 0);
    
    while (!isEmpty(&pq)) {
        printf("%d ", peek(&pq));
        pop(&pq);
    }
    
    return 0;
}
