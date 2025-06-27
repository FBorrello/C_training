/*Requirements:

Use functions to modularize your code (e.g., one for calculating the average, one for determining the grade).
Use a switch or if statements for grade assignment.
Store names in character arrays (e.g., char name[50]).
Commit your code to your Git repo with clear comments and a README*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define studentScores 3

typedef struct student{
    char name[50];
    int grades[studentScores];
    float average;
} Student; 

typedef struct grade{
    char letter;
    int number;
} Grade;

void displayIntArray(int* array, int arraySize)
{
    int i;
    if (arraySize > 0)
    {
        for (i = 0; i < arraySize; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");
    }
}

Student* addStudentsNumber(int* studentsNumber)
{
    do {
        printf("Enter number of students: ");
        scanf("%d", studentsNumber);
        if (*studentsNumber <=0) printf("Error: Number of student must be positive integer.");
    } while (*studentsNumber <=0);
    printf("The number of strudent is %d\n", *studentsNumber);
    Student* students = (Student*)malloc(*studentsNumber * sizeof(Student));
    if (students == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    return students;
}

int validateScore(int scoreNumber, char* name)
{
    int score;
    do {
        printf("Enter test score %d for %s: ", scoreNumber, name);
        scanf("%d", &score);
        if (score <= 0 || score > 100) printf("Error: Scores must be between 0 and 100. Try again.\n");
    } while (score <= 0 || score > 100);
    printf("You stored test score %d for %s: %d\n", scoreNumber, name, score);
    return score;
}

void storeStudentData(int* studentsNumber, Student* students)
{
    int i, j;
    if (*studentsNumber > 0 && students != NULL)
    {
        for (i = 0; i < *studentsNumber; i++)
        {
            printf("\nEnter name for student %d: ", i + 1);
            scanf(" %[^\n]", students[i].name);
            printf("You entered the following student name: %s\n", students[i].name);

            for (j = 0; j < studentScores; j++)
            {
                students[i].grades[j] = validateScore(j + 1, students[i].name);
            }
            printf("Student %s scores: ", students[i].name);
            displayIntArray(students[i].grades, studentScores);
        }
    }
}

int main ()
{
    int studentsNumber = 0;
    Student* students;
    
    /*Accept the number of students (via scanf).*/
    students = addStudentsNumber(&studentsNumber);

    /*For each student, input their name (as a string) and three test scores (integers between 0 and 100).*/
    storeStudentData(&studentsNumber, students);

    /*Calculate the average score for each student and assign a letter grade (A: 90–100, B: 80–89, C: 70–79, D: 60–69, F: <60).*/
    /*Print a formatted report with each student’s name, average score, and letter grade.*/
    /*Handle errors: reject invalid scores (outside 0–100) and ensure the number of students is positive.*/

    return 0;
}