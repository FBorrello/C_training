#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

// Define the LED pin (GPIO 4 for ESP32-CAM onboard LED)
#define LED_PIN GPIO_NUM_4

void app_main(void)
{
    // Configure the LED pin
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_PIN), // Select GPIO 4
        .mode = GPIO_MODE_OUTPUT,          // Set as output
        .pull_up_en = GPIO_PULLUP_DISABLE, // No pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // No pull-down
        .intr_type = GPIO_INTR_DISABLE     // No interrupts
    };
    gpio_config(&io_conf);

    // Blink loop
    while (1) {
        gpio_set_level(LED_PIN, 1); // Turn LED ON
        vTaskDelay(500 / portTICK_PERIOD_MS); // Wait 500ms
        gpio_set_level(LED_PIN, 0); // Turn LED OFF
        vTaskDelay(500 / portTICK_PERIOD_MS); // Wait 500ms
    }
}