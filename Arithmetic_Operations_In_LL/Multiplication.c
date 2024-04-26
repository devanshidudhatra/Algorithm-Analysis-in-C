#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

struct Node* add(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    struct Node* tail = NULL;
    int carry = 0;

    while (num1 || num2 || carry) {
        int digit1 = num1 ? num1->data : 0;
        int digit2 = num2 ? num2->data : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        int digit = sum % 10;

        struct Node* newNode = createNode(digit);

        if (!result) {
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        if (num1) num1 = num1->next;
        if (num2) num2 = num2->next;
    }

    return result;
}

struct Node* subtract(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    struct Node* tail = NULL;
    int borrow = 0;

    while (num1 || num2) {
        int digit1 = num1 ? num1->data : 0;
        int digit2 = num2 ? num2->data : 0;

        int diff = digit1 - borrow - digit2;
        borrow = (diff < 0) ? 1 : 0;
        diff = (diff < 0) ? diff + 10 : diff;

        struct Node* newNode = createNode(diff);

        if (!result) {
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        if (num1) num1 = num1->next;
        if (num2) num2 = num2->next;
    }

    return result;
}

struct Node* multiplyDigit(struct Node* num, int digit) {
    struct Node* result = NULL;
    struct Node* tail = NULL;
    int carry = 0;

    while (num || carry) {
        int currentDigit = num ? num->data : 0;
        int product = currentDigit * digit + carry;
        carry = product / 10;
        int newDigit = product % 10;

        struct Node* newNode = createNode(newDigit);

        if (!result) {
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        if (num) num = num->next;
    }

    return result;
}


// Function to shift digits of the list to the left by `shifts` positions
struct Node* shiftList(struct Node* num, int shifts) {
    struct Node* shiftedList = NULL;
    struct Node* tail = NULL;

    // Create nodes with value 0 for the shifted positions
    while (shifts > 0) {
        struct Node* newNode = createNode(0);
        if (!shiftedList) {
            shiftedList = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        shifts--;
    }

    // Append the digits of the original list to the shifted list
    struct Node* current = num;
    while (current != NULL) {
        struct Node* newNode = createNode(current->data);
        if (!shiftedList) {
            shiftedList = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        current = current->next;
    }

    return shiftedList;
}

// Function to multiply two linked lists representing integers
struct Node* multiply(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;

    // Handle multiplication by zero
    if (!num1 || !num2) return NULL;

    // Multiply each digit of num1 with num2, adding partial products
    struct Node* cur1 = num1;
    while (cur1) {
        int digit1 = cur1->data;
        struct Node* partial = multiplyDigit(num2, digit1);
        struct Node* shifted = shiftList(partial, cur1->data - 1);
        result = add(result, shifted);
        cur1 = cur1->next;
    }

    return result;
}
struct Node* power(struct Node* num, int exp) {
    if (exp == 0) return createNode(1);
    struct Node* result = power(num, exp / 2);
    result = multiply(result, result);
    if (exp % 2 == 1) result = multiply(result, num);
    return result;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

int main() {
    // Test addition
    struct Node* num1 = createNode(12345);  // Represented as 5 -> 4 -> 3 -> 2 -> 1
    struct Node* num2 = createNode(6789);   // Represented as 9 -> 8 -> 7 -> 6
    struct Node* sum = add(num1, num2);

    printf("Addition result: ");
    printList(sum);
    // freeList(sum);

    // Test subtraction
    struct Node* diff = subtract(num1, num2);
    printf("Subtraction result: ");
    printList(diff);
    // freeList(diff);

    // Test multiplication
    struct Node* product = multiply(num1, num2);
    printf("Multiplication result: ");
    printList(product);
    // freeList(product);

    // Test exponentiation
    int exponent = 3;
    struct Node* result = power(num1, exponent);
    printf("Exponentiation result (num1^%d): ", exponent);
    printList(result);
    // freeList(result);

    // // Free allocated memory
    // freeList(num1);
    // freeList(num2);

    return 0;
}