#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a lecture interval
struct Interval
{
    int start;
    int end;
};

struct Interval intervals[100];
int n;

// Structure to represent a classroom
struct Classroom
{
    int end_time; // End time of the last lecture scheduled in the classroom
    int count;    // Number of lectures scheduled in the classroom
};

void Sort()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (intervals[i].start > intervals[j].start)
            {
                struct Interval temp;
                temp = intervals[i];
                intervals[i] = intervals[j];
                intervals[j] = temp;
            }
        }
    }
}

// // Function to compare two intervals based on their start times
// int compareIntervals(const void *a, const void *b) {
//     return ((struct Interval*)a)->start - ((struct Interval*)b)->start;
// }

// Function to schedule lectures using greedy approach
int scheduleLectures(struct Interval *intervals, int n)
{
    // Sort the intervals based on their start times
    // qsort(intervals, n, sizeof(struct Interval), compareIntervals);

    Sort();

    // Create an array of classrooms
    struct Classroom *classrooms = (struct Classroom *)malloc(n * sizeof(struct Classroom));
    for (int i = 0; i < n; i++)
    {
        classrooms[i].end_time = -1; // Initialize end time of each classroom
        classrooms[i].count = 0;     // Initialize count of lectures scheduled in each classroom
    }
    int maximum = 0;
    // Iterate through each interval and assign it to a classroom
    for (int i = 0; i < n; i++)
    {
        int j;
        for (j = 0; j < n; j++)
        {
            if (classrooms[j].end_time <= intervals[i].start)
            {
                // Assign interval i to classroom j
                classrooms[j].end_time = intervals[i].end;
                classrooms[j].count++;
                // if (classrooms[j].count > maximum) {
                //      maximum = classrooms[j].count;
                // }
                break;
            }
        }
        if (j == n)
        {
            // If no available classroom found, create a new one
            classrooms[j].end_time = intervals[i].end;
            classrooms[j].count++;
        }
        if (maximum < j + 1)
            maximum = j + 1;
    }

    // Free dynamically allocated memory
    free(classrooms);

    // return max_classrooms;
    return maximum;
}

// Main function
int main()
{
    struct Interval intervals[] = {{0, 3}, {1, 4}, {2, 5}, {3, 6}, {5, 7}};
    n = sizeof(intervals) / sizeof(intervals[0]);

    printf("Minimum number of classrooms required: %d\n", scheduleLectures(intervals, n));

    return 0;
}
