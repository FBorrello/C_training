#include <stdio.h>
#include <string.h>

void sortAscendingSensorsReading(float *seansors_readings, int array_size)
{
    if (seansors_readings == NULL)
    {
        printf("seansors_readings pointer is NULL");
    } else if (array_size <= 0)
    {
        printf("array_size is less or wqual to 0");
    }
    
    int i, j;
    float *array_p_head = seansors_readings;
    float *array_p_cursor = seansors_readings + 1;
    float temp;
    for (i = 1; i < array_size; i++)
    {
        for (j = i + 1; j <= array_size; j++)
        {
            if (*array_p_cursor < *array_p_head)
            {
                temp = *array_p_head;
                *array_p_head = *array_p_cursor;
                *array_p_cursor = temp;
            }
            
            array_p_cursor++;
        }
        
        array_p_head++;
        array_p_cursor = array_p_head + 1;
    }
}

void printSensorsData(char *header, float*seansors_readings, int array_size)
{
    int i;
    float *array_p_cursor = seansors_readings;
    printf("%s Sensors data: ", header);
    for (i = 0; i < array_size; i++){
        printf("%.2f ", *array_p_cursor);
        array_p_cursor++;
    }
    printf("\n");
}

int main() {
    float data[] = {5.1, 1.5, 4.7, 3.2, 2.3};
    int size = sizeof(data) / sizeof(float);
    char header[] = "Before";
    printSensorsData(header, data, size);
    sortAscendingSensorsReading(data, size);
    strcpy(header, "After");
    printSensorsData(header, data, size);
    return 0;
}