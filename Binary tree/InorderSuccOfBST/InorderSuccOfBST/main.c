//
//  main.c
//  InorderSuccOfBST
//
//  Created by Fei Yuan on 2022/1/14.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//In Binary Search Tree, Inorder Successor of an input node can also be defined as the node with the smallest key greater than the key of the input node. So, it is sometimes important to find next node in sorted order


struct node {
    int data;
    struct node *left;
    struct node * right;
    struct node * parent;
};

struct node* newNode(int data)
{
    struct node* node = (struct node*)
        malloc(sizeof(
            struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
 
    return (node);
}

//inserts a new node with the given number in the correct place
// in the tree.Return the new root pointer which the caller should
//then use(the standard tirck to aovid using reference parameters)
struct node * insert(struct node * node, int data) {
    //1.If the tree is empty, return a new, single node
    if (node == NULL) {
        return  newNode(data);
    }else{
        struct node * tmp;
        
        //2.Otherwise, recur down the tree
        if (data <= node->data) {
            tmp = insert(node->left, data);
            node->left = tmp;
            tmp->parent = node;
        }else{
            tmp = insert(node->right, data);
            node->right = tmp;
            tmp->parent = node;
        }
        //return the (unchanged) node pointer
        return node;
    }
}

struct node * minValue(struct node * node) {
    struct node*current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
//1.If right subtree of node is not NULL, then succ lies in right subtree
//Go to right subtree and return the node with minimum key value in the right subtree

//2.If right subtree of node is NULL, then succ is one of the ancestors
//Travel up using the parent pointer until you see a node which is left child of its parent
struct node * inOrderSuccessor(struct node * root, struct node *n) {
    //1.
    if (n->right != NULL) {
        return minValue(n->right);
    }
    
    struct node * p = n->parent;
//方案1
//    while (p != NULL && n != p->left) {
//        n = p;
//        p = p->parent;
//    }

//方案2，直接遍历找比n大于的节点即可
//    while (p != NULL && p->data <= n->data) {
//        p = p->parent;
//    }
//    return p;

    //方案3：直接从根节点找，再从left，right遍历
    struct node * succ = NULL;
    while (root != NULL) {
        if (n->data < root->data) {
            //succ存在left上
            succ = root;
            root = root->left;
        }else if (n ->data > root->data) {
            //succ可能存在right上
            root = root->right;
        }else{
            break;
        }
    }
    return succ;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    struct node *root = NULL, *temp, *succ, *min;
     
    // creating the tree given in the above diagram
    root = insert(root, 20);
    root = insert(root, 8);
    root = insert(root, 22);
    root = insert(root, 4);
    root = insert(root, 12);
    root = insert(root, 10);
    root = insert(root, 14);
    temp = root->left->right->right;
 
    succ = inOrderSuccessor(root, temp);
    if (succ != NULL)
        printf(
            "\n Inorder Successor of %d is %d ",
            temp->data, succ->data);
    else
        printf("\n Inorder Successor doesn't exit");
    
    
    return 0;
}
