#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#define MAX_CITIES 100

struct City {
    char name[40];
    int x;
    int y;
};

struct City cities[MAX_CITIES];
int cityCount = 0;

void Insert() {
    if (cityCount < MAX_CITIES) {
        printf("Enter name of city: ");
        scanf("%s", cities[cityCount].name);
        printf("Enter X-Coordinate: ");
        scanf("%d", &cities[cityCount].x);
        printf("Enter Y-Coordinate:");
        scanf("%d", &cities[cityCount].y);
        cityCount++;
        printf("Record Inserted...\n");
    } else {
        printf("Database full. Cannot insert more records.\n");
    }
}

void DeleteByName() {
    char name[40];
    printf("Enter city name to be deleted: ");
    scanf("%s", name);
    int i, found = 0;
    for (i = 0; i < cityCount; i++) {
        if (strcmp(cities[i].name, name) == 0) {
            found = 1;
            break;
        }
    }
    if (found) {
        for (; i < cityCount - 1; i++) {
            cities[i] = cities[i + 1];
        }
        cityCount--;
        printf("Record deleted successfully.\n");
    } else {
        printf("City not found.\n");
    }
}

void DeleteByCoord() {
    int x, y;
    printf("Enter X-Coordinate to be deleted: ");
    scanf("%d", &x);
    printf("Enter Y-Coordinate to be deleted: ");
    scanf("%d", &y);
    int i, found = 0;
    for (i = 0; i < cityCount; i++) {
        if (cities[i].x == x && cities[i].y == y) {
            found = 1;
            break;
        }
    }
    if (found) {
        for (; i < cityCount - 1; i++) {
            cities[i] = cities[i + 1];
        }
        cityCount--;
        printf("Node deleted...\n");
    } else {
        printf("Coordinates not found...\n");
    }
}

void SearchByName() {
    char name[40];
    printf("Enter city name to be searched: ");
    scanf("%s", name);
    int i, found = 0;
    for (i = 0; i < cityCount; i++) {
        if (strcmp(cities[i].name, name) == 0) {
            found = 1;
            printf("City found at index %d...\n", i);
            break;
        }
    }
    if (!found) {
        printf("City not found...\n");
    }
}

void SearchByCoord() {
    int x, y;
    printf("Enter X-Coordinate to be searched: ");
    scanf("%d", &x);
    printf("Enter Y-Coordinate to be searched: ");
    scanf("%d", &y);
    int i, found = 0;
    for (i = 0; i < cityCount; i++) {
        if (cities[i].x == x && cities[i].y == y) {
            found = 1;
            printf("Coordinates found at index %d...", i);
            break;
        }
    }
    if (!found) {
        printf("Coordinates not found...\n");
    }
}

void PrintWithinDistance() {
    int i,X,Y,distance;
    printf("Enter x-coordinate : ");
    scanf("%d" , &X);
    printf("Enter y-coordinate : ");
    scanf("%d" , &Y);
    printf("Enter distance : ");
    scanf("%d" , &distance);
    for (i = 0; i < cityCount; i++) {
        double dist = sqrt(pow(cities[i].x - X, 2) + pow(cities[i].y - Y, 2));
        if (dist <= distance) {
            printf("Name: %s(%d, %d), Distance: %.2f\n", cities[i].name, cities[i].x, cities[i].y, dist);
        }
    }
}

void Print() {
    if (cityCount == 0) {
        printf("No records found.\n");
        return;
    }
    printf("Printing all records...\n");
    for (int i = 0; i < cityCount; i++) {
        printf("%s(%d, %d)\n", cities[i].name, cities[i].x, cities[i].y);
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Insert a record\n2. Delete a record by name\n3. Delete a record by coordinates\n4. Search a record by name\n5. Search a record by coordinates\n6. Print within range\n7. Print\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: Insert(); break;
            case 2: DeleteByName(); break;
            case 3: DeleteByCoord(); break;
            case 4: SearchByName(); break;
            case 5: SearchByCoord(); break;
            case 6: PrintWithinDistance(); break;
            case 7: Print(); break;
            case 8: printf("Exiting...\n");break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);
    return 0;
}