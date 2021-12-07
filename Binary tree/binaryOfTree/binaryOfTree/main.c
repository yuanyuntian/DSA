//
//  main.c
//  binaryOfTree
//
//  Created by Fei Yuan on 2021/11/30.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node * leftChild;
    struct Node * rightChild;
}Node;

void insert(Node ** tree, int value) {
    Node * tmp = NULL;
    if ((*tree) == NULL) {
        tmp = (Node *)malloc(sizeof(Node));
        tmp->leftChild = NULL;
        tmp->rightChild = NULL;
        tmp->data = value;
        *tree = tmp;
        return;
    }
    if (value < (*tree)->data) {
        insert(&((*tree)->leftChild), value);
    }else{
        insert(&((*tree)->rightChild), value);
    }
}



//Give a non-empty binary search tree, return the node with minmum key valye found in that tree.
//Note that the entire tree does not need to be searched
Node * minValueNode(Node ** tree) {
    Node * current = *tree;
    //loop down to find the leftmost leaf
    while (current && current->leftChild != NULL) {
        current = current->leftChild;
    }
    return current;
}
Node * search(Node ** tree, int value) {
    if (!(*tree)) {
        return NULL;
    }
    if (value == (*tree)->data) {
        return *tree;
    }else if (value < (*tree)->data) {
        search(&((*tree)->leftChild), value);
    }else{
        search(&((*tree)->rightChild), value);
    }
    return NULL;
}

//Binary search Tree(Delete)
//1.Deleting a node with no children: remove the node from the tree
//2.Deleting a node with one child: remove the node and replace it with its child
//3.

void deleteNode(Node ** tree, int key) {
    //base case
    if ((*tree) == NULL) {
        return ;
    }
    
    //if the key to be deleted is smaller than the root's key, then  it lies in left subtree
    if (key < (*tree)->data) {
        deleteNode(&((*tree)->leftChild), key);
    }else if(key > (*tree)->data) {
        //if hte key to be deleted is greater than the root's key, then it lies in the right subtree
        deleteNode(&((*tree)->rightChild), key);
    }else{
        //if key is the same as root's key, then this is the node to be deleted
        //node with only one child or no child
        
        //Case 1: node to be deleted has no children (it is a leaf node)
        if ((*tree)->leftChild == NULL && (*tree)->rightChild == NULL) {
            free(*tree);
        }
        //Case 2: node to be deleted has two children
        else if ((*tree)->leftChild && (*tree)->rightChild){
            //get the inorder successor
            //(samllest in the right subtree)
            Node * tmp = minValueNode(&((*tree)->rightChild));
            (*tree)->data = tmp->data;
            deleteNode(&((*tree)->rightChild), tmp->data);
        }
        //Node to be deleted has only one child
        else{
            Node * tmp = (*tree)->leftChild ? (*tree)->leftChild :(*tree)->rightChild;
            Node *curr = (*tree);
            *tree = tmp;
            free(curr);
        }
    }
}



//find the height of tree using Recursion
int heightOftree(Node ** tree) {
        
    if ((*tree) == NULL) {
        return 0;
    }
    
    if ((*tree)->leftChild == NULL && (*tree)->rightChild == NULL) {
        return 1;
    }
    
    int l = heightOftree(&(*tree)->leftChild);
    int r = heightOftree(&(*tree)->rightChild);
    
    return fmax(l, r) + 1;
}

//it displays in order. First root node,then left node and then right node
void displayPreOrder(Node ** tree) {

    if ((*tree) != NULL) {
        printf("%d\n", (*tree)->data);
        displayPreOrder(&(*tree)->leftChild);
        displayPreOrder(&(*tree)->rightChild);
    }
}

//it displays in order. first left node, then root node,then right node
void displayInOrder(Node ** tree) {

    if ((*tree) != NULL) {
        displayInOrder(&(*tree)->leftChild);
        printf("%d\n", (*tree)->data);
        displayInOrder(&(*tree)->rightChild);
    }
}

//it displays in order. first left node, then right node,then root node
void displayPostOrder(Node ** tree) {
    if ((*tree) != NULL) {
        displayPostOrder(&(*tree)->leftChild);
        displayPostOrder(&(*tree)->rightChild);
        printf("%d\n", (*tree)->data);
    }
}


void clearTree(Node ** tree) {
    if (!(*tree)) {
        return ;
    }
    clearTree(&(*tree)->leftChild);
    clearTree(&(*tree)->rightChild);
    free(*tree);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    Node * root = NULL;
    insert(&root, 10);
    insert(&root, 11);
    insert(&root, 12);
    insert(&root, 13);
    insert(&root, 15);
    insert(&root, 9);
    insert(&root, 5);
    
    int h = heightOftree(&root);
    printf("pre order\n");

    deleteNode(&root, 12);
    
    displayPreOrder(&root);
    
    
    printf("in order\n");
    displayInOrder(&root);
    
    printf("Post order\n");
    displayPostOrder(&root);

    return 0;
}
