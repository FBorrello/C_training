#include <stdio.h>

int filter_sensor_data(int *input, int in_size, int *output, int *out_size);

int main()
{
    int array[] = {2, -5, -8, 2, 4};
    int new_array[5] = {0};
    int size = sizeof(array) / sizeof(int);
    int new_size = 0;
    int result = 0;
    
    result = filter_sensor_data(array, size, new_array, &new_size);

    printf("array\n");
    for (int i = 0; i < size; i ++)
    {
        printf("%d ", array[i]);
    }

    printf("\nnew array\n");
    for (int i = 0; i < new_size; i ++)
    {
        printf("%d ", new_array[i]);
    }
    printf("\n");
    
    if(result < 0)
    {
        printf("Sensors values filter failed");
    }

    return 0;
}

/*
Write a C function for an IoT device that filters invalid sensor readings (e.g., negative values) from an array using pointer arithmetic.
The function should take an input array, its size, an output array, and a pointer to the output array’s size.
It should copy only valid readings (non-negative values) to the output array and update the output size.
Return 0 on success, -1 on invalid inputs (NULL pointers or size <= 0).

Requirements:

Use pointer arithmetic, not array indexing, to process input and fill output.
Check for NULL pointers (input, output, out_size) and invalid in_size (<= 0).
Copy non-negative values from input to output using the provided output array.
Update *out_size with the count of valid (non-negative) readings.
Print the number of valid readings (e.g., printf("Valid readings: %d\n", *out_size);).
Return 0 on success, -1 on invalid inputs.
Do not allocate or free memory within the function.

*/
int filter_sensor_data(int *input, int in_size, int *output, int *out_size) {
    // Check for NULL pointers (input, output, out_size) and invalid in_size (<= 0).
    if (input == NULL)
    {
        printf("input pointer is NULL");
        return -1;
    }
    if (output == NULL)
    {
        printf("output pointer is NULL");
        return -1;
    }
    if (out_size == NULL)
    {
        printf("out_size pointer is NULL");
        return -1;
    }
    if (in_size <= 0)
    {
        printf("in_size is equal or less than 0");
        return -1;
    }

    //Copy non-negative values from input to output using the provided output array.
    // Update *out_size with the count of valid (non-negative) readings.
    int i, *array_p = input, *new_array_p = output;
    *out_size = 0;
    
    for (i = 0; i < in_size; i++)
    {
        if (*array_p >= 0)
        {
            *new_array_p = *array_p;
            new_array_p++;
            *out_size += 1;
        }
        array_p++;
        
    }

    //Print the number of valid readings (e.g., printf("Valid readings: %d\n", *out_size);).
    printf("Valid readings: %d\n", *out_size);

    return 0;
}