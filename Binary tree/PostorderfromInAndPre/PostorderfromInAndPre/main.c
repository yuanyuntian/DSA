//
//  main.c
//  PostorderfromInAndPre
//
//  Created by Fei Yuan on 2022/1/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

//We can print postorder traversal without constructing the tree. The idea is, root is always the first item in preorder traversal and it must be the last item in postorder traversal. We first recursively print left subtree, then recursively print right subtree. Finally, print root. To find boundaries of left and right subtrees in pre[] and in[], we search root in in[], all elements before root in in[] are elements of left subtree, and all elements after root are elements of right subtree. In pre[], all elements after index of root in in[] are elements of right subtree. And elements before index (including the element at index and excluding the first element) are elements of left subtree.

//function  to search x in arr[] of size n
int search(int arr[], int x, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

void printPostOrder(int in[], int pre[], int n) {
    //the first element in pre[] is always root,
    //search it in[] to find left and right subtrees
    int root = search(in, pre[0], n);
    
    //if left subtree is not empty, print left subtree
    if (root != 0) {
        printPostOrder(in, pre + 1, root);
    }
    
    //if right subtree is not empty ,print right subtree
    if (root != n - 1) {
        printPostOrder(in + root + 1, pre + root + 1, n -root -1);
    }
    printf("%d ", pre[0]);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int in[] = { 4, 2, 5, 1, 3, 6 };
    int pre[] = { 1, 2, 4, 5, 3, 6 };
    int n = sizeof(in) / sizeof(in[0]);
    printf("Postorder traversal\n");
    printPostOrder(in, pre, n);
    return 0;
}
