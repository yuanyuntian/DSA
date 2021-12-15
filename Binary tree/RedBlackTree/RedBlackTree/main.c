//
//  main.c
//  RedBlackTree
//
//  Created by Fei Yuan on 2021/12/14.
//

#include <stdio.h>
#include <stdlib.h>
/**
 A red-black tree is a kind of self-balancing binary search tree where each node has an extra bit, and that bit is often interpreted as the colour (red or black)
 
 Rules:
   
 1.every node has a colour eithor red or black
 2.the root of tree is always black;
 3.there are no two adjacent red nodes(A red node cannot have a red parent or red child)
 4.Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.
 
 Comparison with AVL Tree:
 The AVL trees are more balanced compared to Red-Black Trees, but they may cause more rotations during insertion and deletion. So if your application involves frequent insertions and deletions, then Red-Black trees should be preferred. And if the insertions and deletions are less frequent and search is a more frequent operation, then AVL tree should be preferred over Red-Black Tree.
 */

//structure to represent each node in a red-black tree
typedef struct Node{
    int d;//data
    int c;//1-red 0-black
    struct Node * p;//parent
    struct Node * r;//right child
    struct Node * l;//left child
}Node;

//global root for the entire tree
Node * root = NULL;

// function to perform BST insertion of a node
Node * bst(Node * trav,   Node* temp){
    // If the tree is empty,
    // return a new node
    if (trav == NULL)
        return temp;
 
    // Otherwise recur down the tree
    if (temp->d < trav->d)
    {
        trav->l = bst(trav->l, temp);
        trav->l->p = trav;
    }
    else if (temp->d > trav->d)
    {
        trav->r = bst(trav->r, temp);
        trav->r->p = trav;
    }
 
    // Return the (unchanged) node pointer
    return trav;
}

// Function performing right rotation
// of the passed node
void rightrotate(Node* temp)
{
    Node* left = temp->l;
    temp->l = left->r;
    if (temp->l)
        temp->l->p = temp;
    left->p = temp->p;
    if (!temp->p)
        root = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;
    left->r = temp;
    temp->p = left;
}
 
// Function performing left rotation
// of the passed node
void leftrotate(Node * temp)
{
    Node* right = temp->r;
    temp->r = right->l;
    if (temp->r)
        temp->r->p = temp;
    right->p = temp->p;
    if (!temp->p)
        root = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;
    right->l = temp;
    temp->p = right;
}

// This function fixes violations
// caused by BST insertion
void fixup(Node * root, Node* pt)
{
    Node * parent_pt = NULL;
    Node * grand_parent_pt = NULL;
 
    while ((pt != root) && (pt->c != 0)
           && (pt->p->c == 1))
    {
        parent_pt = pt->p;
        grand_parent_pt = pt->p->p;
 
        /*  Case : A
             Parent of pt is left child
             of Grand-parent of
           pt */
        if (parent_pt == grand_parent_pt->l)
        {
 
            Node* uncle_pt = grand_parent_pt->r;
 
            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->c == 1)
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
 
            else {
 
                /* Case : 2
                     pt is right child of its parent
                     Left-rotation required */
                if (pt == parent_pt->r) {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }
 
                /* Case : 3
                     pt is left child of its parent
                     Right-rotation required */
                rightrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
 
        /* Case : B
             Parent of pt is right
             child of Grand-parent of
           pt */
        else {
            Node * uncle_pt = grand_parent_pt->l;
 
            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->c == 1))
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->l) {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }
 
                /* Case : 3
                     pt is right child of its parent
                     Left-rotation required */
                leftrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
    }
 
    root->c = 0;
}
 
// Function to print inorder traversal
// of the fixated tree
void inorder(Node * trav)
{
    if (trav == NULL)
        return;
    inorder(trav->l);
    printf("%d ", trav->d);
    inorder(trav->r);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int n = 7;
      int a[7] = { 7, 6, 5, 4, 3, 2, 1 };
   
      for (int i = 0; i < n; i++) {
   
          // allocating memory to the node and initializing:
          // 1. color as red
          // 2. parent, left and right pointers as NULL
          // 3. data as i-th value in the array
          Node * temp
              = (Node *)malloc(sizeof(Node));
          temp->r = NULL;
          temp->l = NULL;
          temp->p = NULL;
          temp->d = a[i];
          temp->c = 1;
   
          // calling function that performs bst insertion of
          // this newly created node
          root = bst(root, temp);
   
          // calling function to preserve properties of rb
          // tree
          fixup(root, temp);
      }
   
      printf("Inorder Traversal of Created Tree\n");
      inorder(root);
    return 0;
}
