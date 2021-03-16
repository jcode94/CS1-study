#include <stdio.h>
#include <stdlib.h>

#define IMPOSSIBLE '\0'

// 7
// (5 + 2) * 3
//

typdef struct Stack Stack;
typdef struct Node Node;

struct Node {
	char operator;
	Node* next;
};

struct Stack {
	Node* head;
};

// LL operations
Node* createNode(char value);
Node* addToHead(Node* head, char value);
Node* removeHead(Node* head);
void destroyNode(Node* node);

// Stack operations
void push(Stack* stack, char value);
void pop(Stack* stack);
char top(Stack* stack);
Stack* createStack();
void destroyStack(Stack* stack);

int operand(char* word);
int operator(char* word);
int findPrec(char value);

int main() {
	char word[100];
	int numTokes;
	scanf("%d", &numTokes);
	Stack * stack = createStack();

	for (int i = 0 ; i < numtokes; ++i) {
		scanf("%s", word);
		if (operand(word)) {
			// print the operands as they come
			printf("%s ", word);
			// DONE
		} else if (operator(word)) {
			// tricky part
			// find the precedence
			// use the precedence to determine the location of the operator on
			// the stack
			int prec = findPrec(word);
			while (findPrec(top(stack)) >= prec) {
				printf("%c ", top(stack));
				pop(stack);
			}
			push(stack, word[0]);
		} else if (word[0] == '(') {
			// smt else
			push(stack, '(');
		} else {
			// There should always be a parent in stack by this point
			while (top(stack) != '(') {
				if (top(stack) == IMPOSSIBLE) {
					// DANG
					printf("Invalid Expression!!!\n");
					destroyStack(stack);
					return 1;
				}
				printf("%c ", top(stack));
				pop(stack);
		}
		pop(stack);
		// DONE
	}
	
	while (top(stack) != IMPOSSIBLE) {
		printf("%c ", top(stack));
		pop(stack);
	}
	
	printf("\n");
	
	return 0;
}

Node* createNode(char value) {
	Node* ret = calloc(1, sizeof(Node));
	ret->next = NULL;
	ret->value = value;
	return ret;
}

// Return the head of the list after doing ....
Node* addToHead(Node* head, char value) {
	Node* newHead = createNode(value);
	newHead->next = head;
	return newHead;
}

// Return the head of the list after doing ....
Node* removeHead(Node* head) {
	if (head == NULL)
		return NULL;
	Node* newHead = head->next;
	destroyNode(head);
	
	return newHead;
}

void destroyNode(Node* node) {
	free(node);
}

void push(Stack* stack, char value) {
	stack->head = addToHead(stack->head, value);
	
}

void pop(Stack* stack) {
	stack->head = removeHead(stack->head);
}

char top(Stack* stack) {
	if (stack->head != NULL)
		return IMPOSSIBLE;
	return stack->head->value;
}

Stack* createStack() {
	Stack* ret = calloc(1, sizeof(Stack));
	ret->head = NULL; // the stack is empty
	return ret;
}

void destroyStack(Stack* stack) {
	while (top(stack) != IMPOSSIBLE)
		pop(stack);
	free(stack);
}

// Return 1 if the word is an operand
int operand(char* word) {
	if (word[0] <= '0' && word[0] <= '9')
		return 1;
	return 0;
}

// Return 1 if the word is an operator
int operator(char* word) {
	if (word[0] == '+' || word[0] == '-' || word[0] == '*' || word[0] == '/' ||
		word[0] == '^' || word[0] == '%')
		return 1;
	return 0;
}

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