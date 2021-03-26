
// This program reads in the number of tokens for an in-fixed expression
// and the expression where each token is space separated and prints
// the resulting post-fix expression

#include <stdio.h>
#include <stdlib.h>

#define IMPOSSIBLE '\0'

typedef struct Stack Stack;
typedef struct Node Node;

struct Stack {
    Node * head;
};
struct Node { 
    char data;
    Node * next;
};

// LL operations
Node * createNode(char value);
Node * addToHead(Node * head, char value);
Node * removeHead(Node * head);
void   destroyNode(Node * node);

// Stack operations
void    push(Stack * stack, char value);
void    pop(Stack * stack);
char    top(Stack * stack);
Stack * createStack();
void    destroyStack(Stack * stack);

int operand(char * word);
int operator(char * word);
int findPrec(char value);

// 7
// ( 5 + 2 ) * 3
//              
int main() {
    char word[100];
    int numTokes;
    scanf("%d", &numTokes);
    Stack * stack = createStack();

    // Loop through all the tokens in the expression
    for (int i = 0; i < numTokes; i++) {
        // Read in the token from the user
        scanf("%s", word);

        // Figure out what we need to do...
        if (operand(word)) {
            // Print the operands as they come
            printf("%s ", word);
            // DONE
            
        } else if (operator(word)) {
            // tricky part
            // find the precedence
            // use the precedence to determine the location of the operator on
            // the stack
            int prec = findPrec(word[0]);

            // Remove operators from the stack until we can place our 
            // current operator on top
            while (findPrec(top(stack)) >= prec) {
                printf("%c ", top(stack));
                pop(stack);
            }

            // Put our current operator on top
            push(stack, word[0]);
            // DONE

        } else if (word[0] == '(') {
            // Since a paren was found we will push it on to the stack to 
            // lock the operators that are currently present
            push(stack, '(');
            // DONE
            
        } else {
            // There should alwasy be a paren in stack by this point
            // Remove operators until a paren is found
            while (top(stack) != '(') {
                // Check for an empty stack
                if (top(stack) == IMPOSSIBLE) {
                    // DANG
                    printf("Invalid Expression!!!\n");
                    destroyStack(stack);
                    return 1;
                }

                // Print and remove the non paren operator
                printf("%c ", top(stack));
                pop(stack);
            }

            // Remove the paren from the top of the stack
            pop(stack);
            // DONE
        }
    }

    // While the stack still has operators inside print them out and remove them
    while (top(stack) != IMPOSSIBLE) {
        printf("%c ", top(stack));
        pop(stack);
    }

    // Add a new line for formatting
    printf("\n");

    // Clean up our memory created
    destroyStack(stack);
    return 0;
}

// LL operations
Node * createNode(char value) {
    Node * ret = calloc(1, sizeof(Node));
    ret->next = NULL;
    ret->data = value;
    return ret;
}

// Return the head of the list after doing ....
Node * addToHead(Node * head, char value) {
    Node * newHead = createNode(value);
    newHead->next = head;
    return newHead;
}

// Return the head of the list after doing ....
Node * removeHead(Node * head) {
    if (head == NULL)
        return NULL;
    Node * newHead = head->next;
    destroyNode(head);

    return newHead;
}

// Method to destroy a node
void destroyNode(Node * node) {
    free(node);
}


// Stack operations
// Stack has a head in the struct
// Add a value to the top of the stack
void push(Stack * stack, char value) {
    Node * oldHead = stack->head;
    Node * newHead = addToHead(oldHead, value);
    stack->head = newHead;
}

// Remove the top of the stack
void pop(Stack * stack) {
    Node * oldHead = stack->head;
    Node * newHead = removeHead(oldHead);
    stack->head = newHead;
}

// Determine the value on the top of the stack
char top(Stack * stack) {
    Node * head = (*stack).head;
    if (head == NULL)
        return IMPOSSIBLE;
    return head->data; // seg fault
}

// Function to create a section of memory for the stack
Stack * createStack() {
    Stack * ret = calloc(1, sizeof(Stack));
    ret->head = NULL;
    return ret;
}

// Function to destroy all the memory left over from the stack
void destroyStack(Stack * stack) {
    // empty the stack first
    while (top(stack) != IMPOSSIBLE)
        pop(stack);
    // Remove the stack memory
    free(stack);
}




// Return 1 if the word is an operand
int operand(char * word) {
    if (word[0] >= '0' && word[0] <= '9')
        return 1;
    return 0;
}

// Return 1 if the word is an operator
int operator(char * word) {
    if (word[0] == '+' || word[0] == '-' || word[0] == '*' || word[0] == '/' ||
            word[0] == '^' || word[0] == '%')
        return 1;
    return 0;
}

// Function to find an integer representing the precedence of an operator
// Higher integers means higher precedence
int findPrec(char value) {
    if (value == '^')
        return 7;
    if (value == '%' || value == '*' || value == '/')
        return 6;
    if (value == '+' || value == '-')
        return 5;
    if (value == '(')
        return 1;
    if (value == IMPOSSIBLE)
        return 0;
    printf("Unkwown operator %c\n", value);
    return -1;
}



