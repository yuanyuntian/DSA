//
//  main.c
//  stackOfArray
//
//  Created by Fei Yuan on 2021/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//A structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    int * array;
};

//create a stack of given capacity,it initializes size of stack as 0
struct Stack * createStack(unsigned capacity) {
    struct Stack * stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(sizeof(struct Stack));
    return  stack;
}

//stack is full when top is equal to the last index
int isFull(struct Stack * stack) {
    return stack->top == stack->capacity - 1;
}

//stack is empty when top is equal to -1
int isEmpty(struct Stack * stack) {
    return stack->top == -1;
}

//add an item to stack .it increase top by 1
void push(struct Stack * stack, int item){
    if (isFull(stack)) {
        return;
    }
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

//remove an item from stack. it drcreases top by 1
int pop(struct Stack * stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }
    return stack->array[stack->top--];
}

//return the top from stack without removeing it
int peek(struct Stack * stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }
    return stack->array[stack->top];
}

//Pros:Easy to implement.Memory is saved as pointers are not involved.
//Cons:It is not dynamic.It don't grow and shrink depending on needs at runtime

int main(int argc, const char * argv[]) {
    // insert code here...
    struct Stack * stack = createStack(100);
    
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    
    return 0;
}
