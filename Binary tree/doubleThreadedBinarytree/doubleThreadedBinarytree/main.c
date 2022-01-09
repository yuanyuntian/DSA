//
//  main.c
//  doubleThreadedBinarytree
//
//  Created by Fei Yuan on 2022/1/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Node {
    struct Node * left, * right;
    int info;
    
    //true if left pointer points to predecessor
    //in Inorder Traversal
    bool lthread;
    
    //true if right pointer points to successor in Inorder Traversal
    bool rthread;
};


// Here 'par' is pointer to parent Node and 'ptr' is
// pointer to current Node.
struct Node* caseA(struct Node* root, struct Node* par,
                   struct Node* ptr);


// Here 'par' is pointer to parent Node and 'ptr' is
// pointer to current Node.
struct Node* caseB(struct Node* root, struct Node* par,
                   struct Node* ptr);

// Here 'par' is pointer to parent Node and 'ptr' is
// pointer to current Node.
struct Node* caseC(struct Node* root, struct Node* par,
                   struct Node* ptr);

struct Node * inSucc(struct Node * ptr);

struct Node * inPred(struct Node * ptr);

//Insert a Node in Binary Threaded Tree
struct Node * insert(struct Node * root, int ikey) {
    //search for a node with given value
    struct Node * ptr = root;
    struct Node * par = NULL;//Parent of key to be inserted
    while (ptr != NULL) {
        //if key already exitsts, return
        if (ikey == (ptr->info)) {
            printf("Duplicate key !\n");
            return root;
        }
        
        par = ptr;//Update parent pointer
        
        //moving on left subtree
        if (ikey < ptr->info) {
            if (ptr ->lthread ==  false) {
                ptr = ptr->left;
            }else{
                break;
            }
        }else{
            //move on right subtree
            if (ptr ->rthread ==  false) {
                ptr = ptr->right;
            }else{
                break;
            }
        }
    }
    
    //create a new node
    struct Node * tmp = (struct Node *)malloc(sizeof(struct Node *));
    tmp->info = ikey;
    tmp->lthread = true;
    tmp->rthread = true;
    
    if (par == NULL) {
        root = tmp;
        tmp->left = NULL;
        tmp->right = NULL;
    }else if (ikey < (par->info)) {
        tmp->left = par->left;
        tmp->right = par;
        par->lthread = false;
        par->left = tmp;
    }else{
        tmp->left = par;
        tmp->right = par->right;
        par->rthread = false;
        par->right = tmp;
    }
    return root;
}

//Delete a key from threaded BST with given root and
//returns new root of BST
struct Node * delThreadedBST(struct Node * root, int dkey) {
    //initialize parent as NULL and ptrent
    //Node as root
    struct Node * par = NULL, * ptr = root;
    
    //set true if key is found
    int found = 0;
    
    //search key in BST:find node and its parent
    while (ptr != NULL) {
        if (dkey == ptr->info) {
            found = 1;
            break;
        }
        par = ptr;
        if (dkey < ptr->info) {
            if (ptr->lthread ==  false) {
                ptr = ptr->left;
            }else{
                break;
            }
        }else{
            if (ptr->rthread ==  false) {
                ptr = ptr->right;
            }else{
                break;
            }
        }
    }
    if (found == 0) {
        printf("dkey not present in tree\n");
    }else{
        //two children
        if (ptr->lthread ==  false && ptr->rthread == false) {
            root =  caseC(root, par, ptr);
        }else if (ptr->lthread == false) {
            //only left child
            root =  caseB(root, par, ptr);
        }else if (ptr->rthread ==  false) {
            root =  caseB(root, par, ptr);
        }else{
            // no child
            root = caseA(root, par, ptr);
        }
    }
    return root;
}

//Case A: Leaf Node need to be deleted
//In BST, for deleting a leaf Node the left or right pointer of parent was set to NULL. Here instead of setting the pointer to NULL it is made a thread.
//If the leaf Node is to be deleted is left child of its parent then after deletion, left pointer of parent should become a thread pointing to its predecessor of the parent Node after deletion.
//If the leaf Node to be deleted is right child of its parent then after deletion, right pointer of parent should become a thread pointing to its successor. The Node which was inorder successor of the leaf Node before deletion will become the inorder successor of the parent Node after deletion.

struct Node* caseA(struct Node* root, struct Node* par, struct Node* ptr) {
    //if node to be deleted is root
    if (par == NULL) {
        root = NULL;
    }else if(ptr == par->left) {
        //if node to be deleted is left of its parent
        par->lthread = true;
        par->left = ptr->left;
    }else{
        par->rthread = true;
        par->right = ptr->right;
    }
    //free memory and return new root
    free(ptr);
    return root;
}

//Case B: Node to be deleted has only one child
//1.After deleting the Node as in a BST, the inorder successor and inorder predecessor of the Node are found out.
//s = inSucc(ptr);
//p = inPred(ptr);

//2.If Node to be deleted has left subtree, then after deletion right thread of its predecessor should point to its successor.
//p->right = s;

//3.If Node to be deleted has right subtree, then after deletion left thread of its successor should point to its prredecessor.
//s->left = p;

struct Node* caseB(struct Node* root, struct Node* par,
                   struct Node* ptr) {
    struct Node * child;
    
    //Initialize child Node to be deleted has left child
    if (ptr->lthread == false) {
        child = ptr->left;
    }else{
        //Node to be deleted has right child
        child = ptr->right;
    }
    
    //Node to be deleted is root Node
    if (par == NULL) {
        root = child;
    }else if (ptr == par->left) {
        //Node is left child of its parent
        par->left = child;
    }else{
        par->right = child;
    }
    
    //Find successor and predecessor
    struct Node * s = inSucc(ptr);
    struct Node* p = inPred(ptr);
    // If ptr has left subtree.
    if (ptr->lthread == false)
        p->right = s;
 
    // If ptr has right subtree.
    else {
        if (ptr->rthread == false)
            s->left = p;
    }
 
    free(ptr);
    return root;
}

//We find inorder successor of Node ptr (Node to be deleted) and then copy the information of this successor into Node ptr. After this inorder successor Node is deleted using either Case A or Case B.
struct Node* caseC(struct Node* root, struct Node* par,
                   struct Node* ptr) {
    //Find inorder successor and its parent
    struct Node * parsucc = ptr;
    struct Node * succ = ptr->right;
    
    //find leftmost child of successor
    while (succ->left != NULL) {
        parsucc = succ;
        succ = succ->left;
    }
    
    ptr->info = succ->info;
     
    if (succ->lthread == true && succ->rthread == true)
        root = caseA(root, parsucc, succ);
    else
        root = caseB(root, parsucc, succ);
 
    return root;
}

//Return inorder successor using left and right children (used in deletion)
struct Node * inSucc(struct Node * ptr) {
    if (ptr->rthread == true) {
        return ptr->right;
    }else{
        ptr = ptr->right;
        while (ptr->lthread == false) {
            ptr = ptr->left;
        }
    }
    return  ptr;
}

//return inorder successor using rthread
struct Node * inorderSuccessor(struct Node * ptr){
    //if rthread is set, we can quickly find
    if (ptr->rthread == true) {
        return ptr->right;
    }
    
    //else return leftmost child of right subtree
    ptr = ptr->right;
    while (ptr->lthread == false) {
        ptr = ptr->left;
    }
    return ptr;
}

struct Node * inPred(struct Node * ptr) {
    if (ptr->lthread == true) {
        return ptr->left;
    }else{
        ptr = ptr->left;
        while (ptr->rthread == false) {
            ptr = ptr->right;
        }
    }
    return ptr;
}

//printing the threaded tree
void inorder(struct Node * root) {
    if (root == NULL) {
        printf("tree is empty");
    }
    
    //reach leftmost node
    struct Node * ptr = root;
    while (ptr->lthread == false) {
        ptr = ptr->left;
    }
    
    //one by one print successors
    while (ptr != NULL) {
        printf("%d ", ptr->info);
        ptr = inorderSuccessor(ptr);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    struct Node* root = NULL;
     
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 16);
    root = insert(root, 14);
    root = insert(root, 17);
    root = insert(root, 13);
 
    root = delThreadedBST(root, 20);
    inorder(root);
    return 0;
}
