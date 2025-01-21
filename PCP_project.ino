#include "scheduler.h"

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;

void loop() {}


static void testFunc1( void *pvParameters )
{
	(void) pvParameters;
	volatile int i,a;
	for( i = 0; i < 10000; i++ )
	{
		a = 1 + i*i*i*i;
	}	
}

static void testFunc2( void *pvParameters )
{ 
	(void) pvParameters;	
	volatile int i, a;	
	for(i = 0; i < 10000; i++ )
	{
		a = 1 + a * a * i;
	}	
}

int main( void )
{
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
	char c1 = 'a';
	char c2 = 'b';			

	vSchedulerInit();

	vSchedulerPeriodicTaskCreate(testFunc1, "t1", configMINIMAL_STACK_SIZE, &c1, 1, &xHandle1, pdMS_TO_TICKS(0), pdMS_TO_TICKS(800), pdMS_TO_TICKS(100), pdMS_TO_TICKS(800));
	vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 2, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(400), pdMS_TO_TICKS(400), pdMS_TO_TICKS(400));



	vSchedulerStart();
	
	for( ;; );
}
void someTask(void *pvParameters);

TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

  xTaskCreate(someTask, "Task 1", 128, NULL, 2, &task1Handle);
  xTaskCreate(someTask, "Task 2", 128, NULL, 3, &task2Handle);

  vTaskStartScheduler();

}


