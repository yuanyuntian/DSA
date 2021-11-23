//
//  main.c
//  stackOfNode
//
//  Created by Fei Yuan on 2021/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Pros:the linked list implementation of a stack can grow and shrink according to the needs of run time
//Cons:Requires extra memory due to involvement of pointers

//A structure to represent a stack
struct StackNode{
    int data;
    struct StackNode * next;
};

struct StackNode * newNode(int data) {
    struct StackNode * stackNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    stackNode->data =data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(struct StackNode * root) {
    return !root;
}

void push(struct StackNode **root, int data){
    struct StackNode * stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
    printf("%d pushed to stack\n", data);

}

int pop(struct StackNode ** root) {
    if (isEmpty(*root)) {
        return INT_MIN;
    }
    
    struct StackNode * temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

int peek(struct StackNode * root) {
    if (isEmpty(root)) {
        return INT_MIN;
    }
    return root->data;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    struct StackNode* root = NULL;
 
    push(&root, 10);
    push(&root, 20);
    push(&root, 30);
 
    printf("%d popped from stack\n", pop(&root));
 
    printf("Top element is %d\n", peek(root));
    
    
    return 0;
}
