//-------------------------------//
        //Broken code//
//-------------------------------//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 20
#define WORD_SIZE 200
typedef struct node node;
struct node {
    char * word;
    struct node ** next;                                                        // This should be a single pointer, holding the address to the next Node. Also, by typedeffing, you can just
};                                                                              // node* next;

void destroyArr(node ** wordArr, int size);
void printArr(node ** wordArr, int size);
void printList(node ** head);

int main(int argc, char ** argv){
    node ** wordArr = (node**)calloc(MAX_WORDS, sizeof(node*));                 // you shouldn't have an array of your nodes. That goes directly opposite to the structure of a linked list
    printf("You entered %d arguments\n", argc);                                 // For a single-linked list, operations are done by recursive traversal. If all your nodes are in an array,
    printf("Your strings entered were: ");                                      // and remember that array elements are natively sequential, there is no need for a Node* next pointer

    for(int i = 0; i < argc - 1; i++){
        wordArr[i] = (node*)calloc(1, sizeof(node));
        wordArr[i]->word = (char*)calloc(WORD_SIZE, sizeof(char));              
    }
    for(int i = 0; i < argc - 1; i++){
        strcpy(wordArr[i]->word, argv[i + 1]);
    }
    //Print unchanged list
    printArr(wordArr, argc);

    //Linked list stuff!                                                        // The idea behind linked lists is that all your operations are recursive, so you don't need iterative
    node ** head;                                                               // interaction with your elements. Traversal takes O(n) time where n is the number of elements in the list
    head = &wordArr[0];                                                         // Additionally, you can on-call create and add nodes simply by holding a single pointer to the root element.
    wordArr[0]->next = &wordArr[1];                                             // This is possible because the nodes themselves are located at the next available memory block instead of 
    wordArr[1]->next = NULL;                                                    // the next sequential block of pre-reserved memory in an array or something
    
    printList(head);

    destroyArr(wordArr, argc);
    return 0;
}

void printList(node ** head){
    node ** temp = head;
    int i = 0;
    while(temp != NULL){
        printf("%s ", temp[i]->word);
        temp = temp[i]->next;
        i++;
    }
    printf("\n");
}

void printArr(node ** wordArr, int size){
    for(int i = 0; i < size - 1; i++){
        printf("%s ", wordArr[i]->word);
    }
    printf("\n");
}

void destroyArr(node ** wordArr, int size){                                     // In a similarly recursive fashion, you can imagine your recursive destroy function working like igniting
    for(int i = 0; i < size - 1; i++){                                          // the last TNT in a row of spaced tnt in Minecraft. the last one is destroyed, which moves the operation 
        free(wordArr[i]->word); //free each word                                // to the n - 1 TNT/Node, which is destroyed, and moves you to the n - 2 TNT/Node until you get to and 
        free(wordArr[i]); //free each struct                                    // destroy the root 
    }
    free(wordArr); //free the double pointer
}
