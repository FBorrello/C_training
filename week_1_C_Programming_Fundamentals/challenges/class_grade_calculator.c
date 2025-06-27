/*
 * Class Grade Calculator
 *
 * This program calculates the average score and assigns a letter grade
 * for each student based on three test scores. It handles multiple students,
 * validates input, and produces a formatted grade report.
 *
 * Compilation:
 *   gcc -o grade_calculator class_grade_calculator.c
 *
 * Usage:
 *   ./grade_calculator
 *
 * Assumptions:
 *   - Student names are up to 49 characters long (excluding null terminator).
 *   - Test scores are integers between 0 and 100, inclusive.
 *   - The number of students is a positive integer.
 * Requirements:
 *
 * - Use functions to modularize your code (e.g., one for calculating the average, one for determining the grade).
 * - Use a switch or if statements for grade assignment.
 * - Store names in character arrays (e.g., char name[50]).
 * - Commit your code to your Git repo with clear comments and a README
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_STUDENT_SCORES 3
#define MAX_NAME 50

typedef struct grade{
    char letter;
    int number;
} Grade;

typedef struct student{
    char name[MAX_NAME];
    Grade grades[NUM_STUDENT_SCORES];
    float average;
    char grade;
} Student; 

/*
 * Displays the grades for a student.
 *
 * @param array Pointer to an array of Grade structs containing test scores and letters.
 * @param arraySize Number of grades to display (typically 3).
 */
void displayGrades(Grade* array, int arraySize)
{
    int i;
    if (arraySize > 0)
    {
        for (i = 0; i < arraySize; i++)
        {
            printf("%d->%c ", array[i].number, array[i].letter);
        }
        printf("\n");
    }
}

/*
 * Prompts the user for the number of students and allocates memory for them.
 *
 * @param studentsNumber Pointer to an integer to store the number of students.
 * @return Pointer to the allocated array of Student structs, or NULL on failure.
 */
Student* addStudentsNumber(int* studentsNumber)
{
    int result;
    do {
        printf("Enter number of students (positive integer): ");
        result = scanf("%d", studentsNumber);
        if (result != 1) {
            printf("Error: Please enter a valid integer.\n");
            while (getchar() != '\n');
        } else if (*studentsNumber <= 0) {
            printf("Error: Number of students must be positive.\n");
            while (getchar() != '\n');
        }
    } while (result != 1 || *studentsNumber <= 0);
    while (getchar() != '\n');
    //printf("The number of strudent is %d\n", *studentsNumber);
    Student* students = (Student*)malloc(*studentsNumber * sizeof(Student));
    if (students == NULL) {
        printf("Error: Failed to allocate memory for %d students.\n", *studentsNumber);
        exit(1);
    }
    return students;
}

/*
 * Validates and retrieves a test score for a student.
 *
 * @param scoreNumber The test number (1-based index) for the prompt.
 * @param name The name of the student for the prompt.
 * @return The validated score (0 to 100).
 */
int validateScore(int scoreNumber, char* name)
{
    int score, result;
    do {
        printf("Enter test score %d for %s: ", scoreNumber, name);
        result = scanf("%d", &score);
        if (result != 1) {
            printf("Error: Please enter a valid integer.\n");
            score = 0;
            while (getchar() != '\n');
        } else if (score <= 0 || score > 100) printf("Error: Scores must be between 0 and 100. Try again.\n");
    } while (score <= 0 || score > 100);
    //printf("You stored test score %d for %s: %d\n", scoreNumber, name, score);
    return score;
}

/*
 * Converts a numerical score to a letter grade.
 *
 * @param score Pointer to the numerical score (0 to 100).
 * @return The corresponding letter grade ('A' to 'F', or 'E' for invalid input).
 */
char generateLetterScore(int* score)
{
    if (*score >= 0 && *score <= 100)
    {
        switch (*score / 10)
        {
        case 10:
        case 9:
            return 'A';
        case 8:
            return 'B';
        case 7:
            return 'C';
        case 6:
            return 'D';
        default:
            return 'F';
        }
    }
    return 'E';
}

/*
 * Collects data (name and test scores) for all students.
 *
 * @param students Pointer to the array of Student structs.
 * @param studentsNumber Number of students to process.
 */
void storeStudentData(int* studentsNumber, Student* students)
{
    int i, j;
    if (*studentsNumber > 0 && students != NULL)
    {
        for (i = 0; i < *studentsNumber; i++)
        {
            printf("\nEnter name for student %d: ", i + 1);
            fgets(students[i].name, MAX_NAME, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            for (j = 0; j < NUM_STUDENT_SCORES; j++)
            {
                students[i].grades[j].number = validateScore(j + 1, students[i].name);
                students[i].grades[j].letter = generateLetterScore(&students[i].grades[j].number);
            }
            printf("Student %s scores: ", students[i].name);
            displayGrades(students[i].grades, NUM_STUDENT_SCORES);
        }
    }
}

/*
 * Calculates the average score and assigns an overall letter grade for each student.
 *
 * @param students Pointer to the array of Student structs.
 * @param studentsNumber Number of students to process.
 */
void calculateStudentsScoresAverage(int* studentsNumber, Student* students)
{
    int i, j, scoresSum;

    if (*studentsNumber > 0 && students != NULL)
    {
        for (i = 0; i < *studentsNumber; i++)
        {
            scoresSum = 0;
            for (j = 0; j < NUM_STUDENT_SCORES; j++)
            {
                scoresSum += students[i].grades[j].number;
            }
            students[i].average = (float) scoresSum / NUM_STUDENT_SCORES;
            int avgScore = (int)(students[i].average + 0.5);
            students[i].grade = generateLetterScore(&avgScore);
        }
    }
}

/*
 * Prints a formatted grade report for all students.
 *
 * @param students Pointer to the array of Student structs.
 * @param studentsNumber Number of students to include in the report.
 */
void printStudentsGradeReports(int* studentsNumber, Student* students)
{
    int i;

    if (*studentsNumber > 0 && students != NULL)
    {
        printf("\n\n --- Grade Report --- \n\n");
        for (i = 0; i < *studentsNumber; i++)
        {
            printf("%s: Average = %.2f, Grade = %c\n\n", students[i].name, students[i].average, students[i].grade);
        }
    }
}

/*
 * Main function: Orchestrates the program flow.
 * - Prompts for and allocates memory for students.
 * - Collects student data.
 * - Calculates averages and grades.
 * - Prints the grade report.
 * - Frees allocated memory.
 *
 * @return 0 on successful execution.
 */
int main ()
{
    /*Handle errors: reject invalid scores (outside 0–100) and ensure the number of students is positive.*/
    int studentsNumber = 0;
    Student* students;
    
    /*Accept the number of students (via scanf).*/
    students = addStudentsNumber(&studentsNumber);

    /*For each student, input their name (as a string) and three test scores (integers between 0 and 100).*/
    storeStudentData(&studentsNumber, students);

    /*Calculate the average score for each student and assign a letter grade (A: 90–100, B: 80–89, C: 70–79, D: 60–69, F: <60).*/
    calculateStudentsScoresAverage(&studentsNumber, students);

    /*Print a formatted report with each student’s name, average score, and letter grade.*/
    printStudentsGradeReports(&studentsNumber, students);

    free(students);
    students = NULL;

    return 0;
}