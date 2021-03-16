#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 20

typedef struct Node Node;

struct Node {
	char name[NAME_LEN + 1];
	int tokens;
};

int main() {
	Node** NodeList;
	int numberOfNodes;
	
	scanf("%d", &numberOfNodes);
	
	NodeList = malloc(numberOfNodes * sizeof(Node*));
	
	// NodeList {ptr1, ptr2, ptr3}
	
	for (int i = 0; i < numberOfNodes; ++i)
	{
		NodeList[i] = malloc(sizeof(Node));
		scanf("%s%d", NodeList[i]->name, &NodeList[i]->tokens);
	}
	
	scanf("%d%d", 
	
	for (int i = 0; i < numberOfNodes; ++i)
	{
		printf("Name: %s, NumTokens: %d", NodeList[i]->name, NodeList[i]->tokens);
	}
	return 0;
}

