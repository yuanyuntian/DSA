//
//  main.c
//  levelOrderBinaryTree
//
//  Created by Fei Yuan on 2022/1/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct node {
    int data;
    struct node * left, *right;
};

void printCurrentLevel(struct node * root,int level);

int height(struct node * node);

struct node * newNode(int data);

//print level order traversal a tree
void printLevelOrder(struct node * root) {
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++) {
        printCurrentLevel(root, i);
    }
}

//print nodes at a current level
void printCurrentLevel(struct node * root,int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d", root->data);
    }else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

//compute the height of a tree:the number of nodes along the longest path from rhe root node
//down to the farthest leaf node
int height(struct node * node) {
    if (node == NULL) {
        return 0;
    }else{
        //compute the height of each subtree
        int lheight = height(node->left);
        int rheight = height(node->right);
        
        //use the large one
        if (lheight > rheight) {
            return (lheight + 1);
        }else{
            return (rheight + 1);
        }
    }
}

struct node * newNode(int data) {
    struct node * node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    struct node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printf("Level Order traversal of binary tree is \n");
    printLevelOrder(root);

    return 0;
}
