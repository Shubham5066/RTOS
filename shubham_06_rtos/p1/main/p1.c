#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"
#include"freertos/timer.h"
#define MQ_SIZE 4
#define MSG_SIZE 64

TaskHandle_t serial_task1;
TaskHandle_t serial_task2;
TaskHandle_t serial_task3;
TaskHandle_t serial_task4;
TaskHandle_t serial_task5;

static int taskcore=1;

QueueHandle_t msg_queue;
TimerHandle_t serial_timer1;
TimerHandle_t serial_timer2;
TimerHandle_t serial_timer3;


void timer_fun1(TimerHandle_t serial_timer1)
{
	printf("\nTimer : 1 is fired");
}


void timer_fun2(TimerHandle_t serial_timer2)
{
        printf("\nTimer : 2 is fired");
}


void timer_fun3(TimerHandle_t serial_timer3)
{
        printf("\nTimer : 3 is fired");
}

void Task_1(void *data)
{

	printf("\nTimer 1 is started");
	printf("\nCrCeating a timer 1");
	serial_timer1=xTimerreate("one_s_timer",1000/portTICK_TO_MS,pdTRUE,0,timer_fun1);
	xTimerStart(serial_timer1,0);
	vTaskDelete(serial_task1);

}

void Task_2(void *data)
{

        printf("\nTimer 2 is started");
        printf("\nCreating a timer 2");
        serial_timer2=xTimerCreate("one_s_timer",2000/portTICK_TO_MS,pdTRUE,0,timer_fun2);
        xTimerStart(serial_timer2,0);
        vTaskDelete(serial_task2);

}


void Task_3(void *data)
{

        printf("\nTimer 3 is started");
        printf("\nCreating a timer 3");
        serial_timer3=xTimerCreate("one_s_timer",1000/portTICK_TO_MS,pdTRUE,0,timer_fun3);
        xTimerStart(serial_timer3,0);
        vTaskDelete(serial_task3);

}

void Task_4(void *data)
{
	int task_data=100;
	printf("Task 4: ");
	while(1)
	{
		task_data++;
		xQueueSend(msg_queue,&task_data,pdMS_TO_TICKS(10000));
		vTaskDelay(1000 /portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}


void Task_5(void *data)
{
	int buffer=0;
	printf("\nTask 5 :");
	while(1)
	{
		xQueueReceive(msg_queue,&buffer,portMAX_DELAY);
		printf("Task 4 Recived : %d\n",buffer);
	}
	vTaskDelete(NULL);
}




void app_main()
{

	printf("\nMain Function");
	msg_queue=xQueueCreate(MQ_SIZE,MSG_SIZE);
	xTaskCreatePinnedToCore(Task_1,"task1",2048,NULL,5,serial_task1,taskcore);
	xTaskCreatePinnedToCore(Task_2,"task2",2048,NULL,6,serial_task2,taskcore);
 	xTaskCreatePinnedToCore(Task_3,"task3",2048,NULL,7,serial_task3,taskcore);
	xTaskCreatePinnedToCore(Task_4,"task4",2048,NULL,8,serial_task4,taskcore);
	xTaskCreatePinnedToCore(Task_5,"task5",2048,NULL,9,serial_task5,taskcore);

}
