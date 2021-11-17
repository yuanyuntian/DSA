//
//  main.c
//  DoubleCircularlinkedlist
//
//  Created by Fei Yuan on 2021/11/11.
//

#include <stdio.h>
#include <stdlib.h>

//Node of a doubly linked list
struct Node {
    int data;
    struct Node * next;//Pointer to next node in DLL
    struct Node * prev;//Pointer to previous node in DLL
};

//Given a reference (pointer to pointer) to the head of a
//and a int.inserts a new node on the front of the list
void push(struct Node ** head_ref, int new_data) {
    //alloccate node
    struct Node * new_node = (struct Node *)malloc(sizeof(struct Node));
    
    //put in the data
    new_node->data = new_data;
    
    //make next of new node as head and previous as NULL
    new_node->next = (*head_ref);
    new_node->prev = NULL;
    
    //change prev of head node to new node
    if ((*head_ref) != NULL) {
        (*head_ref)->prev = new_node;
    }
    
    //move the head to point to the new node
    (*head_ref) = new_node;
}

//Give a node as prev_node, insert a new node after the given node
void insertAfter(struct Node * prev_node, int new_data) {
    //check if the given prev_node is NULL
    if (prev_node == NULL) {
        return;
    }
    
    //allocate new node
    struct Node * new_node = (struct Node *)malloc(sizeof(struct Node));

    new_node->data = new_data;
    
    //make next of new node as next of prev_node
    new_node->next = prev_node->next;
    
    //make the next of prev_node as new_node
    prev_node->next = new_node;
    
    //Make prev_node as previous of new_node
    new_node->prev = prev_node;
    
    //change previous of new_node's next node
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
