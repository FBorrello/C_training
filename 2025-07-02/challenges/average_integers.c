#include <stdio.h>

#define ARRAY_SIZE 5

/*
 * @brief Prompts the user to enter 5 integers and stores them in an array.
 *
 * @param array to store integers.
 */
void fillIntArray(int* array);

/*
 * @brief Calculates the average of those integers.
 *
 * @param average to store calculated average.
 * @param array to store integers.
 */
void averageIntArray(double* average, int* array);

/*
 * @brief Prints the average and all numbers greater than the average.
 *
 * @param average to store calculated average.
 * @param array to store integers.
 */
 void printIntArray(double* average, int* array);

int main()
{
    /*Prompts the user to enter 5 integers and stores them in an array.*/
    int array[ARRAY_SIZE];
    fillIntArray(array);

    /*Calculates the average of those integers.*/
    double average;
    averageIntArray(&average, array);

    /*Prints the average and all numbers greater than the average.*/
    printIntArray(&average, array);
}

void fillIntArray(int* array)
{
    int user_entry, i = 0;
    int result;
    for (; i < ARRAY_SIZE; i++)
    {
        do {
            printf("Enter the positive integer %d of %d: ", i + 1, ARRAY_SIZE);
            result = scanf("%d", &user_entry);
            if (result != 1)
            {
                printf("Error: Please enter a valid integer.\n");
                while (getchar() != '\n');
            }
        } while (result != 1);
        while (getchar() != '\n');
        array[i] = user_entry;
    }
}

void averageIntArray(double* average, int* array)
{
    int sum = 0, i;
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        sum += array[i];
    }
    *average = (double) sum / ARRAY_SIZE;
}

void printIntArray(double* average, int* array)
{
    int i;
    printf("Array average: %lf\n", *average);
    for (i = 0; i <= ARRAY_SIZE; i++)
    {
        if (array[i] > (int) *average)
        {
            printf("Integer %d in position %d into the array is grater than the average.\n", array[i], i + 1);
        }
    }
}