//
//  main.c
//  diameterOfBinarytree
//
//  Created by Fei Yuan on 2022/1/11.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct node {
    int data;
    struct node * left, * right;
};

struct node * newNode(int data);

int max(int a,int b){return (a > b) ?a:b;}

int height(struct node * node);

int diameter(struct node * tree) {
    //base case where tree is empty
    if (tree == NULL) {
        return 0;
    }
    
    //get height of left and right sub-tree
    int lheight = height(tree->left);
    int rheight = height(tree->right);
    
    //get the diameter of left and right
    int ldiameter = diameter(tree->left);
    int rdiameter = diameter(tree->right);
    
    // Return max of following three
    // 1) Diameter of left subtree
    // 2) Diameter of right subtree
    // 3) Height of left subtree + height of right subtree + 1
    return max(lheight + rheight + 1,
               max(ldiameter, rdiameter));
}

// UTILITY FUNCTIONS TO TEST diameter() FUNCTION

//  The function Compute the "height" of a tree. Height is
//  the number f nodes along the longest path from the root
//   node down to the farthest leaf node.
int height(struct node* node)
{
    // base case tree is empty
    if (node == NULL)
        return 0;

    // If tree is not empty then height = 1 + max of left
    // height and right heights
    return 1 + max(height(node->left), height(node->right));
}

// Helper function that allocates a new node with the
// given data and NULL left and right pointers.
struct node* newNode(int data)
{
    struct node* node
        = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return (node);
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
     struct node* root = newNode(1);
//     root->left = newNode(2);
//     root->right = newNode(3);
//     root->left->left = newNode(4);
//     root->left->right = newNode(5);

     // Function Call
     printf("Diameter of the given binary tree is %d\n",
            diameter(root));

     return 0;
}
