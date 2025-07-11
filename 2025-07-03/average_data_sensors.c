#include <stdio.h>

int process_sensor_data(int *data, int size, float *avg);

int main()
{
    int array[] = {2, 5, 8, 2, 4};
    int size = sizeof(array) / sizeof(int);
    float average;
    int result;
    
    result = process_sensor_data(array, size, &average);
    
    if(!result)
    {
        printf("Sensors values average failde");
    }

    return 0;
}

/*
Write a C function for an IoT device that processes sensor data stored in an array using pointers.
The function should take an array of integers (sensor readings), its size, and a pointer to store the average.
Use pointer arithmetic to calculate the sum and avoid dereferencing NULL pointers.
The function should return 0 on success or -1 if the input is invalid (e.g., NULL array or size <= 0).

Requirements:

Use pointer arithmetic instead of array indexing.
Check for NULL pointers and invalid sizes.
Store the average via the provided pointer.
Output the average to verify correctness (e.g., via printf).

*/
int process_sensor_data(int *data, int size, float *avg) {
    // Check for NULL pointers and invalid sizes.
    if (data == NULL) 
    {   printf("data pointer is NULL");
        return -1;
    }
    if (avg == NULL)
    {   printf("avg pointer is NULL");
        return -1;
    }
    if (size <= 0)
    {   printf("size is equal or less than 0");
        return -1;
    }
    
    // Use pointer arithmetic instead of array indexing.
    int sum = 0, i, *array_p = data;
    for (i = 0; i < size; i++)
    {
        sum += *array_p;
        array_p++;
    }
    
    // Store the average via the provided pointer.
    *avg = (float) sum / size;
    
    // Output the average to verify correctness (e.g., via printf).
    printf("Sensors values average: %.2f", *avg);
    
    return 0;
}