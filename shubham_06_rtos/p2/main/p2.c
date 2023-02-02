
#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/timer.h"

TaskHandle_t serial_task1;
TaskHandle_t serial_task2;
TaskHandle_t serial_task3;

static int taskcore=1;

TimerHandle_t serial_timer1;
const TickTypes_t xDelay1=1000 /portTICK_PERIOD_MS;
const TickTypes_t xDelay2=2000 /portTICK_PERIOD_MS;
const TickTypes_t xDelay3=5000 /portTICK_PERIOD_MS;


void timer_callback(TimerHandle_t serial_timer1)
{
		printf("\nTimer is Fired");
}

void task_1(void *data)

{
	while(1)
	{
	printf("\nSerial Task 1 is started ");
	vTaskDelay(xDelay1);
	}
	vTaskDelete(serial_task1);
}

void task_2(void *data)

{
        while(1)
        {
        printf("\nSerial Task 2 is started ");
        vTaskDelay(xDelay2);
        }
        vTaskDelete(serial_task2);
}

void task_3(void *data)

{
	 printf("\nTimer 2 is started");
        printf("\nCreating a timer 2");
        serial_timer2=xTimerCreate("one_s_timer",10000/portTICK_TO_MS,pdTRUE,0,timer_callback);
        xTimerStart(serial_timer2,0);
        while(1)
        {
        printf("\nSerial Task 3 is started ");
        vTaskDelay(xDelay3);
        }
        vTaskDelete(serial_task3);
}


void app_main()
{
	BaseType_t serial1,serial2,serial3;

	printf("\nMain Function");
	serial1=xTaskCreatePinnedToCore(Task_1,"task1",2048,NULL,5,serial_task1,taskcore);
	if(serial1==pdPASS)
	{
		printf("\nTask 1 is created successfully");
	}
	serial2=xTaskCreatePinnedToCore(Task_2,"task2",2048,NULL,6,serial_task2,taskcore);
	if(serial2==pdPASS)
        {
                printf("\nTask 2 is created successfully");
        }

 	serial3=xTaskCreatePinnedToCore(Task_3,"task3",2048,NULL,7,serial_task3,taskcore);
	if(serial3==pdPASS)
        {
                printf("\nTask 3 is created successfully");
        }



}
