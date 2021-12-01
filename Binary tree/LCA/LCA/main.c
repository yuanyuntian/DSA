//
//  main.c
//  LCA
//
//  Created by Fei Yuan on 2021/12/1.
//

#include <stdio.h>
#include <stdlib.h>

//problem solution
//1.如果两个节点不在同一边，那么根节点就是他们的LCA
//2.如果root大于两个节点，那么LCA在left subtree
//3.如果小于，那么LCA在right subtree

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

//find the lowest common ancestor

Node * findLCA(Node *root, int node1, int node2) {
    if (root != NULL) {
        if (root->data > node1 && root->data > node2) {
            return findLCA(root->leftChild, node1, node2);
        }
        if (root->data < node1 && root->data < node2) {
            return findLCA(root->rightChild, node1, node2);
        }
        return root;
    }
    return NULL;
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
    insert(&root, 1);

    Node *t = findLCA(root, 11,1);

    return 0;
}
