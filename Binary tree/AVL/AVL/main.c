//
//  main.c
//  AVL
//
//  Created by Fei Yuan on 2021/12/14.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// left left case
//T1, T2, T3 and T4 are subtrees.
//         z                                      y
//        / \                                   /   \
//       y   T4      Right Rotate (z)          x      z
//      / \          - - - - - - - - ->      /  \    /  \
//     x   T3                               T1  T2  T3  T4
//    / \
//  T1   T2



/*
 left right case
 z                               z                           x
/ \                            /   \                        /  \
y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
/ \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
/ \                        / \
T2   T3                    T1   T2
 
*/

/*
right right case

 z                                y
/  \                            /   \
T1   y     Left Rotate(z)       z      x
   /  \   - - - - - - - ->    / \    / \
  T2   x                     T1  T2 T3  T4
      / \
    T3  T4
 
 */


/**
 right left case
 z                            z                            x
/ \                          / \                          /  \
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
  / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
 x   T4                      T2   y                  T1  T2  T3  T4
/ \                              /  \
T2   T3                           T3   T4
 */

// An AVL tree node
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};
 
// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

//Give a non-empty binary search tree, return the node with minmum key valye found in that tree.
//Note that the entire tree does not need to be searched
struct Node * minValueNode(struct Node * tree) {
    struct Node * current = tree;
    //loop down to find the leftmost leaf
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


//Recursive function to delete a node with given key
//from subtree with given root,it return root of
//the modified subtree
struct Node * deleteNode(struct Node * root, int key) {
    //1.perform standard BST delete
    if (root == NULL) {
        return root;
    }
    
    //if the key to be deleted is smaller than the root's
    //key, then it lies in left subtree
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }else if (key > root->key) {
        // If the key to be deleted is greater than the
        // root's key, then it lies in right subtree
        root->right = deleteNode(root->right, key);
    }else{
        //Case 1: node to be deleted has no children (it is a leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
        }else if (root->left && root->right) {
            //Case 2: node to be deleted has two children
            struct Node * tmp = minValueNode(root->right);
            root->key = tmp->key;
            root->right = deleteNode(root->right, tmp->key);
        }else{
            //Node to be deleted has only one child
            struct Node * tmp = root->left ? root->left :root->right;
            struct Node *curr = root;
            root = tmp;
            free(curr);
        }
    }
    
    //if the tree had only one node then return
    if (root == NULL) {
        return root;
    }
    
    //update height of the current node
    root->height =  1 + max(height(root->left), height(root->right));
    
    //get the balance factor of this node
    //check whether this node become unbalance
    int balance = getBalance(root);
    
    // If this node becomes unbalanced, then there are 4 cases
     
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int main(int argc, const char * argv[]) {
    // insert code here...
     struct Node *root = NULL;
     
      /* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 12);
    root = insert(root, 13);
//    root = insert(root, 0);
//    root = insert(root, 6);
//    root = insert(root, 11);
//    root = insert(root, -1);
//    root = insert(root, 1);
//    root = insert(root, 2);
     
    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */
     
      printf("Preorder traversal of the constructed AVL"
             " tree is \n");
      preOrder(root);
    
    
      root = deleteNode(root, 10);
     
        /* The AVL Tree after deletion of 10
                1
               /  \
              0    9
            /     /  \
           -1    5     11
               /  \
              2    6
        */
     
        printf("\nPreorder traversal after deletion of 10 \n");
        preOrder(root);
     
        return 0;
    
    
    return 0;
}

