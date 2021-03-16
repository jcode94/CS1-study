/*
 * Justice Smith - COP3502C - CS1
 * Assignment 4 - Coin Organization
 * Merge Sort template sourced from https://www.geeksforgeeks.org/merge-sort/
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_NAME 20

typedef struct Customer {
    char *name;
    long long int tokens, bills, adjustedValue;
}Customer;

// Create and return a single customer object
Customer *createCustomer() {
    Customer *ret;
    char *buffer;

    // Creating the customer struct
    ret = malloc(sizeof(Customer));

    // Taking in the name of length LEN_NAME and one spot for '\0'
    buffer = malloc((LEN_NAME + 1) * sizeof(char));
    
    // Taking in the customer currency
    scanf("%s%lli%lli", buffer, &ret->tokens, &ret->bills);
    ret->adjustedValue = 0;

    // Copying trimmed name to struct
    ret->name = strdup(buffer);

    return ret;
}

void merge(Customer **customers, int left, int mid, int right) {
    int i, j, k;
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // Temp arrays
    Customer** leftArr = malloc(leftSize * sizeof(Customer*));
    Customer** rightArr = malloc(rightSize * sizeof(Customer*));

    // Copy struct pointers over for sorting
    for (i = 0; i < leftSize; ++i)
        leftArr[i] = customers[left + i];
    for (j = 0; j < rightSize; ++j)
        rightArr[j] = customers[mid + 1 + j];

    // Merging the temp arrays back into customers[left...right]
    i = 0;
    j = 0;
    k = left;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i]->adjustedValue >= rightArr[j]->adjustedValue) {
            customers[k] = leftArr[i];
            i++;
        }
        else {
            customers[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Cleanup copying of remaining leftArr elements after comparisons, if any
    while (i < leftSize) {
        customers[k] = leftArr[i];
        i++;
        k++;
    }

    // Cleanup copying of remaining rightArr elements after comparisons, if any
    while (j < rightSize) {
        customers[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(Customer **customers, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(customers, left, mid);
        mergeSort(customers, mid + 1, right);

        merge(customers, left, mid, right);
    }
}

// Print single customer record helper function
void printCustomer(Customer *customer) {
    printf("--------------------------------\n");
    printf("Customer: %s\n", customer->name);
    printf("Tokens: %d, Bills: %d\n", customer->tokens, customer->bills);
    printf("Adjusted value: %d units\n", customer->adjustedValue);
}

int main() {
    long long int numCustomers, tokenMultiplier, billsMultiplier;
    Customer **customerList;

    // Get number of customers and create struct array
    scanf("%lli", &numCustomers);
    customerList = malloc(numCustomers * sizeof(Customer*));

    // Fill customer array
    for (int i = 0; i < numCustomers; ++i)
        customerList[i] = createCustomer();

    // Scan multipliers
    scanf("%lli%lli", &billsMultiplier, &tokenMultiplier);

    for (int i = 0; i < numCustomers; ++i)
        customerList[i]->adjustedValue = (customerList[i]->tokens * tokenMultiplier) + (customerList[i]->bills * billsMultiplier);

    // Sort the customers in descending order
    mergeSort(customerList, 0, numCustomers - 1);

    /*
    // Print all customers
    for (int i = 0; i < numCustomers; ++i)
        printf("%s\n", customerList[i]->name);
    */
    return 0;
}