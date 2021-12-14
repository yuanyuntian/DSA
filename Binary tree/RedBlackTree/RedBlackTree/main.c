//
//  main.c
//  RedBlackTree
//
//  Created by Fei Yuan on 2021/12/14.
//

#include <stdio.h>

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
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
