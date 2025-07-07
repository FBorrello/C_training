#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>


volatile uint16_t buffer = 0;
SemaphoreHandle_t sensor_semaphore;

void init_semaphore(void) {
    sensor_semaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(sensor_semaphore); // Initialize as available
}

void sensor_task(void *params) {
    volatile uint16_t *SENSOR_REG = (volatile uint16_t*)params;
    while (1) {
        if (xSemaphoreTake(sensor_semaphore, portMAX_DELAY) == pdTRUE) {
            buffer = *SENSOR_REG;
            xSemaphoreGive(sensor_semaphore);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000 ms delay
    }
}
uint8_t format_sensor_data(volatile uint16_t *buffer, char *output) {
    sprintf(output, "sensor:%d", *buffer);
    return strlen(output);
}

int main()
{
    volatile uint16_t sensor_reading = 1234;
    char string_output[10];
    uint8_t string_length = 0;
    
    sensor_task(&sensor_reading);
    string_length = format_sensor_data(&buffer, string_output);
    printf("%s\n", string_output);
    printf("%d\n", buffer);
    printf("%d\n", string_length);
    printf("value:%d", buffer);
    return 0;
}