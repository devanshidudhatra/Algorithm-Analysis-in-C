#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct Node {
    char name[40];
    int x;
    int y;
    struct Node* next;
};

struct Node *head = NULL;

void Insertion() {
    char Name[40];
    int X, Y;
    struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
    printf("Enter name of city: ");
    scanf("%s", Name);
    printf("Enter X-Coordinate: ");
    scanf("%d", &X);
    printf("Enter Y-Coordinate:");
    scanf("%d", &Y);
    strcpy(ptr->name, Name);
    ptr->x = X;
    ptr->y = Y;
    ptr->next = head;
    head = ptr;
    printf("Node Inserted...\n");
}

void SearchByName() {
    char Name[40];
    struct Node *ptr;
    ptr = head;
    int flag = 0;
    printf("Enter city to be searched : ");
    scanf("%s", Name);
    while (ptr != NULL) {
        if (strcmp(ptr->name, Name) == 0) {
            printf("City found...\n");
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }
    if (flag == 0) {
        printf("City not found...\n");
    }
}

void SearchByCoord() {
    struct Node *ptr;
    ptr = head;
    int X, Y, flag = 0;
    printf("Enter x coordinate to be searched : ");
    scanf("%d", &X);
    printf("Enter y coordinate to be searched : ");
    scanf("%d", &Y);
    while (ptr != NULL) {
        if (ptr->x == X && ptr->y == Y) {
            printf("City found...\n");
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }
    if (flag == 0) {
        printf("City not found...\n");
    }
}

void DeleteByName() {
    char Name[40];
    struct Node *ptr;
    struct Node *preptr = NULL;
    int flag = 0;
    printf("Enter city to be deleted : ");
    scanf("%s", Name);
    ptr = head;
    if (strcmp(ptr->name, Name) == 0) {
        head = ptr->next;
        printf("Node Deleted... \n");
        return;
    }
    while (ptr != NULL) {
        if (strcmp(ptr->name, Name) == 0) {
            preptr->next = ptr->next;
            flag = 1;
            break;
        }
        preptr = ptr;
        ptr = ptr->next;
    }
    if (flag == 0) {
        printf("City not found...\n");
    }
}

void DeleteByCoord() {
    int X, Y;
    struct Node *ptr;
    struct Node *preptr = NULL;
    int flag = 0;
    printf("Enter x coordinate to be deleted : ");
    scanf("%d", &X);
    printf("Enter y coordinate to be deleted : ");
    scanf("%d", &Y);
    ptr = head;
    if (ptr != NULL && ptr->x == X && ptr->y == Y) {
        head = ptr->next;
        printf("Node Deleted... \n");
        return;
    }
    while (ptr != NULL) {
        if (ptr->x == X && ptr->y == Y) {
            preptr->next = ptr->next;
            free(ptr);
            flag = 1;
            break;
        }
        preptr = ptr;
        ptr = ptr->next;
    }
    if (flag == 0) {
        printf("City not found...\n");
    }
}

void PrintWithinDistance() {
    int X,Y,distance;
    printf("Enter x-coordinate : ");
    scanf("%d" , &X);
    printf("Enter y-coordinate : ");
    scanf("%d" , &Y);
    printf("Enter distance : ");
    scanf("%d" , &distance);
    struct Node *current = head;
    while (current != NULL) {
        double dist = sqrt(pow(current->x - X, 2) + pow(current->y - Y, 2));
        if (dist <= distance) {
            printf("Name: %s(%d, %d), Distance: %.2f\n", current->name, current->x, current->y, dist);
        }
        current = current->next;
    }
}

void Print() {
    struct Node *ptr;
    ptr = head;
    if (ptr == NULL) {
        printf("List is Empty...\n");
    } else {
        while (ptr != NULL) {
            printf("%s (%d , %d) -> ", ptr->name, ptr->x, ptr->y);
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n1 for Insertion\n2 for Delete by Name\n3 to Delete by Coordinates\n4 to Search by Name\n5 to Search by Coordinates\n6 to Print Records in range\n7 to Print\n8 to Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
        case 1: Insertion(); break;
        case 2: DeleteByName(); break;
        case 3: DeleteByCoord(); break;
        case 4: SearchByName();  break;
        case 5: SearchByCoord();  break;
        case 6: PrintWithinDistance(); break;
        case 7: Print(); break;
        case 8: printf("Exiting..."); exit(0);
        default: printf("Enter proper choice...\n"); break;
        }
    } while (choice != 8);
    return 0;
}
