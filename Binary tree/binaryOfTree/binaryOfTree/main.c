//
//  main.c
//  binaryOfTree
//
//  Created by Fei Yuan on 2021/11/30.
//

#include <stdio.h>
#include <stdlib.h>

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
    printf("pre order\n");

    displayPreOrder(&root);
    
    
    printf("in order\n");
    displayInOrder(&root);
    
    printf("Post order\n");
    displayPostOrder(&root);

    return 0;
}
