//
//  main.c
//  ThreadedBinarytree
//
//  Created by Fei Yuan on 2022/1/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

//since right pointer is used for two purposes, the boolean variable
//rightthread is used to indicate whether right pointer points to right child or inorder successor
struct Node {
    int data;
    struct Node * left, * right;
    bool rightThread;
};


//find leftmost node in a tree rooted with n
struct Node * leftMost(struct Node * n) {
    if (n == NULL) {
        return  NULL;
    }
    
    while (n->left != NULL) {
        n = n->left;
    }
    return n;
}

//Insert a Node in Binary Threaded Tree
struct Node * insert(struct Node * root, int ikey) {
    //search for a node with given value
    struct Node * ptr = root;
    struct Node * par = NULL;//Parent of key to be inserted
    while (ptr != NULL) {
        //if key already exitsts, return
        if (ikey == (ptr->data)) {
            printf("Duplicate key !\n");
            return root;
        }
        
        par = ptr;//Update parent pointer
        
        //moving on left subtree
        if (ikey < ptr->data) {
            if (ptr ->left != NULL) {
                ptr = ptr->left;
            }else{
                break;
            }
        }else{
            //move on right subtree
            if (ptr ->rightThread ==  false) {
                ptr = ptr->right;
            }else{
                break;
            }
        }
    }
    
    //create a new node
    struct Node * tmp = (struct Node *)malloc(sizeof(struct Node));
    if (tmp == NULL) {
        printf("stack overflow \n");
        exit(0);
    }
    tmp->data = ikey;
    tmp->rightThread = true;
    
    if (par == NULL) {
        root = tmp;
        tmp->left = NULL;
        tmp->right = NULL;
    }else if (ikey < (par->data)) {
        tmp->right = par;
        par->left = tmp;
    }else{
        tmp->right = par->right;
        par->rightThread = false;
        par->right = tmp;
    }
    return root;
}


// c code to do inorder traversal in a threaded binary tree
void inOrder(struct Node * root) {
    struct Node * cur = leftMost(root);
    
    while (cur != NULL) {
        printf("%d ", cur->data);
        
        //if this node is a thread node,then go to
        //inorder successor
        if (cur->rightThread) {
            cur = cur->right;
        }else{
            //else go to the leftmost child in right subtree
            cur = leftMost(cur->right);
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    struct Node *root = NULL;
     
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 16);
    root = insert(root, 14);
    root = insert(root, 17);
    root = insert(root, 13);
 
    inOrder(root);
    return 0;
}
