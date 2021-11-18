//
//  main.c
//  DoubleCircularlinkedlist
//
//  Created by Fei Yuan on 2021/11/11.
//

#include <stdio.h>
#include <stdlib.h>

//Node of a doubly linked list
struct Node {
    int data;
    struct Node * next;//Pointer to next node in DLL
    struct Node * prev;//Pointer to previous node in DLL
};

//Given a reference (pointer to pointer) to the head of a
//and a int.inserts a new node on the front of the list
void push(struct Node ** head_ref, int new_data) {
    //alloccate node
    struct Node * new_node = (struct Node *)malloc(sizeof(struct Node));
    
    //put in the data
    new_node->data = new_data;
    
    //make next of new node as head and previous as NULL
    new_node->next = (*head_ref);
    new_node->prev = NULL;
    
    //change prev of head node to new node
    if ((*head_ref) != NULL) {
        (*head_ref)->prev = new_node;
    }
    
    //move the head to point to the new node
    (*head_ref) = new_node;
}

//Give a node as prev_node, insert a new node after the given node
void insertAfter(struct Node * prev_node, int new_data) {
    //check if the given prev_node is NULL
    if (prev_node == NULL) {
        return;
    }
    
    //allocate new node
    struct Node * new_node = (struct Node *)malloc(sizeof(struct Node));

    new_node->data = new_data;
    
    //make next of new node as next of prev_node
    new_node->next = prev_node->next;
    
    //make the next of prev_node as new_node
    prev_node->next = new_node;
    
    //Make prev_node as previous of new_node
    new_node->prev = prev_node;
    
    //change previous of new_node's next node
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }
}

//give a reference to the head of a DLL and an int , appends a new node at the end
void append(struct Node ** head_ref, int new_data) {
    //allocate node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    
    struct Node * last = *head_ref;
    
    new_node->data = new_data;
    
    //this new node is going to be the last node, so make next of it as NULL
    new_node->next = NULL;
    
    //if the linked list is empty, then make the new node as head
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }
    
    // traverse till the last node
    while (last->next != NULL) {
        last = last->next;
    }
    
    //change the next of last node
    last->next = new_node;
    
    //make last node as previous of new node
    new_node->prev = last;
    return;
}

// This function prints contents of linked list starting
// from the given node
void printList(struct Node* node)
{
    struct Node* last;
    printf("\nTraversal in forward direction \n");
    while (node != NULL) {
        printf(" %d ", node->data);
        last = node;
        node = node->next;
    }
 
    printf("\nTraversal in reverse direction \n");
    while (last != NULL) {
        printf(" %d ", last->data);
        last = last->prev;
    }
}

//节点的删除一般在三个位置：头结点，中间，尾部。针对这些位置，我们只需要按照两种情况来处理
//1.如果删除的节点是头部，只需要把头结点的下一个节点设置成头结点即可
//2.如果不是头结点，只需要关联它的前节点和后节点即可

void deleteNode(struct Node ** head_ref, struct Node * del) {
    if (*head_ref == NULL || del == NULL) {
        return;
    }
    
    //if node to be deleted is head node
    if (*head_ref == del) {
        *head_ref = del->next;
    }
    
    //change next only if node to be deleted is NOT the last node
    if (del->next != NULL) {
        del->next->prev = del->prev;
    }
    
    //change prev only if node to be deleted is NOT the first node
    if (del->prev != NULL) {
        del->prev->next = del ->next;
    }
    
    //finally , free the memory
    free(del);
    return;
}

//delte the node at the given position in doubly linked list
void deleteNodeGivenPos(struct Node ** head_ref, int n) {
    if (*head_ref == NULL || n <= 0) {
        return;
    }
    
    struct Node * current = *head_ref;
    
    //获取要删除位置的结点
    for (int i = 1; current != NULL && i < n; i++) {
        current = current->next;
    }
    
    //if n is greater than the number of linked
    if (current == NULL) {
        return;
    }
    deleteNode(head_ref, current);
}

//count triplets in a sorted doubly linked list whose sum is
//equal to a given value x
//Time complexity:O(n3)
//auxiliary space:0(1)
//int countTriplets(struct Node * head, int x) {
//    struct Node * ptr1, * ptr2, * ptr3;
//
//    int count = 0;
//    //generate all possible triplets
//    for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->next) {
//        for (ptr2 = ptr1->next; ptr2 != NULL; ptr2=ptr2->next) {
//            for (ptr3 = ptr2->next; ptr3 != NULL; ptr3=ptr3->next) {
//                // if elements in the current triplet sum up to 'x'
//                if ((ptr1->data + ptr2->data + ptr3->data) == x){
//                    // increment count
//                    count++;
//                }
//            }
//        }
//    }
//    return count;
//}

//count triplets in a sorted doubly linked list
// whose sum is equal to a given value 'x'
int countPairs(struct Node* first, struct Node* second, int value) {
    int count  = 0;
    
    // The loop terminates when either of two pointers
        // become NULL, or they cross each other (second->next
        // == first), or they become same (first == second)
    while (first != NULL && second != NULL && first != second && second->next != first) {
        //pair found
        if (first->data + second->data == value) {
            //increment count
            count ++;
            
            //move first in forward direction
            first = first ->next;
            
            //move second in backward direction
            second = second->prev;
        }else if ((first->data + second->data) > value) {
            second = second->prev;
        }else{
            first = first->next;
        }
    }
    return count;
}

int countTriplets(struct Node * head, int x) {
    
    //if list is empty
    if (head == NULL) {
        return 0;
    }
    int count = 0;

    struct Node * current, * first, *last;
    
    //get pointer to the last node
    last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    
    //traversing the doubly linked list
    for (current = head; current != NULL; current = current->next) {
        //
        first = current->next;
        // count pairs with sum(x - current->data) in the range
        // first to last and add it to the 'count' of triplets
        count += countPairs(first, last, x - current->data);
    }
    return count;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    /* Start with the empty list */
      struct Node* head = NULL;
   
      // Insert 6.  So linked list becomes 6->NULL
      append(&head, 6);
   
      // Insert 7 at the beginning. So linked list becomes
      // 7->6->NULL
      push(&head, 7);
   
      // Insert 1 at the beginning. So linked list becomes
      // 1->7->6->NULL
      push(&head, 1);
   
      // Insert 4 at the end. So linked list becomes
      // 1->7->6->4->NULL
      append(&head, 4);
   
      // Insert 8, after 7. So linked list becomes
      // 1->7->8->6->4->NULL
      insertAfter(head->next, 8);
   
      printf("Created DLL is: ");
      printList(head);
    
    return 0;
}
