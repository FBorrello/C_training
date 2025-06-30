#ifndef GRADE_CALCULATOR_H
#define GRADE_CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>

#define NUM_STUDENT_SCORES 3
#define MAX_NAME 50

typedef struct grade {
    char letter;
    int number;
} Grade;

typedef struct student {
    char name[MAX_NAME];
    Grade grades[NUM_STUDENT_SCORES];
    float average;
    char grade;
} Student;

void displayGrades(Grade* array, int arraySize);
Student* addStudentsNumber(int* studentsNumber);
int validateScore(int scoreNumber, char* name);
char generateLetterScore(int* score);
void storeStudentData(int* studentsNumber, Student* students);
void calculateStudentsScoresAverage(int* studentsNumber, Student* students);
void printStudentsGradeReports(int* studentsNumber, Student* students);
void calculateAverageClassGrades(int* studentsNumber, Student* students);

#endif