#include <stdlib.h>

typedef struct Employee {
    char* name;
    char* likes;
    char* dislikes;
}Employee;

Employee* createEmployee(char* name) {
    Employee* newEmp = malloc(sizeof(Employee));
    newEmp->name = name;
    newEmp->likes = NULL;
    newEmp->dislikes = NULL;

    return newEmp;
}

int main() {
    Employee* Greg = createEmployee("Greg");
    Employee* Steve = createEmployee("Steve");
    Employee* Matt = createEmployee("Matt");

    Steve->likes = Matt;
    Matt->likes = Greg;

}

// Steve->likes->likes->dislikes = Steve;