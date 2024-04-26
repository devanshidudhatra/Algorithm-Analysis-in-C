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
    int quotient, remainder;
    
    while (number != 0)
    {
        remainder = number % 10;
        quotient = number / 10;
        
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = remainder;
        newNode->next = NULL;
        
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
        number = quotient;
    }
    return head;
}

void Print(struct Node* head)
{
    struct Node* current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
}

void PrintReverse(struct Node* head)
{
    if (head == NULL)
        return;
    PrintReverse(head->next);
    printf("%d", head->data);
}

// struct Node* Add(struct Node* head1, struct Node* head2)
// {
//     struct Node* n1 = head1;
//     struct Node* n2 = head2;
//     struct Node* sumHead = NULL;
//     struct Node* sumTail = NULL;
//     int carry = 0;
    
//     while (n1 != NULL || n2 != NULL || carry != 0)
//     {
//         int val1 = (n1 != NULL) ? n1->data : 0;
//         int val2 = (n2 != NULL) ? n2->data : 0;
        
//         int total = val1 + val2 + carry;
//         carry = total / 10;
//         int digit = total % 10;

//         struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//         newNode->data = digit;
//         newNode->next = NULL;
        
//         if (sumHead == NULL) // This is when the sum ll is totally empty
//         {
//             sumHead = newNode;
//             sumTail = newNode;
//         }
//         else   // If any element is present the sum ll
//         {
//             sumTail->next = newNode;
//             sumTail = newNode;
//         }

//         if (n1 != NULL) 
//             n1 = n1->next;
//         if (n2 != NULL) 
//             n2 = n2->next;
//     }
    
//     printf("Sum: ");
//     PrintReverse(sumHead);
//     printf("\n");
// }

void Subtract(struct Node* head1, struct Node* head2)
{
    struct Node* n1 = head1;
    struct Node* n2 = head2;
    struct Node* resultHead = NULL;
    struct Node* resultTail = NULL;
    int borrow = 0;

    while (n1 != NULL || n2 != NULL)
    {
        int val1 = (n1 != NULL) ? n1->data : 0;
        int val2 = (n2 != NULL) ? n2->data : 0;

        val1 -= borrow; // Subtract the borrow from the first number
        borrow = 0;     // Reset borrow

        if (val1 < val2)
        {
            val1 += 10;  // Borrow from the next higher digit
            borrow = 1;  // Set borrow flag
        }

        int digit = val1 - val2;

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = digit;
        newNode->next = NULL;

        if (resultHead == NULL)
        {
            resultHead = newNode;
            resultTail = newNode;
        }
        else
        {
            resultTail->next = newNode;
            resultTail = newNode;
        }

        if (n1 != NULL) n1 = n1->next;
        if (n2 != NULL) n2 = n2->next;
    }

    printf("Difference: ");
    PrintReverse(resultHead);
    printf("\n");
}

int main()
{
    int num1, num2;
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);
    struct Node* head1 = Create(num1);
    struct Node* head2 = Create(num2);
    if(num1 > num2){
        Subtract(head1 , head2);
    }
    else{
        printf("Enter correct numbers... NUmber 2 should be greater than number 1...");
    }
    printf("\n");
    // Add(head1, head2);
    return 0;
}
