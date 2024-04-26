#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Event
{
    char eventName[40];
    int start;
    int finish;
    struct Event *next;
};

struct Event events[100];
int eventCount = 0;

void Insert()
{
    printf("Enter name of event : ");
    scanf("%s", events[eventCount].eventName);
    printf("Enter start time : ");
    scanf("%d", &events[eventCount].start);
    printf("Enter finish time : ");
    scanf("%d", &events[eventCount].finish);
    eventCount++;
    printf("Event Inserted...\n");
}

void Sort()
{
    for (int i = 0; i < eventCount; i++)
    {
        for (int j = i + 1; j < eventCount; j++)
        {
            if (events[i].finish > events[j].finish)
            {
                struct Event temp;
                temp = events[i];
                events[i] = events[j];
                events[j] = temp;
            }
        }
    }
}

void Print()
{
    for (int i = 0; i < eventCount; i++)
    {
        printf("\n%s(%d,%d)", events[i].eventName, events[i].start, events[i].finish);
    }
}

void Selection(int n)
{
    int lastSelectedFinishTime = -1;
    for (int i = 0; i < n; i++)
    {
        if (events[i].start >= lastSelectedFinishTime)
        {
            printf("\n%s(%d,%d)", events[i].eventName, events[i].start, events[i].finish);
            lastSelectedFinishTime = events[i].finish;
        }
    }
}

int main()
{
    int n;
    printf("Enter the number u want to enter : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        Insert();
    }
    printf("\nList before sorting : ");
    Print();
    Sort();
    printf("\nList after sorting :");
    Print();
    printf("\n Events to be selected : ");
    Selection(n);
    return 0;
}