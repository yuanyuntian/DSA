//
//  main.c
//  InorderOfStack
//
//  Created by Fei Yuan on 2022/1/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
//1.create an empty stack S
//2.Initialize current node as root
//3. Push the current node to S and set current = current->left
//    until current is NULL
//4.If current is NULL and stack is not empty then
//   a).Pop the top item from stack
//   b).print the popped item, set current = popped_item->right
//   c).go to step 3
//5.If current is NULL and stack is empty then we are done.


struct tNode{
    int data;
    struct tNode * left;
    struct tNode * right;
};

//structure of a stack node,Linked list implementation is used for stack.A
//stack node contains a pointer to tree node and a pointer to next stack node
struct sNode {
    struct tNode * t;
    struct sNode * next;
};

//stack related function
void push(struct sNode **top_ref, struct tNode * t);
struct tNode * pop(struct sNode **top_ref);
bool isEmpty(struct sNode * top);

//Iterative function for inorder tree traversal
void inOrder(struct tNode * root) {
    //set current to root of binary tree
    struct tNode * current = root;
    struct sNode * s = NULL;//initialize stack s
    bool done = 0;
    while (!done) {
        //reach the left most tnode of the current tnode
        if (current != NULL) {
            //place pointer to a tree node on the stack before traversing
            //the node's left subtree
            push(&s, current);
            current = current->left;
        }else{
            //backtrack from the empty subtree and visit the tnode
            //at the top of the stack;however, if the stack is empty you are done
            if (!isEmpty(s)) {
                current = pop(&s);
                printf("%d", current->data);
                current = current ->right;
            }else{
                done = 1;
            }
        }
        

    }
}

//return true if stack is empty,otherwise false
bool isEmpty(struct sNode * top) {
    return  (top == NULL)?1 :0;
}


//pop an item from stack
struct tNode * pop(struct sNode ** top_ref) {
    struct tNode * res;
    struct sNode * top;
    
    //if snode is empty then error
    if (isEmpty(* top_ref)) {
        printf("stack underflow\n");
        exit(0);
    }else{
        top = *top_ref;
        res = top->t;
        *top_ref = top->next;
        free(top);
        return  res;
    }
}

//push an item to snode
void push(struct sNode **top_ref, struct tNode * t) {
    //allocate tnode
    struct sNode * new_tNode = (struct sNode*)malloc(sizeof(struct sNode));
    
    if (new_tNode == NULL) {
        printf("stack overflow \n");
        exit(0);
    }
    
    //put in the data
    new_tNode->t = t;
    
    //link the old list off the new tnode
    new_tNode->next = (*top_ref);
    
    //move the head to point to the new tnode
    (*top_ref) = new_tNode;
}

struct tNode * newNode(int data) {
    struct tNode * tnode = (struct tNode*)malloc(sizeof(struct tNode));
    tnode->data = data;
    tnode->left = NULL;
    tnode->right = NULL;
    return tnode;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    /* Constructed binary tree is
              1
            /   \
          2      3
        /  \
      4     5
    */
    struct tNode *root = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
   
    inOrder(root);
    return 0;
}
