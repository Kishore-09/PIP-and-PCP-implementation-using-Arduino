#include "scheduler.h"

typedef struct {
    SemaphoreHandle_t mutex;
    TaskHandle_t owner;
    UBaseType_t originalPriority;
} CustomMutexResource;

CustomMutexResource resource1, resource2;

void setup() {
    Serial.begin(9600);
    while (!Serial);  

    resource1.mutex = xSemaphoreCreateMutex();
    resource2.mutex = xSemaphoreCreateMutex();

    BaseType_t task1Status, task2Status;
    task1Status = xTaskCreate(testTask1, "Task1", 256, NULL, 2, NULL);
    task2Status = xTaskCreate(testTask2, "Task2", 256, NULL, 1, NULL);

    if (task1Status != pdPASS) {
        Serial.println("Task 1 creation failed!");
    }
    if (task2Status != pdPASS) {
        Serial.println("Task 2 creation failed!");
    }
}

void loop() {
}

void testTask1(void *pvParameters) {
    while(1) {
        if (xSemaphoreTake(resource1.mutex, portMAX_DELAY) == pdTRUE) {
            Serial.println("Task 1 has taken Resource 1");
            vTaskDelay(pdMS_TO_TICKS(500)); 
            xSemaphoreGive(resource1.mutex);
            Serial.println("Task 1 has released Resource 1");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void testTask2(void *pvParameters) {
    while(1) {
        if (xSemaphoreTake(resource2.mutex, portMAX_DELAY) == pdTRUE) {
            Serial.println("Task 2 has taken Resource 2");
            vTaskDelay(pdMS_TO_TICKS(500)); 
            if (xSemaphoreTake(resource1.mutex, portMAX_DELAY) == pdTRUE) {
                Serial.println("Task 2 has taken Resource 1");
                vTaskDelay(pdMS_TO_TICKS(500)); 
                xSemaphoreGive(resource1.mutex);
                Serial.println("Task 2 has released Resource 1");
            }
            xSemaphoreGive(resource2.mutex);
            Serial.println("Task 2 has released Resource 2");
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}