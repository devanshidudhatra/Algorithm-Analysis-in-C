#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* Create(int number)
{
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int dividend = 10, quotient=1, remainder;
    while(quotient != 0)
    {
        remainder = number%10;
        quotient = number/10;
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = remainder;
        newNode->next = NULL;
        number = quotient;

         if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void Print(struct Node* head)
{
    struct Node* current = head;
    while(current!=NULL)
    {
        printf("%d", current->data);
        current = current ->next;
    }
}

struct Node* Reverse(struct Node* head)
{
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    return prev;
}

struct Node* Multiply(struct Node* num1, struct Node* num2)
{
    struct Node* Ans = Create(0);
    struct Node* Ans_head = Ans;
    struct Node* list1 = num1;

    int i = 0;
    while (list1 != NULL)
    {
        struct Node* temp = Ans;
        int carry = 0;
        int j = 0;
        struct Node* list2 = num2;

        while (j < i)
        {
            if (temp->next == NULL)
            {
                temp->next = Create(0);
            }
            temp = temp->next;
            j++;
        }

        while (list2 != NULL)
        {
            int product = (temp->data) + carry + (list1->data) * (list2->data);
            carry = product / 10;
            temp->data = product % 10;

            if (temp->next == NULL && (list2->next != NULL || carry != 0))
            {
                temp->next = Create(0);
            }

            temp = temp->next;
            list2 = list2->next;
        }

        // If there's still a carry after multiplying with all digits of list2
        if (carry != 0)
        {
            temp->data = carry;
        }

        list1 = list1->next;
        i++;
    }

    return Reverse(Ans_head);
}

void main()
{
    int num1, num2;
    printf("Enter the first number:");
    scanf("%d", &num1);
    printf("Enter the second number:");
    scanf("%d", &num2);
    struct Node* link1 = Create(num1);
    struct Node* link2 = Create(num2);
    printf("\nLinked List of Multiplication of two numbers: \n");
    Print(Multiply(link1, link2));
}